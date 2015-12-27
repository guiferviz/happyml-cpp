
#include "happyml/classifier.h"


namespace happyml
{

    void Classifier::saveBoundary(const string& filename, unsigned samples,
            double minx_1, double maxx_1, double minx_2, double maxx_2) const
    {
        ofstream myfile;
        myfile.open(filename.c_str());

        double step = 4 / 50.0;
        for (double i = -2; i <= 2; i += step)
        {
            vec x(2);
            x[0] = i;
            for (double j = -2; j <= 2; j += step)
            {
                x[1] = j;
                myfile << as_scalar(classify(x)) << ",";
            }
            myfile << "\n";
        }

        myfile.close();
    }

}
