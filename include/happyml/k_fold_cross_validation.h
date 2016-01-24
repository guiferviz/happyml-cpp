
#ifndef _HAPPY_ML_K_FOLD_CROSS_VALIDATION_H_
#define _HAPPY_ML_K_FOLD_CROSS_VALIDATION_H_


#include <map>

#include "happyml/types.h"
#include "happyml/predictor.h"


namespace happyml
{

    /**
     * 
     */
    class TrainingProcess
    {

        public:

            virtual void run(const DataSet& training, const DataSet& cv) = 0;

    };


    /**
     * 
     */
    class KFoldCrossValidation
    {

        private:

            KFoldCrossValidation() {}


        public:

            /**
             * 
             * 
             * @param dataset Dataset to devide.
             * @param n Number of divisions.
             * @param process Training process to repeat for each fold.
             */
            static void apply(const DataSet& dataset, int n,
                    TrainingProcess& process);

    };

}


#endif  // _HAPPY_ML_K_FOLD_CROSS_VALIDATION_H_
