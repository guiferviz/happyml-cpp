
#include "happyml/transformer.h"


namespace happyml
{

    void Transformer::addPower(unsigned feature, double power, bool create_new)
    {
        actions.push_back(POW);
        features.push_back(feature);
        param.push_back(power);
        creates.push_back(create_new);
    }

    void Transformer::addAddition(unsigned feature, double n, bool create_new)
    {
        actions.push_back(ADD);
        features.push_back(feature);
        param.push_back(n);
        creates.push_back(create_new);
    }

    void Transformer::addProduct(unsigned feature, double n, bool create_new)
    {
        actions.push_back(MUL);
        features.push_back(feature);
        param.push_back(n);
        creates.push_back(create_new);
    }

    void Transformer::remove(unsigned feature)
    {
        removeOrder.push_back(feature);
    }

    void Transformer::applyActions(mat& x) const
    {
        unsigned nActions = actions.size();
        for (unsigned i = 0; i < nActions; ++i)
        {
            if (creates[i])
            {
                applyCreateNew(x, i);
            }
            else
            {
                applyNoCreateNew(x, i);
            }
        }
        // Last we remove features from higher to low.
        for(deque<unsigned>::const_reverse_iterator it = removeOrder.rbegin();
                it != removeOrder.rend(); ++it)
        {
            x.shed_col(*it);
        }
    }

    void Transformer::applyCreateNew(mat& x, unsigned i) const
    {
        unsigned feature = features[i];
        colvec feature_i = x.col(feature);
        switch (actions[i])
        {
            case ADD:
                feature_i += param[i];
                break;
            case MUL:
                feature_i *= param[i];
                break;
            case POW:
                feature_i = pow(feature_i, param[i]);
                break;
        }
        x.insert_cols(x.n_cols, feature_i);
    }

    void Transformer::applyNoCreateNew(mat& x, unsigned i) const
    {
        unsigned feature = features[i];
        switch (actions[i])
        {
            case ADD:
                x.col(feature) += param[i];
                break;
            case MUL:
                x.col(feature) *= param[i];
                break;
            case POW:
                x.col(feature) = pow(x.col(feature), param[i]);
                break;
        }
    }

    void Transformer::applyNormalization(mat& x) const
    {
        // Assumes stdDeviationVec and meanVec have been correctly initialized.
        mat stdDeviationMat = vec(x.n_rows, fill::ones) * stdDeviationVec;
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        
        x -= meanMat;
        x /= stdDeviationMat;
    }

    void Transformer::applyPCA(mat& x) const
    {
        // Assumes eigVec has been correctly initialized.
        // Normalize if is not already normalized.
        if (!toNormalize)
        {
            mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
            x -= meanMat;
        }
        x *= eigVec;
        // x is now a z vector (transformed).
    }

    void Transformer::apply(DataSet& dataset)
    {
        // Apply all the actions (add, sub, pow and delete).
        applyActions(dataset.X);
        // Let's normalize the dataset.
        if (toNormalize)
        {
            // Remove x_0 feature.
            dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
            // Initialize meanVec and stdDeviationVec using the currect dataset.
            if (meanVec.size() == 0)
            {
                // Compute and save the mean.
                meanVec = mean(dataset.X);
                
                // Compute and save the standard deviation.
                stdDeviationVec = stddev(dataset.X);
                // Change 0s to 1e-100 to avoid NaN in the division.
                stdDeviationVec.elem(find(stdDeviationVec == 0)).fill(1e-100);
            }
            // Apply normalization.
            applyNormalization(dataset.X);
            // Add x_0 = 1 feature.
            dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        }
        // Initialize eigenvalues and eigenvectors if PCA is required.
        if (pcaK > 0 || pcaVariance > 0)
        {
            // Remove x_0 feature.
            dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
            mat covMat;
            if (toNormalize)
            {
                covMat = cov(dataset.X);
            }
            else if (meanVec.size() == 0)
            {
                // Compute and save the mean.
                meanVec = mean(dataset.X);
                // X mean.
                mat Xm = dataset.X - vec(dataset.N, fill::ones) * meanVec;
                // Covariance matrix.
                covMat = cov(Xm);
            }
            // Save eigenvectors and eigenvalues.
            if (eigVal.size() == 0)
            {
                eig_sym(eigVal, eigVec, covMat);  // return eig in ascendenting order.
                if (pcaK > 0)
                {
                    eigVec = eigVec.cols(eigVec.n_cols - pcaK, eigVec.n_cols - 1);
                }
            }
            // Apply PCA.
            applyPCA(dataset.X);
            // Add x_0 = 1 feature.
            dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        }
        dataset.d = dataset.X.n_cols - 1;
    }

    void Transformer::normalize()
    {
        toNormalize = true;
    }

    void Transformer::pca(int k)
    {
        pcaVariance = 0;
        pcaK = k;
    }

    void Transformer::pcaMinVariance(double pcaVar)
    {
        pcaVariance = pcaVar;
        pcaK = 0;
    }

    Input Transformer::apply(const Input& input) const
    {
        mat x = input.t();
        applyActions(x);
        x = x.cols(1, x.n_cols - 1);
        if (toNormalize)
        {
            applyNormalization(x);
        }
        if (pcaK > 0 || pcaVariance > 0)
        {
            applyPCA(x);
        }
        x = join_rows(vec(x.n_rows, fill::ones), x);
        
        return x.t();
    }

}
