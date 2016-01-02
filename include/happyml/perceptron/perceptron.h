
#ifndef _HAPPY_ML_PERCEPTRON_H_
#define _HAPPY_ML_PERCEPTRON_H_


#include "happyml/types.h"
#include "happyml/predictor.h"
#include "happyml/linear_model.h"


namespace happyml
{

    class Perceptron : public Classifier, LinearModel
    {
        public:

            /**
             * Creates a perceptron with the indicated input size.
             * 
             * @param d Dimension \f$d\f$ of the input feature vectors.
             */
            Perceptron(unsigned d = 0) : LinearModel(d) {}

            /**
             * Creates a perceptron with the indicated weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ dimensions.
             */
            Perceptron(const vec& weights) : LinearModel(weights) {}

            Perceptron(const LinearModel& lm) : LinearModel(lm) {}


            /**
             * Train the perceptron until the training loops over the data nTimes,
             * or classifies all correctly.
             * Data must contain the \f$x_0 = 1\f$ property.
             * 
             * @param data Training set.
             * @param iter Maximun number of iterations.
             *
             * @return Returns the error of the best perceptron found.
             */
            double train(const DataSet& data, unsigned iter);

            /**
             * Classifies an input vector.
             *
             * @return \f$-1\f$ or \f$+1\f$.
             */
            double predict(const Input& x) const;

            /**
             * Compute the error of the perceptron on the given dataset.
             * 
             * @param data Dataset with the correct output.
             * 
             * @return Error of classify the given dataset. It's in the
             *         interval \f$[0, 1]\f$.
             */
            double error(const DataSet& data) const;
    };

}


#endif  // _HAPPY_ML_PERCEPTRON_H_
