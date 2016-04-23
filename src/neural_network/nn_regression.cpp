
#include "happyml/neural_network/nn_regression.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> // std::setprecision
#include <cstdarg>


namespace happyml
{

    NNRegression::NNRegression(unsigned layers ...) :
            NeuralNetworkModel(layers, false)
    {
        if (layers >= 2)
        {
            va_list args;
            va_start(args, layers);
    
            d[0] = va_arg(args, unsigned);
            for (unsigned l = 1; l <= L; ++l)
            {
                d[l] = va_arg(args, unsigned);
                weights[l] = mat(d[l - 1] + 1, d[l], fill::randn);
            }
    
            va_end(args);
        }
    }


    double NNRegression::train(const DataSet& dataset, unsigned iter,
            float learning_rate, float lambda)
    {
        //srand(time(0));
        float error_in = -1;
        const unsigned N = dataset.N;  // number of samples.s
        cout << colors::BLUE << "Training Neural Network (" << iter
                << " iterations)." << colors::RESET << endl;

        // Unit vector to join the inputs as a bias term.
        const vec u(1, fill::ones);
        for (unsigned i = 0; i < iter; ++i)
        {
            error_in = 0;
            mat g[L + 1];
            for (unsigned l = 1; l <= L; ++l) g[l] = 0 * weights[l];
            for (unsigned n = 0; n < N; ++n)
            {
                // Forward propagation.
                vec x[L + 1];
                vec s[L + 1];
                // Point plus bias term.
                x[0] = dataset.X.row(n).t();
                for (unsigned l = 1; l < L; ++l)
                {
                    // Compute the signal using last inputs and weights.
                    s[l] = weights[l].t() * x[l - 1];
                    // Apply soft threshold to the signal.
                    x[l] = tanh(s[l]);
                    // Add bias neuron.
                    x[l] = join_vert(u, x[l]);
                }
                // Last layer without activation function.
                x[L] = weights[L].t() * x[L - 1];

                // Backpropagation.
                vec delta[L + 1];
                // Delta last layer.
                delta[L] = x[L] - dataset.y.row(n).t();
                for (unsigned l = L - 1; l > 0; --l)
                {
                    // Sensitivities of the signal in layer l: 1 - x(l)^2
                    vec derivative = 1 - x[l] % x[l];
                    derivative = derivative(span(1, d[l])); // Extract bias term.
                    // Compute delta.
                    delta[l] = (weights[l + 1] * delta[l + 1]);
                    delta[l] = delta[l](span(1, d[l])); // Extract bias term.
                    delta[l] = derivative % delta[l];
                }

                // E_in.
                error_in += as_scalar(1.0f / N * (x[L] - dataset.y[n]).t() * (x[L] - dataset.y[n]));

                // Updating gradients.
                for (unsigned l = 1; l <= L; ++l)
                {
                    mat gn = x[l - 1] * delta[l].t();
                    g[l] = g[l] + 1.0f / N * gn;
                }
            }

            // Updating weights.
            for (unsigned l = 1; l <= L; ++l)
            {
                weights[l] = weights[l] * (1 - 2 * learning_rate * lambda / N)
                        - learning_rate * g[l];
            }
        }

        cout << colors::RED << "End of the training. Error " << setprecision(4)
                << error_in << colors::RESET << endl;

        return error_in;
    }

    double NNRegression::predict(const Input& input) const
    {
        // Unit vector to join the inputs as a bias term.
        const vec u(1, fill::ones);
        // Inputs plus bias term.
        vec x = input;
        // Forward propagation.
        for (unsigned l = 1; l < L; ++l)
        {
            // Compute the signal using last inputs and weights.
            vec s = weights[l].t() * x;
            // Apply soft threshold to the signal.
            s = tanh(s);
            // Add bias neuron if it isn't the last layer.
            x = (l == L) ? s : join_vert(u, s);
        }
        // Last layer with linear activation function.
        x = weights[L].t() * x;
        // Return the output vector.
        cout <<  x << endl;
        return as_scalar(x);
    }

    vec NNRegression::predictVec(const Input& input) const
    {
        // Unit vector to join the inputs as a bias term.
        const vec u(1, fill::ones);
        // Inputs plus bias term.
        vec x = input;
        // Forward propagation.
        for (unsigned l = 1; l < L; ++l)
        {
            // Compute the signal using last inputs and weights.
            vec s = weights[l].t() * x;
            // Apply soft threshold to the signal.
            s = tanh(s);
            // Add bias neuron if it isn't the last layer.
            x = (l == L) ? s : join_vert(u, s);
        }
        // Last layer with linear activation function.
        x = weights[L].t() * x;
        // Return the output vector.
        return x;
    }

    double NNRegression::error(const DataSet& dataset) const
    {
        double error_in = 0;
        // Unit vector to join the inputs as a bias term.
        const vec u(1, fill::ones);
        for (unsigned n = 0; n < dataset.N; ++n)
        {
            // Forward propagation.
            vec x[L + 1];
            vec s[L + 1];
            // Point plus bias term.
            x[0] = dataset.X.row(n).t();
            for (unsigned l = 1; l < L; ++l)
            {
                // Compute the signal using last inputs and weights.
                s[l] = weights[l].t() * x[l - 1];
                // Apply soft threshold to the signal.
                x[l] = tanh(s[l]);
                // Add bias neuron.
                x[l] = join_vert(u, x[l]);
            }
            // Last layer without activation function.
            x[L] = weights[L].t() * x[L - 1];

            // E_in.
            vec error = dataset.y.row(n).t() - x[L];
            error_in += 1.0f / dataset.N * sum(error % error);
        }

        return error_in;
    }
}
