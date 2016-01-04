
#ifndef _HAPPY_ML_LINEAR_MODEL_H_
#define _HAPPY_ML_LINEAR_MODEL_H_


#include <armadillo>


using namespace arma;


namespace happyml
{

    /**
     * Hypothesis of the form \f$w_0 \cdot x_0 + w_1 \cdot x_1 + \cdots + w_d
     * \cdot x_d\f$. In other words, each input feature has a weight asociated.
     * 
     * This class contains a protected weight vector and a public getter.
     */
    class LinearModel
    {
        protected:

            /**
             * Vector of weights.
             */
            vec w;

        public:

            /**
             * Creates a linear model with the indicated input size.
             * 
             * @param d Dimension \f$d\f$ of the input feature vectors.
             */
            LinearModel(unsigned d = 0) : w(d + 1, fill::zeros) {}

            /**
             * Creates a linear model with the indicated weights.
             * 
             * @param weights Weight vector with \f$d + 1\f$ dimensions.
             */
            LinearModel(const vec& weights) : w(weights) {}

            /**
             * Creates a linear model from the weights of another linear model.
             * 
             * @param lm Linear model from which weights are copied.
             */
            LinearModel(const LinearModel& lm) : w(lm.w) {}

            /**
             * Destroys the linear model (sets the weights size to \f$0\f$).
             */
            ~LinearModel() { w.set_size(0); }


            /**
             * Get a copy of the model weights.
             * 
             * @return Copy of the model weights.
             */
            vec getWeights() const { return w; }
    };

}


#endif  // _HAPPY_ML_LINEAR_MODEL_H_
