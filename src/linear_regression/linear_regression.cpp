
#include "happyml/linear_regression/linear_regression.h"

#include <iomanip>  // std::setprecision


namespace happyml
{

    LinearRegression::LinearRegression(unsigned d) : w(d + 1)
    {
    }

    LinearRegression::LinearRegression(const vec& weights) : w(weights)
    {
    }

    LinearRegression::LinearRegression(const LinearRegression& l) : w(l.w)
    {
    }

    LinearRegression::~LinearRegression()
    {
        w.set_size(0);
    }


    double LinearRegression::train(const DataSet& dataset)
    {
        cout << colors::BLUE << "Training Logistic Regression"
                << colors::RESET << endl;

        w = pinv(dataset.X) * dataset.y; 

        double currentError = error(dataset);
        cout << colors::RED << "End of the training. Error " << setprecision(4)
                << currentError << colors::RESET << endl;

        return currentError;
    }

    double LinearRegression::classify(const Input& x) const
    {
        return as_scalar(w.t() * x);
    }

    double LinearRegression::error(const DataSet& dataset) const
    {
        vec currentError = dataset.X * w - dataset.y;
        currentError %= currentError;  // Error to the square.

        return 1.0 / dataset.N * sum(currentError);
    }

    void LinearRegression::saveLine(const string& filename, double minx,
            double maxx, unsigned samples) const
    {
        ofstream file;
        file.open(filename.c_str());
        
        // Write headers.
        file << minx << "," << maxx << "," << samples << "\n";

        // Compute distance between samples.
        const double step = (maxx - minx) / (samples - 1);

        // Compute the line vector.
        rowvec line(samples);
        Input input(2);
        input[0] = 1;
        double x = minx;
        for (unsigned i = 0; i < samples; ++i, x += step)
        {
            input[1] = x;
            line(i) = classify(input);
        }
        line.save(file, csv_ascii);
        file.close();
    }
    
    void LinearRegression::saveLine(const string& filename, double minx,
            double maxx, unsigned samples, const Transformer& t) const
    {
        ofstream file;
        file.open(filename.c_str());
        
        // Write headers.
        file << minx << "," << maxx << "," << samples << "\n";

        // Compute distance between samples.
        const double step = (maxx - minx) / (samples - 1);

        // Compute the line vector.
        rowvec line(samples);
        Input input(2);
        input[0] = 1;
        double x = minx;
        for (unsigned i = 0; i < samples; ++i, x += step)
        {
            input[1] = x;
            line(i) = classify(t.apply(input));
        }
        line.save(file, csv_ascii);
        file.close();
    }

}
