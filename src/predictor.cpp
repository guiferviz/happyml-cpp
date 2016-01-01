
#include "happyml/predictor.h"


namespace happyml
{

    void Predictor::saveSampling(const string& filename,
            double minx_1, double maxx_1, unsigned samples_1,
            double minx_2, double maxx_2, unsigned samples_2,
            const Transformer& t) const
    {
        ofstream file;
        file.open(filename.c_str());
        
        // Write headers.
        file << minx_1 << "," << maxx_1 << "," << samples_1 << "\n";
        file << minx_2 << "," << maxx_2 << "," << samples_2 << "\n";

        // Compute distance between samples.
        const double stepx_1 = (maxx_1 - minx_1) / (samples_1 - 1);
        const double stepx_2 = (maxx_2 - minx_2) / (samples_2 - 1);

        // Compute the boundary matrix.
        mat boundary(samples_2, samples_1);
        Input x(3);
        x[0] = 1;
        double x_1 = minx_1;
        for (unsigned i = 0; i < samples_1; ++i, x_1 += stepx_1)
        {
            x[1] = x_1;
            double x_2  = minx_2;
            for (unsigned j = samples_2 - 1; j < samples_2; --j, x_2 += stepx_2)
            {
                x[2] = x_2;
                boundary(j, i) = predict(x);
            }
        }
        boundary.save(file, csv_ascii);
        file.close();
    }

}
