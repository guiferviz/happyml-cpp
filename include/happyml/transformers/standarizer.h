
#ifndef _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_
#define _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_


#include "happyml/types.h"
#include "happyml/transformers/transformer.h"


namespace happyml
{

    /**
     * Applies Z-Score transformation:
     * x' = x - mean(x) / stddev(x)
     */
    class Standarizer : public Transformer
    {
        private:
        
            void init(const mat&);


        protected:

            rowvec meanVec, stdVec;


        public:

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the mean
             *                and stddev that will be used when apply Z-Score.
             * //@param normY If true, it standarizes also the outputs.
             */
            Standarizer(const DataSet& dataset);

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the given matrix.
             * 
             * @param x Matrix from which it will be extracted the mean and
             *          stddev vectors that will be used when apply Z-Score.
             */
            Standarizer(const mat& x);

            /**
             * Creates a standarizer that will use mean and stddev vectors.
             * 
             * @param mean Vector with the mean of each column.
             * @param stddev Vector with the stddev of each column.
             */
            Standarizer(vec mean, vec stddev);
            
            ~Standarizer() {}


            void apply(DataSet& dataset) const;

            void apply(mat& x) const;

            Input apply(const Input& input) const;
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_
