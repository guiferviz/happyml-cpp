
#include "happyml/transformers/standarizer.h"


namespace happyml
{

    void Standarizer::init(const mat& x)
    {
        // Compute and save the min and max values.
        meanVec = mean(x);
        
        // Compute and save the range.
        stdVec = stddev(x);
        // Change 0s to 1e-100 to avoid NaN in the division.
        stdVec.elem(find(stdVec == 0)).fill(1e-100);
    }

    void Standarizer::apply(mat& x) const
    {
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        mat stdMat = vec(x.n_rows, fill::ones) * stdVec;
        
        x -= meanMat;
        x /= stdMat;
    }

    void Destandarizer::apply(mat& x) const
    {
        mat meanMat = vec(x.n_rows, fill::ones) * meanVec;
        mat stdMat = vec(x.n_rows, fill::ones) * stdVec;
        
        x %= stdMat;
        x += meanMat;
    }

}
