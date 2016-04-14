
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

            vec eigVal;
            
            mat eigVec;

            mat covMat;

            int k;

            double minVar;


        public:

            /**
             * Creates a PCA extractor using the dataset data.
             * 
             * @param dataset Dataset from which the eigenvecs for the PCA
             *                will be extracted.
             * @param n Number of dimension to preserve or min mariance if it
             *          is a number between 0 and 1.
             */
            PCA(const DataSet& dataset, double n);

            /**
             * Creates a PCA extractor using the matrix data.
             * 
             * @param x Matrix from which the eigenvecs for the PCA will be
             *          extracted.
             * @param n Number of dimension to preserve or min mariance if it
             *          is a number between 0 and 1.
             */
            PCA(const mat& x, double n);

            ~PCA() {}


            /**
             * Returns the retained data variance of the PCA transformation.
             * It's a number between 0 and 1.
             * If you pass a min variance to the constructor remember that
             * the retained variance is >= the min variance choosen.
             * 
             * @return The retained data variance of the PCA transformation.
             */
            double getRetainedVariance() const { return minVar; }

            void apply(DataSet& dataset) const;

            void apply(mat& x) const;

            Input apply(const Input& input) const;
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_PCA_H_
