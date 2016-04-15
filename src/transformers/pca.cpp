
#include "happyml/transformers/pca.h"


using namespace std;


namespace happyml
{

    PCA::PCA(const DataSet& dataset, double n)
    {
        k = (int) n;
        minVar = n;
        init(dataset.X.cols(1, dataset.X.n_cols - 1));
    }
    
    PCA::PCA(const mat& x, double n)
    {
        k = (int) n;
        minVar = n;
        init(x);
    }


    void PCA::init(const mat& x)
    {
        // Compute and save the mean.
        meanVec = mean(x);
        // X mean.
        mat Xm = x - vec(x.n_rows, fill::ones) * meanVec;
        // Covariance matrix.
        covMat = cov(Xm);
        // Compute and save eigen vectors and values.
        eig_sym(eigVal, eigVec, covMat);  // return eig in ascendenting order
        
        if (k == minVar)
        {
            double total = sum(eigVal);
            // Selects first k vectors.
            eigVec = eigVec.cols(eigVec.n_cols - k, eigVec.n_cols - 1);
            eigVal = eigVal.cols(eigVal.n_cols - k, eigVal.n_cols - 1);
            // Compute variance retained.
            double partial_sum = sum(eigVal);
            minVar = partial_sum / total;
        }
        else
        {
            // Selects a number of dimensions that retains the minVar required.
            double total = sum(eigVal);
            double sum = 0;
            for (int i = eigVec.n_cols - 1; i >= 0; --i)
            {
                sum += eigVal(i);
                if (sum / total >= minVar)
                {
                    minVar = sum / total;  // save the variance retained.
                    eigVec = eigVec.cols(i, eigVec.n_cols - 1);
                    break;
                }
            }
        }
    }

    void PCA::apply(DataSet& dataset) const
    {
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
        
        apply(dataset.X);
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        dataset.d = dataset.X.n_cols - 1;
    }

    void PCA::apply(mat& x) const
    {
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        
        x -= meanMat;
        x *= eigVec;
    }

    Input PCA::apply(const Input& x) const
    {
        mat input = x.t();
        input = input.cols(1, input.n_cols - 1);
        
        apply(input);
        
        input = join_rows(vec(input.n_rows, fill::ones), input);
        return input.t();
    }


}
