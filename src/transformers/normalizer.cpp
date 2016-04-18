
#include "happyml/transformers/normalizer.h"


namespace happyml
{

    // NORMALIZER.

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

    void Normalizer::apply(mat& x) const
    {
        mat minMat = vec(x.n_rows, fill::ones) * minx;
        mat rangeMat = vec(x.n_rows, fill::ones) * rangex;
        
        x -= minMat;
        x /= rangeMat;
    }

    
    // DENORMALIZER.

    void Denormalizer::apply(mat& x) const
    {
        mat minMat = vec(x.n_rows, fill::ones) * minx;
        mat rangeMat = vec(x.n_rows, fill::ones) * rangex;
        
        x %= rangeMat;
        x += minMat;
    }
}
