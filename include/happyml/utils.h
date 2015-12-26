
#ifndef _HAPPY_ML_UTILS_H_
#define _HAPPY_ML_UTILS_H_


namespace happyml
{

    /**
     * Default sgn function.
     * \f$
     * \operatorname {sgn}(x) := {\begin{cases}
     *      -1 & {\text{if }} x < 0, \\
     *      1  & {\text{if }} x \geq 0.
     * \end{cases}}
     * \f$
     * 
     * @param x Input number.
     * 
     * @return Sign of x.
     */
    int sgn(double x);

}


#endif  // _HAPPY_ML_UTILS_H_
