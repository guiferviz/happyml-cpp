
#ifndef _HAPPY_ML_TRANSFORMER_H_
#define _HAPPY_ML_TRANSFORMER_H_


#include <queue>
#include <vector>

#include "happyml/types.h"


namespace happyml
{

    /**
     * Class that applies linear and non-linear transformations to an input or
     * to a whole dataset.
     */
    class Transformer
    {
        private:

            enum Actions
            {
                ADD,
                POW,
                MUL
            };

            vector<Actions> actions;

            vector<unsigned> features;

            vector<double> param;

            vector<bool> creates;
            
            deque<unsigned> removeOrder;

            /*
             * Applies the actions in the given order to a matrix.
             */
            void applyToMatrix(mat&) const;

            /*
             * Applies the action and add the result as a new feature.
             */
            void applyCreateNew(mat&, unsigned actionIndex) const;

            /*
             * Applies the action at the existing feature.
             */
            void applyNoCreateNew(mat& x, unsigned actionIndex) const;

        public:

            Transformer() {}
            
            ~Transformer() {}


            /**
             * Raise the feature number \f$feature\f$ to the power of
             * \f$power\f$.
             * 
             * @param feature Feature to raise.
             * @param power Exponent.
             * @param create_new Create a new feature or not.
             */
            void addPower(unsigned feature, double power, bool create_new = true);

            /**
             * Adds (or substract) a value to the indicated feature. Doesn't
             * add a new feature.
             * 
             * @param feature \f$n\f$ will be added to this feature number.
             * @param n Number to be added.
             * @param create_new Create a new feature or not.
             */
            void addAddition(unsigned feature, double n, bool create_new = false);

            /**
             * Multiply (or divide) the indicated feature by \f$n\f$. Doesn't
             * add a new feature.
             * 
             * @param feature \f$n\f$ will be added to this feature number.
             * @param n Number to be added.
             * @param create_new Create a new feature or not.
             */
            void addProduct(unsigned feature, double n, bool create_new = false);

            /**
             * Deletes a feature.
             * 
             * @param feature Feature that will be removed.
             */
            void remove(unsigned feature);

            /**
             * Applies all the transformations in the given dataset.
             * 
             * @param dataset Dataset to transform.
             */
            void apply(DataSet& dataset) const;

            /**
             * Applies all the transformations in the given input.
             * 
             * @param input Input to transform.
             * 
             * @return A transformated version of the input.
             */
            Input apply(const Input& input) const;

    };
}


#endif  // _HAPPY_ML_TRANSFORMER_H_
