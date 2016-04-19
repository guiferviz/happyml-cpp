
#ifndef _HAPPY_ML_SVM_H_
#define _HAPPY_ML_SVM_H_


#include "happyml/types.h"
#include "happyml/predictor.h"
#include "happyml/linear_model.h"


namespace happyml
{

    /**
     * Support vector machine with linear kernel.
     */
    class SVM : public Classifier, public LinearModel
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
             * Returns the bias term. It's the first weight of the vector of
             * weights.
             * 
             * @return Bias term.
             */
            double getBias() const { return w[0]; }

            /**
             * Returns the number of support vectors found.
             * 
             * @return Number of support vectors.
             */
            int getNumberSupportVectors() const { return sv.N; }

            /**
             * Returns a dataset with the support vectors found.
             * 
             * @return Dataset with the support vectors.
             */
            DataSet getSupportVectors() const { return sv; }

            /**
             * Train the SVM using the given dataset and the given parameters.
             * 
             * @param data Training set.
             * @param C    SVM regularization parameter.
             * @param iter Maximun number of iterations that the SMO algorithm
             *             does all over the dataset.
             * @param tolerance Tolerance that checks if a change in any alpha
             *                  is significant to continue with other iteration.
             *
             * @return Returns the error of the SVM.
             */
            double train(const DataSet& data, double C = 1, unsigned iter = 5,
                    double tolerance = 0.001);

            /**
             * Classifies an input vector.
             *
             * @return \f$-1\f$ or \f$+1\f$.
             */
            double predict(const Input& x) const;
    };

}


#endif  // _HAPPY_ML_SVM_H_
