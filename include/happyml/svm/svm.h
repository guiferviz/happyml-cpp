
#ifndef _HAPPY_ML_SVM_H_
#define _HAPPY_ML_SVM_H_


#include "happyml/types.h"
#include "happyml/predictor.h"


namespace happyml
{

    /**
     * Support vector machine with linear kernel.
     */
    class SVM : public Classifier
    {
        private:

            /**
             * Support vectors.
             */
            DataSet sv;

        public:

            /**
             * Creates a SVM without any support vector.
             * Needs to be trained.
             */
            SVM() {}


            /**
             * Train the SVM using the given dataset and the given parameters.
             * 
             * @param data Training set.
             * @param C \f$C\f$ constant.
             * @param iter Maximun number of iterations.
             * @param tolerance Tolerance that checks if a change in any alpha
             *                  is significant to continue with other iteration.
             *
             * @return Returns the error of the SVM.
             */
            double train(const DataSet& data, double C, unsigned iter,
                    double tolerance);

            /**
             * Classifies an input vector.
             *
             * @return \f$-1\f$ or \f$+1\f$.
             */
            double predict(const Input& x) const;

            /**
             * Compute the error of the SVM on the given dataset.
             * 
             * @param data Dataset with the correct output.
             * 
             * @return Error of classify the given dataset.
             */
            double error(const DataSet& data) const;
    };

}


#endif  // _HAPPY_ML_SVM_H_
