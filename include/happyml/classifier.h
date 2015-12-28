
#ifndef _HAPPY_ML_CLASSIFIER_H_
#define _HAPPY_ML_CLASSIFIER_H_


#include "happyml/types.h"


namespace happyml
{

    /**
     * Abstract class that represent an algorithm that classifies an input
     * vector of features.
     */
    class Classifier
    {
        public:

            /**
             * Classifies an input vector.
             *
             * @param x An input vector.
             * 
             * @return Returns a real value corresponding with the
             *         classification done by the current classifier.
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

            /**
             * Saves the value of predicting the output of the classifier on the
             * rectangular area defined between (minx_1, minx_2) and
             * (maxx_1, maxx_2) points.
             * The CSV output file has the following structure:
             * 
             * \f$\\
             * minx_1,maxx_1,samples\\
             * minx_2,maxx_2,samples\\
             * h_{1\ 1},h_{1\ 2},\cdots,h_{1\ samples}\\
             * \ \vdots\ ,\ \vdots\ ,\cdots,\ \vdots\ \\
             * h_{samples\ 1},h_{samples\ 2},\cdots,h_{samples\ samples}
             * \f$
             * 
             * Use 'happyplot' command line tool to visualize the output.
             * 
             * @param filename Output filename.
             * @param samples Number of samples of each dimension.
             * @param minx_1 Start value of the first feature.
             * @param maxx_1 End value of the first feature.
             * @param minx_2 Start value of the second feature.
             * @param maxx_2 End value of the second feature.
             */
            virtual void saveBoundary(const string& filename, unsigned samples,
                    double minx_1, double maxx_1,
                    double minx_2, double maxx_2) const;

    };

}


#endif  // _HAPPY_ML_CLASSIFIER_H_
