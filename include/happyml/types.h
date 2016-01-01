
#ifndef _HAPPY_ML_TYPES_H_
#define _HAPPY_ML_TYPES_H_


#include <armadillo>
#include <istream>
#include <ostream>

#include "happyml/dataset.h"


using namespace arma;
using namespace std;


namespace happyml
{

    /**
     * Vector of inputs features.
     * \f$
     * \mathbf{x} = \begin{pmatrix}
     *      x_0 \\
     *      x_1 \\
     *      \vdots \\
     *      x_d
     * \end{pmatrix}
     * \f$
     */
    typedef vec Input;

}


#endif  // _HAPPY_ML_TYPES_H_
