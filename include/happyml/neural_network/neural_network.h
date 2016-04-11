
#ifndef _HAPPY_ML_NEURAL_NETWORK_H_
#define _HAPPY_ML_NEURAL_NETWORK_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"


namespace happyml
{

    class NeuralNetwork : public Classifier, public Serializable
    {
        private:

            /**
             * Number of layers - 1. The input layer is the first layer and the
             * output layer is the last one.
             */
            unsigned L;

            /**
             * Weights of the neuronal network.
             * The size of this vector is always \f$L\f$, but the first element
             * is always a 0x0 matrix.
             */
            vector<mat> weights;

            /**
             * Number of neurons of each layer.
             * The size of this vector is \f$L\f$.
             */
            vector<unsigned> d;


        public:

            /**
             * Creates a neural network with the layers and number of neurons
             * indicated in the arguments.
             * Initialize the weights to a random values.
             * 
             * By default (without parameters), creates an empty neural network
             * without layers. Use load method to give values to the network.
             * 
             * @param layers Number of layers, number of neurons on the input
             *               layer, number of neurons on the second layer...
             */
            NeuralNetwork(unsigned layers = 0 ...);

            /**
             * Creates a neural network with the layers and number of neurons
             * indicated in the vector.
             * Initialize the weights to a random values.
             * 
             * @param layers Number of neurons on the input layer, number of
             *               neurons on the second layer...
             */
            NeuralNetwork(const vector<unsigned>& layers);

            /**
             * Creates a neural network using the indicated weights matrices.
             * 
             * @param w Wheights matrices to use.
             */
            NeuralNetwork(const vector<mat> w);

            /**
             * Creates a copy of a neural network.
             */
            NeuralNetwork(const NeuralNetwork& nn);

            ~NeuralNetwork();


            /**
             * Returns a copy of all the weights of the neural network.
             * 
             * @return Copy of all the weights of the neural network.
             */
            const vector<mat> getWeights() const { return weights; }

            unsigned getNumberLayers() const { return L + 1; }

            unsigned getNumberNeurons(unsigned layer) const { return d[layer]; }

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
            
            void read(istream& stream);
            
            void write(ostream& stream) const;
    };

}


#endif // _HAPPY_ML_NEURAL_NETWORK_H_
