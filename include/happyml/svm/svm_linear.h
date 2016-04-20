
#ifndef _HAPPY_ML_SVM_LINEAR_H_
#define _HAPPY_ML_SVM_LINEAR_H_


#include "happyml/types.h"
#include "happyml/svm/svm.h"
#include "happyml/linear_model.h"


namespace happyml
{

    /**
     * Support vector machine with linear kernel.
     */
    class SVMLinear : public SVM, public LinearModel
    {
        public:

            /**
             * Creates a linear kernel SVM without any support vector.
             * Needs to be trained.
             */
            SVMLinear() {}
            
            ~SVMLinear() {}


            double train(const DataSet& data, double C = 1, unsigned iter = 5,
                    double tolerance = 0.001);

            double kernel(vec x, vec z) const;
            
            double predict(const Input& input) const;
    };

}


#endif  // _HAPPY_ML_SVM_H_
