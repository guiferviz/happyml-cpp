
#ifndef _HAPPY_ML_LINEAR_REGRESSION_H_
#define _HAPPY_ML_LINEAR_REGRESSION_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"
#include "happyml/transformer.h"


using namespace arma;


namespace happyml
{

    class LinearRegression : public Classifier
    {
        private:

            vec w;

        public:

            /**
             * Creates a linear regression algorithm with the indicated
             * input size.
             * 
             * @param d Dimension \f$d\f$, number of features of the input
             *          vectors.
             */
            LinearRegression(unsigned d = 0);

            /**
             * Creates a linear regression algorithm with the indicated
             * weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ size.
             */
            LinearRegression(const vec& weights);

            /**
             * Creates a linear regression algorithm from the weights of
             * the other algorithm.
             * 
             * @param lr Linear regression to copy.
             */
            LinearRegression(const LinearRegression& lr);

            /**
             * Destroys the linear regression algorithm (sets the weights
             * size to \f$0\f$).
             */
            ~LinearRegression();


            /**
             * Get a copy of the linear regression weights.
             * 
             * @return Copy of the linear regression weights.
             */
            vec getWeights() const { return w; }

            /**
             * Train the linear regression.
             * 
             * @param data Training set.
             *
             * @return Returns the final error.
             */
            double train(const DataSet& data);

            /**
             * Predict the output of an input vector.
             *
             * @return Estimated real output.
             */
            double classify(const Input& x) const;

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

            /**
             * TODO: Add comment.
             */
            void saveLine(const string& filename, double minx, double maxx,
                    unsigned samples) const;

            /**
             * TODO: Add comment.
             */
            void saveLine(const string& filename, double minx, double maxx,
                    unsigned samples, const Transformer& t) const;
    };

}


#endif  // _HAPPY_ML_LINEAR_REGRESSION_H_
