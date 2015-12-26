
#ifndef _HAPPY_ML_UTILS_H_
#define _HAPPY_ML_UTILS_H_


#include <string>


using namespace std;


namespace happyml
{

    namespace colors
    {
        const string CYAN = "\e[46m";

        const string GREEN = "\e[32m";

        const string PINK = "\e[45m\e[37m";

        const string BLUE = "\e[44m\e[37m";

        const string RED = "\e[41m\e[37m";

        const string RESET = "\e[m";
    }

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
