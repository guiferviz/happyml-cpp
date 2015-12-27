
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
             * Dimension of the inputs vector in this dataset (\f$d\f$).
             * All the points has the same dimension.
             */
            unsigned d;

            /**
             * Number of pairs \f$(\mathbf{x}, y)\f$ in the dataset.
             * We denote it with \f$N\f$.
             */
            unsigned N;

            /**
             * Matrix with all the inputs.
             * \f$
             * \mathbf{X} = \begin{pmatrix}
             *      \mathbf{x}^{\rm T}_1 \\
             *      \mathbf{x}^{\rm T}_2 \\
             *      \vdots \\
             *      \mathbf{x}^{\rm T}_N
             * \end{pmatrix} = \begin{pmatrix}
             *      x_{10} & \cdots & x_{1d} \\
             *      x_{20} & \cdots & x_{2d} \\
             *      \vdots & \ddots & \vdots \\
             *      x_{N0} & \cdots & x_{Nd}
             * \end{pmatrix}
             * \f$
             */
            mat X;

            /**
             * Expected outputs.
             * \f$
             * \mathbf{y} = \begin{pmatrix}
             *      y_1 \\
             *      y_2 \\
             *      \vdots \\
             *      y_N
             * \end{pmatrix}
             * \f$
             */
            mat y;


            /**
             * Creates a generic collection of inputs and outputs.
             * 
             * @param dim Dimension \f$d\f$ of the inputs.
             * @param size Number of inputs (\f$N\f$) in the dataset.
             */
            DataSet(unsigned dim = 0, unsigned size = 0) : d(dim), N(size),
                    X(N, d + 1, fill::ones), y(N, 1, fill::zeros)
            {
            }


            /**
             * Creates a dataset from a CSV file.
             * The order of the file is:
             * 
             * \f$\\
             * x_{11},x_{12},\cdots,x_{1d},y_{1}\\
             * x_{21},x_{22},\cdots,x_{2d},y_{2}\\
             * \ \ \vdots\ \ ,\ \ \vdots\ \ ,\ \cdots\ ,\ \ \vdots\ \ ,\ \ \vdots\\
             * x_{N1},x_{N2},\cdots,x_{Nd},y_{N}
             * \f$
             */
            void read(istream& stream);

            void load(const string& filename);

            /**
             * Save a file with the format:
             * 
             * \f$\\
             * x_{11},x_{12},\cdots,x_{1d},y_{1}\\
             * x_{21},x_{22},\cdots,x_{2d},y_{2}\\
             * \ \ \vdots\ \ ,\ \ \vdots\ \ ,\ \cdots\ ,\ \ \vdots\ \ ,\ \ \vdots\\
             * x_{N1},x_{N2},\cdots,x_{Nd},y_{N}
             * \f$
             */
            void write(ostream& stream) const;
            
            void save(const string& filename) const;

    };
}


#endif  // _HAPPY_ML_DATASET_H_
