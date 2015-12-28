
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

        // Compute the boundary matrix.
        mat boundary(samples, samples);
        Input x(3);
        x[0] = 1;
        double x_1 = minx_1;
        for (unsigned i = 0; i < samples; ++i, x_1 += stepx_1)
        {
            x[1] = x_1;
            double x_2  = minx_2;
            for (unsigned j = samples - 1; j < samples; --j, x_2 += stepx_2)
            {
                x[2] = x_2;
                boundary(j, i) = classify(x);
            }
        }
        boundary.save(file, csv_ascii);
        file.close();
    }

}
