
#ifndef _HAPPY_ML_H_
#define _HAPPY_ML_H_


#include <string>
#include <armadillo>

#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/transformer.h"
#include "happyml/predictor.h"
#include "happyml/perceptron/perceptron.h"
#include "happyml/logistic_regression/logistic_regression.h"
#include "happyml/linear_regression/linear_regression.h"
#include "happyml/neural_network/neural_network.h"
#include "happyml/neural_network/nn_regression.h"
#include "happyml/svm/svm.h"
#include "happyml/knn/knn.h"
#include "happyml/happytools.h"
#include "happyml/k_fold_cross_validation.h"


#ifndef HAPPY_ML_VERSION
    #define HAPPY_ML_VERSION "1.0"
#endif


using namespace std;
using namespace arma;


/**
 * HappyML library namespace.
 * All in this library is under this namespace.
 */
namespace happyml
{

    /**
     * String with the library version.
     */
    const string version = HAPPY_ML_VERSION;


    /**
     * **Prints a greeting** to the standard output.
     * This library it's not only a **happy** library, it's also a **polite**
     * library :)
     */
    void greet();

}


#endif  // _HAPPY_ML_H_
