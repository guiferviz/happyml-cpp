
#ifndef _HAPPY_ML_DATASET_H_
#define _HAPPY_ML_DATASET_H_


#include <armadillo>

#include "happyml/serializable.h"


using namespace arma;


namespace happyml
{

    /**
     * Generic collection of inputs and outputs.
     * We denote it with \f$\mathcal{D}\f$.
     */
    class DataSet : public Serializable
    {
        public:

            /**
             * Dimension of the inputs vectors of this dataset (\f$d\f$).
             * All the points has the same dimension.
             */
            unsigned d;

            /**
             * Number of pairs \f$(\mathbf{x}, y)\f$ in the dataset.
             * We denote it with \f$N\f$.
             */
            unsigned N;

            /**
             * Number of outputs by sample.
             */
            unsigned k;

            /**
             * Matrix with all the inputs.
             * \f$
             * \mathbf{X} = \begin{pmatrix}
             *      \mathbf{x}^{\rm T}_0 \\
             *      \mathbf{x}^{\rm T}_1 \\
             *      \vdots \\
             *      \mathbf{x}^{\rm T}_{N - 1}
             * \end{pmatrix} = \begin{pmatrix}
             *      x_{00} & \cdots & x_{0d} \\
             *      x_{10} & \cdots & x_{1d} \\
             *      \vdots & \ddots & \vdots \\
             *      x_{(N-1)0} & \cdots & x_{(N-1)d}
             * \end{pmatrix}
             * \f$
             */
            mat X;

            /**
             * Expected outputs.
             * \f$
             * \mathbf{y} = \begin{pmatrix}
             *      y_0 \\
             *      y_1 \\
             *      \vdots \\
             *      y_{N - 1}
             * \end{pmatrix}
             * \f$
             */
            mat y;


            /**
             * Creates a generic collection of inputs and outputs.
             * 
             * @param dim Dimension \f$d\f$ of the inputs.
             * @param size Number of inputs (\f$N\f$) in the dataset.
             * @param output Number of tail columns to be used
             */
            DataSet(unsigned dim = 0, unsigned size = 0, unsigned outputs = 1) :
                    d(dim), N(size), k(outputs), X(N, d + 1, fill::ones),
                    y(N, outputs, fill::zeros)
            {
            }


            /**
             * Creates a dataset from a text input stream with the following
             * format:
             * 
             * \f$\\
             * x_{01},x_{02},\cdots,x_{0d},y_{0}\\
             * x_{11},x_{12},\cdots,x_{1d},y_{1}\\
             * \ \ \vdots\ \ ,\ \ \vdots\ \ ,\ \cdots\ ,\ \ \vdots\ \ ,\ \ \vdots\\
             * x_{(N-1)1},x_{(N-1)2},\cdots,x_{(N-1)d},y_{(N-1)}
             * \f$
             */
            void read(istream& stream);
            void read(istream& stream, int n_outputs);
            
            using Serializable::load;
            void load(const string& filename, int n_outputs);
            void load(const string& filename, bool one_hot);

            /**
             * Write to an output stream the next data:
             * 
             * \f$\\
             * x_{01},x_{02},\cdots,x_{0d},y_{0}\\
             * x_{11},x_{12},\cdots,x_{1d},y_{1}\\
             * \ \ \vdots\ \ ,\ \ \vdots\ \ ,\ \cdots\ ,\ \ \vdots\ \ ,\ \ \vdots\\
             * x_{(N-1)1},x_{(N-1)2},\cdots,x_{(N-1)d},y_{(N-1)}
             * \f$
             */
            void write(ostream& stream) const;

            void shuffle();
    };
}


#endif  // _HAPPY_ML_DATASET_H_
