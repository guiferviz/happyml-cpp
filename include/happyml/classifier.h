
#ifndef _HAPPY_ML_CLASSIFIER_H_
#define _HAPPY_ML_CLASSIFIER_H_


#include "happyml/types.h"
#include "happyml/transformer.h"


namespace happyml
{

    /**
     * Abstract class that represent an algorithm that predict an output or
     * classifies an input vector.
     */
    class Predictor
    {
        public:

            /**
             * Predict an output from an input vector.
             *
             * @param x An input vector.
             * 
             * @return Returns a real value corresponding with the
             *         prediction done by the current predictor.
             */
            virtual double predict(const Input& x) const = 0;

            /**
             * Compute the error of the predictor in the given output.
             * By default it computes the square diff.
             * 
             * @param h The value predicted by the predictor (hypothesis).
             * @param y Correct output.
             * 
             * @return Error of the predicted value comparate to y.
             */
            virtual double error(double h, double y) const;

            /**
             * Compute the error of the predictor on the given dataset.
             * 
             * @param data Dataset with the correct output.
             * 
             * @return Error of predicting the output of the given dataset.
             */
            virtual double error(const DataSet& dataset) const;

            /**
             * Saves the value of predicting the output of the predicter on
             * the rectangular area defined between \f$(minx_1, minx_2)\f$ and
             * \f$(maxx_1, maxx_2)\f$ points.
             * The CSV output file has the following structure:
             * 
             * \f$\\
             * minx_1,maxx_1,samples_1\\
             * minx_2,maxx_2,samples_2\\
             * h_{1\ 1},h_{1\ 2},\cdots,h_{1\ samples_1}\\
             * \ \vdots\ ,\ \vdots\ ,\cdots,\ \vdots\ \\
             * h_{samples\ 1},h_{samples\ 2},\cdots,h_{samples_2\ samples_1}
             * \f$
             * 
             * Use 'happyplot' command line tool to visualize the output.
             * 
             * @param filename Output filename.
             * @param minx_1 Start value of the first feature.
             * @param maxx_1 End value of the first feature.
             * @param samples_1 Number of samples of the first feature.
             * @param minx_2 Start value of the second feature.
             * @param maxx_2 End value of the second feature.
             * @param samples_2 Number of samples of the second feature.
             * @param t Transformer that transform the inputs to predict.
             */
            virtual void saveSampling(const string& filename,
                    double minx_1, double maxx_1, unsigned samples_1,
                    double minx_2, double maxx_2, unsigned samples_2,
                    const Transformer& t) const;

            /**
             * Saves the value of predicting the output of the predicter in
             * the segment \f$[minx, maxx]\f$.
             * The CSV output file has the following structure:
             * 
             * \f$\\
             * minx,maxx,samples\\
             * h_{1},h_{2},\cdots,h_{samples}\\
             * \f$
             * 
             * Use 'happyplot' command line tool to visualize the output.
             * 
             * @param filename Output filename.
             * @param minx_1 Start value of the first feature.
             * @param maxx_1 End value of the first feature.
             * @param samples_1 Number of samples of the first feature.
             * @param t Transformer that transform the inputs to predict.
             */
            virtual void saveSampling(const string& filename,
                    double minx, double maxx, unsigned samples,
                    const Transformer& t) const;
    };

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

            virtual void saveBoundary(const string& filename, unsigned samples,
                    double minx_1, double maxx_1,
                    double minx_2, double maxx_2,
                    const Transformer& t) const;
    };

}


#endif  // _HAPPY_ML_CLASSIFIER_H_
