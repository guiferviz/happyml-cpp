
#ifndef _HAPPY_ML_LINEAR_REGRESSION_H_
#define _HAPPY_ML_LINEAR_REGRESSION_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"
#include "happyml/linear_model.h"


using namespace arma;


namespace happyml
{

    class LinearRegression : public Predictor, public LinearModel
    {
        public:

            /**
             * Creates a linear regression algorithm with the indicated
             * input size.
             * 
             * @param d Dimension \f$d\f$, number of features of the input
             *          vectors.
             */
            LinearRegression(unsigned d = 0) : LinearModel(d) {}

            /**
             * Creates a linear regression algorithm with the indicated
             * weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ size.
             */
            LinearRegression(const vec& weights) : LinearModel(weights) {}

            LinearRegression(const LinearModel& lm) : LinearModel(lm) {}


            /**
             * Train the linear regression.
             * 
             * @param data Training set.
             *
             * @return Returns the final error.
             */
            double train(const DataSet& data);

            /**
             * Train the linear regression.
             * 
             * @param data Training set.
             * @param lambda Regularization paramiter \f$\lambda\f$.
             *
             * @return Returns the final error.
             */
            double train(const DataSet& data, double lambda);

            /**
             * Predict the output of an input vector.
             *
             * @return Estimated real output.
             */
            double predict(const Input& x) const;

            /**
             * Compute the mean squared error of the linear regression
             * algorithm on the given dataset.
             * 
             * @param data Dataset with the correct output.
             * 
             * @return Error of classify the given dataset. It's value is
             *         grater than \f$0\f$.
             */
            double error(const DataSet& data) const;
    };

}


#endif  // _HAPPY_ML_LINEAR_REGRESSION_H_
