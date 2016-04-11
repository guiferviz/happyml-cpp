
#ifndef _HAPPY_ML_NEURAL_NETWORK_H_
#define _HAPPY_ML_NEURAL_NETWORK_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"
#include "happyml/neural_network/neural_network_model.h"

#include <utility>  // forward


namespace happyml
{

    class NeuralNetwork : public Classifier, public NeuralNetworkModel
    {

        public:

            NeuralNetwork(unsigned layers = 0 ...);

            NeuralNetwork(const vector<unsigned>& layers) : NeuralNetworkModel(layers) {}

            NeuralNetwork(const vector<mat> w) : NeuralNetworkModel(w) {}

            NeuralNetwork(const NeuralNetwork& nn) : NeuralNetworkModel(nn) {}

            ~NeuralNetwork() {};


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
    };

}


#endif // _HAPPY_ML_NEURAL_NETWORK_H_
