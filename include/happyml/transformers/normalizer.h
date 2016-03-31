
#ifndef _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_
#define _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_


#include "happyml/types.h"
#include "happyml/transformers/transformer.h"


namespace happyml
{

    /**
     * Normalizes a dataset using feature scaling:
     * x' = x - min(x) / (max(x) - min(x))
     */
    class Normalizer : public Transformer
    {
        private:
        
            void init(const mat&);


        protected:

            rowvec minx, maxx, rangex;

            rowvec miny, maxy;


        public:

            /**
             * Creates a normalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the min
             *                and max that will be use when apply normalization.
             * //@param normY If true, it normalizes also the outputs.
             */
            Normalizer(const DataSet& dataset);
            Normalizer(const mat& x);

            /**
             * Creates a normalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the min
             *                and max that will be use when apply normalization.
             */
            Normalizer(const vec& min, const vec& max);
            
            ~Normalizer() {}


            void apply(DataSet& dataset) const;

            void apply(mat& x) const;

            Input apply(const Input& input) const;
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_
