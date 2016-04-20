
#include "happyml/svm/svm_linear.h"
#include "happyml/utils.h"


namespace happyml
{

    double SVMLinear::train(const DataSet& dataset, double C, unsigned iter,
            double tolerance)
    {
        double currentError = SVM::train(dataset, C, iter, tolerance);
        
        w = ((alphas % dataset.y).t() * dataset.X).t();
        w[0] = b;

        return currentError;
    }

    double SVMLinear::predict(const Input& input) const
    {
        // Bias term is included on weights.
        double output = as_scalar(w.t() * input);
        
        return sgn(output);
    }

    double SVMLinear::kernel(vec x1, vec x2) const
    {
        return as_scalar(x1.t() * x2);
    }

    void SVMLinear::read(istream& stream)
    {
        SVM::read(stream);
        
        uvec idx = find(alphas > 0);
        w = ((alphas(idx) % sv.y).t() * sv.X).t();
        w[0] = b;
    }

}
