
#include "happyml/transformers/lda.h"


using namespace std;


namespace happyml
{

    LDA::LDA(const DataSet& dataset, double n)
    {
        k = (int) n;
        minVar = n;
        mat x = dataset.X.cols(1, dataset.X.n_cols - 1);
        mat y = dataset.y;
        // Number of classes.
        // TODO: make it work with more than 2 classes.
        int classes = 2;
        // Select elements by class.
        uvec pClassIndex = find(y ==  1);  // positive class
        uvec nClassIndex = find(y == -1);  // negavive class
        mat pClass = x.rows(pClassIndex);
        mat nClass = x.rows(nClassIndex);
        mat pMean = mean(pClass);
        mat nMean = mean(nClass);
        mat mu = join_vert(pMean, nMean);
        // Compute and save the mean.
        meanVec = mean(x);
        // Sw
        uvec c(y.n_rows);
        c(pClassIndex).fill(0);
        c(nClassIndex).fill(1);
        mat Sw = (x - mu.rows(c));
        Sw = Sw.t() * Sw;
        // Sb
        mat Sb = ones(classes) * meanVec - mu;
        Sb = Sb.t() * Sb;
        // 
        mat matrix = pinv(Sw) * Sb;
        // Compute and save eigen vectors and values.
        eig_sym(eigVal, eigVec, matrix);  // return eig in ascendenting order
        
        if (k == minVar)
        {
            double total = sum(eigVal);
            // Selects first k vectors.
            eigVec = eigVec.cols(eigVec.n_cols - k, eigVec.n_cols - 1);
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

    void LDA::apply(DataSet& dataset) const
    {
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
        
        apply(dataset.X);
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        dataset.d = dataset.X.n_cols - 1;
    }

    void LDA::apply(mat& x) const
    {
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        
        x -= meanMat;
        x *= eigVec;
    }

    Input LDA::apply(const Input& x) const
    {
        mat input = x.t();
        input = input.cols(1, input.n_cols - 1);
        
        apply(input);
        
        input = join_rows(vec(input.n_rows, fill::ones), input);
        return input.t();
    }


}
