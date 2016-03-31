
#include "happyml/transformers/normalizer.h"


namespace happyml
{

    Normalizer::Normalizer(const DataSet& dataset)
    {
        init(dataset.X.cols(1, dataset.X.n_cols - 1));
    }

    Normalizer::Normalizer(const mat& x)
    {
        init(x);
    }

    Normalizer::Normalizer(const vec& minvec, const vec& maxvec)
    {
        init(join_cols(minvec.t(), maxvec.t()));
    }


    void Normalizer::init(const mat& x)
    {
        // Compute and save the min and max values.
        minx = min(x, 0);
        maxx = max(x, 0);
        
        // Compute and save the range.
        rangex = maxx - minx;
        // Change 0s to 1e-100 to avoid NaN in the division.
        rangex.elem(find(rangex == 0)).fill(1e-100);
    }


    void Normalizer::apply(DataSet& dataset) const
    {
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
        
        apply(dataset.X);
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
    }

    void Normalizer::apply(mat& x) const
    {
        mat minMat = vec(x.n_rows, fill::ones) * minx;
        mat rangeMat = vec(x.n_rows, fill::ones) * rangex;
        
        x -= minMat;
        x /= rangeMat;
    }

    Input Normalizer::apply(const Input& x) const
    {
        mat input = x.t();
        input = input.cols(1, input.n_cols - 1);
        
        apply(input);
        
        input = join_rows(vec(input.n_rows, fill::ones), input);
        return input.t();
    }

}
