
#ifndef _HAPPY_ML_NN_REGRESSION_H_
#define _HAPPY_ML_NN_REGRESSION_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"
#include "happyml/neural_network/neural_network_model.h"


namespace happyml
{

    class NNRegression : public NeuralNetworkModel
    {
        public:

            NNRegression(unsigned layers ...);

            NNRegression(const vector<unsigned>& layers) : NeuralNetworkModel(layers) {}

            NNRegression(const vector<mat> w) : NeuralNetworkModel(w) {}

            NNRegression(const NNRegression& nn) : NeuralNetworkModel(nn) {}

            ~NNRegression() {};

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
