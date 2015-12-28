
#ifndef _HAPPY_ML_LOGISTIC_REGRESSION_H_
#define _HAPPY_ML_LOGISTIC_REGRESSION_H_


#include "happyml.h"


using namespace arma;


namespace happyml
{

    class LogisticRegression : public Classifier
    {
        private:

            vec w;

        public:

            /**
             * Creates a logistic regression algorithm with the indicated
             * input size.
             * 
             * @param d Dimension \f$d\f$ of the input feature vectors.
             */
            LogisticRegression(unsigned d = 0);

            /**
             * Creates a logistic regression algorithm with the indicated
             * weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ size.
             */
            LogisticRegression(const vec& weights);

            /**
             * Creates a logistic regression algorithm from the weights of
             * the other algorithm.
             */
            LogisticRegression(const LogisticRegression&);

            /**
             * Destroys the logistic regression algorithm (sets the weights
             * to \f$0\f$).
             */
            ~LogisticRegression();


            /**
             * Get a copy of the logistic regression weights.
             * 
             * @return Copy of the logistic regression weights.
             */
            vec getWeights() const { return w; }

            /**
             * Train the logistic regression until the training loops over the
             * data nTimes, or classifies all correctly.
             * Data must contain the \f$x_0 = 1\f$ property.
             * 
             * @param data Training set.
             * @param iter Maximun number of iterations.
             * @param learning_rate Learning rate.
             *
             * @return Returns the error of the best weights found.
             */
            double train(const DataSet& data, unsigned iter,
                    double learning_rate);

            /**
             * Classifies an input vector.
             *
             * @return Probability of the input to belong to +1 class.
             *         Output in the interval \f$[0, 1]\f$.
             */
            double classify(const Input& x) const;

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
