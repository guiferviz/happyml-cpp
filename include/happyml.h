
#ifndef _HAPPY_ML_H_
#define _HAPPY_ML_H_


#include <string>


using namespace std;


/**
 * HappyML library namespace.
 * All in this library is under this namespace.
 *
 * @author guiferviz
 */
namespace happyml
{

    /**
     * String with the library version.
     */
    const string version = HAPPY_ML_VERSION;


    /**
     * **Prints a greeting** to the standard output.
     * This library it's not only a **happy** library, it's also a **polite**
     * library :)
     */
    void greet();


    /**
     * Set of inputs features.
     * \f$
     * \mathbf{x} = \begin{pmatrix}
     *      x_0 \\
     *      x_1 \\
     *      \vdots \\
     *      x_d
     * \end{pmatrix}
     * \f$
     */
    typedef vec Input;


    /**
     * Generic collection of inputs and outputs.
     * We denote it with \f$\mathcal{D}\f$.
     */
    typedef struct {

        /**
         * Dimension of the inputs vector in this dataset (\f$d\f$).
         * All the points has the same dimension.
         */
        const unsigned d;

        /**
         * Number of pairs \f$(\mathbf{x}, y)\f$ in the dataset.
         * We denote it with \f$N\f$.
         */
        const unsigned N;

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
         * Expected output.
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
        DataSet(unsigned dim, unsigned size) : d(dim), N(size),
                X(d + 1, N, fill::ones), y(N, 1, fill::zero)
        {
        }

    } DataSet;

}


#endif // _HAPPY_ML_H_
