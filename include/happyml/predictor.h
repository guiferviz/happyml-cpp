
#ifndef _HAPPY_ML_PREDICTOR_H_
#define _HAPPY_ML_PREDICTOR_H_


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
             * Compute the error of the predictor in a given input.
             * By default it computes the square diff.
             * 
             * @param x The input vector.
             * @param y Correct output.
             * 
             * @return Error of the predicted value comparate to y.
             */
            virtual double error(const Input& x, double y) const;

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
             *          By default a void transformed is used.
             */
            virtual void saveSampling(const string& filename,
                    double minx_1, double maxx_1, unsigned samples_1,
                    double minx_2, double maxx_2, unsigned samples_2,
                    const Transformer& t = Transformer()) const;

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
             * @param minx Start value of the first feature.
             * @param maxx End value of the first feature.
             * @param samples Number of samples of the first feature.
             * @param t Transformer that transform the inputs to predict.
             *          By default a void transformed is used.
             */
            virtual void saveSampling(const string& filename,
                    double minx, double maxx, unsigned samples,
                    const Transformer& t = Transformer()) const;
    };

    /**
     * Abstract class that represent an algorithm that classifies
     * an input in classes.
     */
    class Classifier : public Predictor {};

}


#endif  // _HAPPY_ML_PREDICTOR_H_
