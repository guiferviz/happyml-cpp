
#include "happyml/logistic_regression/logistic_regression.h"

#include <iomanip>  // std::setprecision


namespace happyml
{

    LogisticRegression::LogisticRegression(unsigned d) : w(d + 1, fill::randn)
    {
    }

    LogisticRegression::LogisticRegression(const vec& weights) : w(weights)
    {
    }

    LogisticRegression::LogisticRegression(const LogisticRegression& l) : w(l.w)
    {
    }

    LogisticRegression::~LogisticRegression()
    {
        w.set_size(0);
    }


    double LogisticRegression::train(const DataSet& dataset, unsigned iter,
            double learning_rate)
    {
        cout << colors::BLUE << "Training Logistic Regression (" << iter
                << " loops)." << colors::RESET << endl;
        int i;
        for (i = 0; i < iter; ++i)
        {
            vec g(w.size(), fill::zeros);  // gradient vector.
            for (int j = 0; j < dataset.N; ++j)
            {
                g += dataset.y[j] * dataset.X.row(j).t() / as_scalar(1 + exp(
                        dataset.y[j] * w.t() * dataset.X.row(j).t()));
            }
            g *= - 1.0 / dataset.N;
            w = w - learning_rate * g;
            // TODO: compute error inside last for loop.
            // TODO: add best end condition.
            if (error(dataset) == 0) break;
        }
        double currentError = error(dataset);
        cout << colors::RED << "End of the training. Total iterations: " << i
                << ". Error " << setprecision(4) << currentError
                << colors::RESET << endl;
        return currentError;
    }

    double LogisticRegression::predict(const Input& x) const
    {
        float output = as_scalar(w.t() * x);

        return sigmoid(output);  // sigmoid function
    }

    double LogisticRegression::error(const DataSet& dataset) const
    {
        double currentError = 0;
        for (unsigned j = 0; j < dataset.N; ++j)
        {
            currentError += as_scalar(log(1 + exp(- dataset.y[j] * w.t()
                    * dataset.X.row(j).t())));
        }
        currentError /= dataset.N;

        return currentError;
    }

}
