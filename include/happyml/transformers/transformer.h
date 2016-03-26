
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
        public:

            Transformer() {}
            
            ~Transformer() {}


            /**
             * Applies all the transformations at the given dataset.
             * 
             * @param dataset Dataset to transform.
             */
            virtual void apply(DataSet& dataset) {};

            /**
             * Applies all the transformations at the given input.
             * 
             * @param input Input to transform.
             * 
             * @return A transformated version of the input.
             */
            virtual Input apply(const Input& input) const {};

    };


    /**
     * Transformer that applies a collection of transformers to a given input
     * or dataset.
     */
    class TransformerCollection : public Transformer
    {
        protected:

            vector<Transformer> transformers;


        public:

            TransformerCollection() {}

            ~TransformerCollection() {}


            /**
             * Applies all the transformers in the order that were added to
             * the collection.
             * 
             * @param dataset Dataset to transform.
             */
            void apply(DataSet& dataset);

            /**
             * Applies all the transformers in the order that were added to
             * the collection.
             * 
             * @param input Input to transform.
             * 
             * @return A transformated version of the input.
             */
            Input apply(const Input& input) const;

            /**
             * Adds a new Transformer to the collection that will be executed
             * when the apply's methods it will be called.
             * 
             * @param t Transformer to add to the collection.
             */
            void add(const Transformer& t);
    };
}


#endif  // _HAPPY_ML_TRANSFORMER_H_
