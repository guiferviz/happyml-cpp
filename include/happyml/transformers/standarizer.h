
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
    class Standarizer : public transforms::SimpleTransformer
    {
        protected:

            rowvec meanVec, stdVec;


            void init(const mat&);


        public:

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the mean
             *                and stddev that will be used when apply Z-Score.
             * //@param normY If true, it standarizes also the outputs.
             */
            Standarizer(const DataSet& dataset)
            {
                init(dataset.X.cols(1, dataset.X.n_cols - 1));
            }

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the given matrix.
             * 
             * @param x Matrix from which it will be extracted the mean and
             *          stddev vectors that will be used when apply Z-Score.
             */
            Standarizer(const mat& x)
            {
                init(x);
            }

            /**
             * Creates a standarizer that will use mean and stddev vectors.
             * 
             * @param mean Vector with the mean of each column.
             * @param stddev Vector with the stddev of each column.
             */
            Standarizer(vec mean, vec stddev)
            {
                meanVec =   mean;
                stdVec  = stddev;
            }
            
            ~Standarizer() {}


            using SimpleTransformer::apply;

            void apply(mat& x) const;
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_
