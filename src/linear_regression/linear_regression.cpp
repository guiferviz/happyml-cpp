
#include "happyml/linear_regression/linear_regression.h"

#include <iomanip>  // std::setprecision


namespace happyml
{

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

    double LinearRegression::train(const DataSet& dataset, double lambda)
    {
        cout << colors::BLUE << "Training Logistic Regression"
                << colors::RESET << endl;

        mat I(dataset.N, dataset.N, fill::eye); I(0, 0) = 0;
        w = inv(dataset.X.t() * dataset.X + lambda * I) * dataset.X.t() * dataset.y; 

        double currentError = error(dataset);
        cout << colors::RED << "End of the training. Error " << setprecision(4)
                << currentError << colors::RESET << endl;

        return currentError;
    }

    double LinearRegression::predict(const Input& x) const
    {
        return as_scalar(w.t() * x);
    }

    double LinearRegression::error(const DataSet& dataset) const
    {
        vec currentError = dataset.X * w - dataset.y;
        currentError %= currentError;  // Error to the square.

        return 1.0 / dataset.N * sum(currentError);
    }

}
