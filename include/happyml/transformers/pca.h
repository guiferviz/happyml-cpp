
#ifndef _HAPPY_ML_TRANSFORMERS_PCA_H_
#define _HAPPY_ML_TRANSFORMERS_PCA_H_


#include "happyml/types.h"
#include "happyml/transformers/transformer.h"


namespace happyml
{

    /**
     * Dimensionality reduction using PCA.
     */
    class PCA : public Transformer
    {
        private:
        
            void init(const mat&);


        protected:

            rowvec meanVec;

            rowvec eigVec, eigValVec;

            int k;

            double minVar;


        public:

            /**
             * Creates a PCA extractor.
             * 
             * @param dataset Dataset from which it will be extracted the
             *                eigenvecs for the PCA.
             * @param n Number of dimension to preserve or min mariance if it
             *          is a number between 0 and 1.
             */
            PCA(const DataSet& dataset, double n);
            PCA(const mat& x);
            
            ~PCA() {}


            void apply(DataSet& dataset) const;

            void apply(mat& x) const;

            Input apply(const Input& input) const;
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_PCA_H_
