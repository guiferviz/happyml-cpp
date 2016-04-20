
#include "happyml/svm/svm_gaussian.h"
#include "happyml/utils.h"


namespace happyml
{

    double SVMGaussian::kernel(vec x1, vec x2) const
    {
        return exp(-pow(norm(x1 - x2), 2) / (2 * pow(sigma, 2)));
    }

}
