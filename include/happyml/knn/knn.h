
#ifndef _HAPPY_ML_KNN_H_
#define _HAPPY_ML_KNN_H_


#include "happyml/types.h"
#include "happyml/utils.h"
#include "happyml/predictor.h"


using namespace arma;


namespace happyml
{

    class KNN : public Classifier
    {
        private:

            /**
             * Training set.
             */
            const DataSet* dataset;

            int k;


        public:

            /**
             * Creates a KNN classifier that uses the indicated training set.
             * 
             * @param d Training set used to compute distances.
             */
            KNN(const DataSet& d, int k = 1) { dataset = &d; this->k = k; }

            KNN(const KNN& knn) { dataset = knn.dataset; k = knn.k; }


            /**
             * Classifies an input vector.
             *
             * @return +1 or -1.
             */
            double predict(const Input& x) const;
            
            void setK(int k) { this->k = k; }
            
            int getK() { return k; }
    };

}


#endif  // _HAPPY_ML_KNN_H_
