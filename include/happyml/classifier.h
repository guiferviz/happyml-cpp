
#ifndef _HAPPY_ML_CLASSIFIER_H_
#define _HAPPY_ML_CLASSIFIER_H_


#include "happyml.h"


namespace happyml
{

    /**
     * Abstract class that represent an algorithm that classifies an input
     * vector of features.
     */
    class Classifier
    {
        
        /**
         * Classifies an input vector.
         *
         * @param input An input vector.
         * 
         * @return Returns a real value corresponding with the classification
         *         done by the current classifier.
         */
        virtual double classify(const Input& x) const = 0;


        /**
         * Compute the error of the classifier on the given dataset.
         * 
         * @param data Dataset with the correct output.
         * 
         * @return Error of classify the given dataset. It's in the
         *         interval \f$[0, 1]\f$.
         */
        virtual double error(const DataSet& dataset) const = 0;
        
    };

}


#endif  // _HAPPY_ML_CLASSIFIER_H_
