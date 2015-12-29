
#ifndef _HAPPY_ML_TRANSFORMER_H_
#define _HAPPY_ML_TRANSFORMER_H_


#include <vector>

#include "happyml/types.h"


namespace happyml
{

    /**
     * Class that applies non-linear transformations to an input or to a whole
     * dataset.
     */
    class Transformer
    {
        private:

            vector<unsigned> featuresPower;

            vector<double> powerPower;


        public:

            Transformer() {}
            
            ~Transformer() {}


            /**
             * Creates a new feature using the feature number \f$feature\f$
             * and raising it to the power of \f$power\f$.
             * 
             * @param feature Feature to raise.
             * @param power Exponent.
             */
            void addPower(unsigned feature, double power);

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
