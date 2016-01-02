
#include "happyml/neural_network/neural_network.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> // std::setprecision
#include <cstdarg>


namespace happyml
{

    NeuralNetwork::NeuralNetwork(unsigned layers ...) :
            L(layers - 1), weights(layers), d(layers)
    {
        va_list args;
        va_start(args, layers);

        d[0] = va_arg(args, unsigned);
        for (unsigned l = 1; l <= L; ++l)
        {
            d[l] = va_arg(args, unsigned);
            weights[l] = mat(d[l - 1] + 1, d[l], fill::randn);
        }

        /* DELETE
        weights[1](0, 0) = 0.1;
        weights[1](0, 1) = 0.2;
        weights[1](1, 0) = 0.3;
        weights[1](1, 1) = 0.4;
        weights[2][0] = 0.2;
        weights[2][1] = 1;
        weights[2][2] = -3;
        weights[3][0] = 1;
        weights[3][1] = 2; */
        //for (unsigned l = 1; l <= L; ++l)
        //{
        //    cout << "Initial w(" << l << ")" << endl << weights[l] << endl;
        //}
        // END DELETE

        va_end(args);
    }

    NeuralNetwork::NeuralNetwork(const NeuralNetwork& p)
    {
        // TODO
    }

    NeuralNetwork::~NeuralNetwork()
    {
        // TODO
    }


    double NeuralNetwork::train(const DataSet& dataset, unsigned iter,
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
                for (unsigned l = 1; l <= L; ++l)
                {
                    // Compute the signal using last inputs and weights.
                    s[l] = weights[l].t() * x[l - 1];
                    // Apply soft threshold to the signal.
                    x[l] = tanh(s[l]);
                    // Add bias neuron if it isn't the last layer.
                    if (l != L) x[l] = join_vert(u, x[l]);
                }

                // Backpropagation.
                vec delta[L + 1];
                // Delta last layer.
                delta[L] = 1 - x[L] % x[L];
                //cout << delta[L] << endl;
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

                // Ein.
                error_in += as_scalar(1.0f / N * (x[L] - dataset.y[n]) * (x[L] - dataset.y[n]));

                // Updating gradients.
                for (unsigned l = 1; l <= L; ++l)
                {
                    // FIXME: this works only with one output neuron.
                    mat gn = 2 * (as_scalar(x[L]) - dataset.y[n])
                            * x[l - 1] * delta[l].t();
                    g[l] = g[l] + 1.0f / N * gn;
                }
            }

            // Updating weights.
            for (unsigned l = 1; l <= L; ++l)
            {
                //cout << "g(" << l << ")" << endl << g[l] << endl;
                weights[l] = weights[l] * (1 - 2 * learning_rate * lambda / N)
                        - learning_rate * g[l];
            }

            //cout << error_in << ",";
        }

        cout << colors::RED << "End of the training. Error " << setprecision(4)
                << error_in << colors::RESET << endl;

        return error_in;
    }

    double NeuralNetwork::predict(const Input& input) const
    {
        // Unit vector to join the inputs as a bias term.
        const vec u(1, fill::ones);
        // Inputs plus bias term.
        vec x = input;
        // Forward propagation.
        for (unsigned l = 1; l <= L; ++l)
        {
            // Compute the signal using last inputs and weights.
            vec s = weights[l].t() * x;
            // Apply soft threshold to the signal.
            s = tanh(s);
            // Add bias neuron if it isn't the last layer.
            x = (l == L) ? s : join_vert(u, s);
        }
        // Return the output vector.
        return as_scalar(x);
    }

}
