
#ifndef _HAPPY_ML_NEURAL_NETWORK_H_
#define _HAPPY_ML_NEURAL_NETWORK_H_


#include "happyml/serializable.h"

#include <armadillo>


using namespace arma;


namespace happyml
{

    /**
     * Hypothesis that uses a network of neurons. The weights of each layer are
     * represented using matrices.
     * 
     * This class contains a protected vector of matrices weights, a public
     * getter and load/save methods.
     */
    class NeuralNetworkModel : public Serializable
    {
        protected:

            /**
             * Number of layers - 1. The input layer is the first layer (indexed
             * as 0) and the output layer is the last one (indexed as L).
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
             * The size of this vector is \f$L + 1\f$.
             * 
             * d[0] -> number of units of the input layer.
             * d[L] -> number of units of the output layer.
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
             * With NeuralNetworkModel nn(2, 2, 1) a 2 layer network is created.
             * In the input layer there are 2 neurons and 1 in the output.
             * Using NeuralNetworkModel nn(3, 2, 4, 1) you add a hidden layer
             * with 4 neurons.
             * 
             * @param layers Number of layers, number of neurons on the input
             *               layer, number of neurons on the second layer...
             */
            NeuralNetworkModel(unsigned layers = 0 ...);

            /**
             * Creates a neural network with the layers and number of neurons
             * indicated in the vector.
             * Initialize the weights to a random values.
             * 
             * @param layers Number of neurons on the input layer, number of
             *               neurons on the second layer...
             */
            NeuralNetworkModel(const vector<unsigned>& layers);

            /**
             * Creates a neural network using the indicated weights matrices.
             * 
             * @param w Weights matrices to use.
             */
            NeuralNetworkModel(const vector<mat>& w);

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
            vector<mat> getWeights() const { return weights; }

            /**
             * Returns the number of layers of the neural network counting
             * the input and ouput layer.
             * 
             * @return Number of layers of the network.
             */
            unsigned getNumberLayers() const { return L + 1; }

            /**
             * Returns the number of neurons on layer 'layer'.
             * Layer number is not checked. Be sure that
             * layer < getNumberLayers().
             * 
             * @returns Number of layers of the layer 'layer'.
             */
            unsigned getNumberNeurons(unsigned layer) const { return d[layer]; }

            void read(istream& stream);

            void write(ostream& stream) const;
    };

}


#endif  // _HAPPY_ML_NEURAL_NETWORK_MODEL_H_
