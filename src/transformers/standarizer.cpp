
#include "happyml/transformers/standarizer.h"


namespace happyml
{

    Standarizer::Standarizer(const DataSet& dataset)
    {
        init(dataset.X.cols(1, dataset.X.n_cols - 1));
    }

    Standarizer::Standarizer(const mat& x)
    {
        init(x);
    }


    void Standarizer::init(const mat& x)
    {
        // Compute and save the min and max values.
        meanVec = mean(x);
        
        // Compute and save the range.
        stdVec = stddev(x);
        // Change 0s to 1e-100 to avoid NaN in the division.
        stdVec.elem(find(stdVec == 0)).fill(1e-100);
    }


    void Standarizer::apply(DataSet& dataset) const
    {
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
        
        apply(dataset.X);
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
    }

    void Standarizer::apply(mat& x) const
    {
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        mat stdMat = vec(x.n_rows, fill::ones) * stdVec;
        
        x -= meanMat;
        x /= stdMat;
    }

    Input Standarizer::apply(const Input& x) const
    {
        mat input = x.t();
        input = input.cols(1, input.n_cols - 1);
        
        apply(input);
        
        input = join_rows(vec(input.n_rows, fill::ones), input);
        return input.t();
    }

}
