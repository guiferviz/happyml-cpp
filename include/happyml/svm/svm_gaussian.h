
#ifndef _HAPPY_ML_SVM_GAUSSIAN_H_
#define _HAPPY_ML_SVM_GAUSSIAN_H_


#include "happyml/types.h"
#include "happyml/svm/svm.h"
#include "happyml/linear_model.h"


namespace happyml
{

    /**
     * Support vector machine with linear kernel.
     */
    class SVMGaussian : public SVM
    {
        protected:

            double sigma;


        public:

            /**
             * Creates a guassian kernel SVM without any support vector.
             * Needs to be trained.
             * 
             * @param s Sigma gaussian kernel parameter.
             */
            SVMGaussian(double s = 1) { sigma = s; }
            
            ~SVMGaussian() {}


            double getSigma() const { return sigma; }

            void setSigma(double s) { sigma = s; }

            double kernel(vec x, vec z) const;
    };

}


#endif  // _HAPPY_ML_SVM_GAUSSIAN_H_
