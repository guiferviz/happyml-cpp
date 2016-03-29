
#include "happyml/transformers/pca.h"


using namespace std;


namespace happyml
{

    PCA::PCA(const DataSet& dataset, double n)
    {
        init(dataset.X.cols(1, dataset.X.n_cols - 1));
    }
    
    PCA::PCA(const mat& x)
    {
        init(x);
    }


    void PCA::init(const mat& x)
    {
        
    }

    void PCA::apply(DataSet& dataset) const
    {
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
        
        apply(dataset.X);
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
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
