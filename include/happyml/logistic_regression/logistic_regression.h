
#ifndef _HAPPY_ML_LOGISTIC_REGRESSION_H_
#define _HAPPY_ML_LOGISTIC_REGRESSION_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"
#include "happyml/linear_model.h"


using namespace arma;


namespace happyml
{

    class LogisticRegression : public Classifier, LinearModel
    {
        public:

            /**
             * Creates a logistic regression algorithm with the indicated
             * input size.
             * 
             * @param d Dimension \f$d\f$ of the input feature vectors.
             */
            LogisticRegression(unsigned d = 0) : LinearModel(d) {}

            /**
             * Creates a logistic regression algorithm with the indicated
             * weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ size.
             */
            LogisticRegression(const vec& weights) : LinearModel(weights) {}

            LogisticRegression(const LinearModel& lm) : LinearModel(lm) {}


            /**
             * Train the logistic regression until the training loops over the
             * data nTimes, or classifies all correctly.
             * Data must contain the \f$x_0 = 1\f$ property.
             * 
             * @param data Training set.
             * @param iter Maximun number of iterations (\f$1000\f$ by default).
             * @param learning_rate Learning rate (\f$0.1\f$ by default.).
             *
             * @return Returns the error of the best weights found.
             */
            double train(const DataSet& data, unsigned iter = 1000,
                    double learning_rate = 0.1);

            /**
             * Classifies an input vector.
             *
             * @return Probability of the input to belong to +1 class.
             *         Output in the interval \f$[0, 1]\f$.
             */
            double predict(const Input& x) const;

            /**
             * Compute the error of the logistic regression on the given
             * dataset.
             * 
             * @param data Dataset with the correct output.
             * 
             * @return Error of classify the given dataset. It's value is
             *         grater than \f$0\f$.
             */
            double error(const DataSet& data) const;
    };

}


#endif  // _HAPPY_ML_LOGISTIC_REGRESSION_H_
