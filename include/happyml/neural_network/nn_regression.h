
#ifndef _HAPPY_ML_NN_REGRESSION_H_
#define _HAPPY_ML_NN_REGRESSION_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"


namespace happyml
{

    class NNRegression : public Predictor
    {
        private:

            /*
             * Number of layers. The input layer is the first layer and the
             * output layer is the last one.
             */
            unsigned L;

            /*
             * Weights of the neuronal network.
             * The size of this vector is always \f$L - 1\f$.
             */
            vector<mat> weights;

            /*
             * Number of neurons of each layer.
             * The size of this vector is \f$L\f$.
             */
            vector<unsigned> d;


        public:

            /**
             * Creates a neural network with the layers and number of neurons
             * indicated in the arguments.
             * Initialize the weight to a random values.
             * 
             * @param layers Number of layers, number of neurons on the input
             *               layer, number of neurons on the second layer...
             */
            NNRegression(unsigned layers ...);

            /**
             * Creates a copy of a neural network.
             */
            NNRegression(const NNRegression& nn);

            ~NNRegression();


            /**
             * Returns a copy of all the weights of the neural network.
             * 
             * @return Copy of all the weights of the neural network.
             */
            const vector<mat> getWeights() const { return weights; }

            /**
             * Train the neural network until the training loops over the
             * data iter times.
             * 
             * @param dataset Training set \f$\mathcal{D}\f$.
             * @param learningRate Learning rate \f$\eta\f$.
             * @param iter Number of iterations.
             * @param lambda Regularization paramiter \f$\lambda\f$.
             *
             * @return Returns the error after the training.
             */
            double train(const DataSet& dataset, unsigned iter = 500,
                    float learning_rate = 0.1, float lambda = 0);

            /**
             * Uses the forward propagation algorithm to predict an output.
             * 
             * @param x Input vector.
             * 
             * @return Predicted value
             */
            double predict(const Input& x) const;
            vec predictVec(const Input& x) const;
    };

}


#endif // _HAPPY_ML_NN_REGRESSION_H_
