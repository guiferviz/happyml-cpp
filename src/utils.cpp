
#include "happyml/utils.h"

#include <math.h>


namespace happyml
{

    int sgn(double x)
    {
        return (x >= 0) ? 1 : -1;
    }

    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }

}
