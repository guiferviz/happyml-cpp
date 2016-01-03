
#ifndef _HAPPY_ML_HAPPYTOOLS_H_
#define _HAPPY_ML_HAPPYTOOLS_H_


#include <map>

#include "happyml/types.h"
#include "happyml/predictor.h"
#include "happyml/linear_model.h"


namespace happyml
{

    namespace tools
    {

        typedef map<string, string> dictionary;

        /**
         * Creates a DOT (graph description language) file of the linear model.
         * 
         * @param lm Linear model to represent.
         * @param filename Name of the file where the DOT info will be saved.
         * @param latex True if use latex in the labels.
         */
        void modelToDot(const LinearModel& lm, const string& filename,
                bool latex = false);

        void modelToDot(const LinearModel& lm, ostream& out, bool latex = false);

        //void modelToDot(const NeuralNetwork& nn, bool latex = false);

        string substitute(const string& in, const dictionary& subst);
    }

}


#endif  // _HAPPY_ML_HAPPYTOOLS_H_
