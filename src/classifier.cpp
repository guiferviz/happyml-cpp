
#include "happyml/classifier.h"

#include "happyml/types.h"


namespace happyml
{

    void Classifier::saveBoundary(const string& filename, unsigned samples,
            double minx_1, double maxx_1, double minx_2, double maxx_2) const
    {
        ofstream file;
        file.open(filename.c_str());
        
        // Write headers.
        file << minx_1 << "," << maxx_1 << "," << samples << "\n";
        file << minx_2 << "," << maxx_2 << "," << samples << "\n";

        // Compute distance between samples.
        const double stepx_1 = (maxx_1 - minx_1) / (samples - 1);
        const double stepx_2 = (maxx_2 - minx_2) / (samples - 1);
        
        // Avoid decimal errors.
        maxx_1 += stepx_1 / 2;
        maxx_2 += stepx_2 / 2;

        // Compute the matrix
        Input x(3);
        x[0] = 1;
        for (double i = minx_1; i <= maxx_1; i += stepx_1)
        {
            x[1] = i;  x[2] = minx_2;
            file << classify(x);
            for (double j = minx_2 + stepx_2; j <= maxx_2; j += stepx_2)
            {
                x[2] = j;
                file << "," << classify(x);
            }
            file << "\n";
        }

        file.close();
    }

}
