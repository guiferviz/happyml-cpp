
#ifndef _HAPPY_ML_PERCEPTRON_H_
#define _HAPPY_ML_PERCEPTRON_H_


#include "happyml.h"


using namespace arma;


namespace happyml
{

    class Perceptron : public Classifier
    {
        private:

            vec w;

        public:

            /**
             * Creates a perceptron with the indicated input size.
             * 
             * @param d Dimension \f$d\f$ of the input feature vectors.
             */
            Perceptron(int d);

            /**
             * Creates a perceptron with the indicated weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ dimensions.
             */
            Perceptron(const vec& weights);

            /**
             * Creates a perceptron from the weights of the other perceptron.
             */
            Perceptron(const Perceptron&);

            /**
             * Destroys the percetron (sets the weights to \f$0\f$).
             */
            ~Perceptron();


            /**
             * Get a copy of the perceptron weights.
             * 
             * @return Copy of the perceptron weights.
             */
            vec getWeights() const { return w; }

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
            double classify(const Input& x) const;

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
