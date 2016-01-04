
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

        /**
         * Dictionary containing variables names as keys and his values.
         * 
         * @see substitute
         */
        typedef map<string, string> dictionary;

        /**
         * Creates a DOT (graph description language) file of the linear model.
         * 
         * You can generate a png image of a file with the next command:
         * 
         * <code>
         * dot -Tpng -o<OUTPUT-FILE.PNG> -Gsize=9,15\\! -Gdpi=100
         * <INPUT-FILE.DOT>
         * </code>
         * 
         * The DOT file can also be generated for Latex (formulas can be
         * included in nodes or edges names). For generating a
         * DOT-Latex files use dot2tex. First generate the tex file from your
         * DOT file and then compile it with pdflatex:
         * 
         * <code>
         * dot2tex <MODEL.DOT> > file.tex<br />
         * pdflatex file.tex
         * </code>
         * 
         * @param lm Linear model to represent.
         * @param filename Name of the file where the DOT info will be saved.
         * @param latex True to use latex in the labels. False by default.
         */
        void modelToDot(const LinearModel& lm, const string& filename,
                bool latex = false);

        /**
         * @see modelToDot(const LinearModel&, const string&, bool)
         */
        void modelToDot(const LinearModel& lm, ostream& out, bool latex = false);

        //void modelToDot(const NeuralNetwork& nn, bool latex = false);

        /**
         * Returns an new string created by substituting vars in the input
         * string. The sintax for the vars in the 'in' string is {{var_name}}.
         * 
         * Thanks Potatoswatter (StackOverflow user) for the code of this
         * function.
         * 
         * @param in Input string with vars names to substitute.
         * @param dic Dictionary with variables names as keys and another
         *            string as value.
         * 
         * @return A new string with the variables names substituted by its
         *         values.
         * 
         * @see dictionary
         */
        string substitute(const string& in, const dictionary& dic);
    }

}


#endif  // _HAPPY_ML_HAPPYTOOLS_H_
