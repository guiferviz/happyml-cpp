
#include "happyml/perceptron/perceptron.h"

#include <iomanip>  // std::setprecision


using namespace std;


namespace happyml
{

    Perceptron::Perceptron(int d) : w(d + 1)
    {
    }

    Perceptron::Perceptron(const vec& weights) : w(weights)
    {
    }

    Perceptron::Perceptron(const Perceptron& p) : w(p.w)
    {
    }

    Perceptron::~Perceptron()
    {
    }


    double Perceptron::train(const DataSet& data, unsigned iter)
    {
        vec bestW;
        float bestError = 1.0f;

        cout << "Training Perceptron (" << iter << " loops)." << endl;
        unsigned i;
        for (i = 0; i < iter; ++i)
        {
            vec output = data.X * w;
            output.transform(sgn);
            uvec errors = find(output.t() * data.y < 0);

            float currentError = ((float) errors.size()) / data.N;
            if (currentError < bestError)  // a better solution found
            {
                // Put in pocket the best weights and the best error.
                bestError = currentError;
                bestW = w;

                cout << "(" << setprecision(4) << bestError * 100
                        << "% errors) Iteration " << i << "." << endl;

                // End of training if a perfect decision boundary is found.
                if (bestError == 0) break;
            }

            // Select a random misclassified point.
            int misclassifiedPoint = errors[rand() % errors.size()];

            // Update weights using that point.
            w = w + data.y[misclassifiedPoint] * data.X.row(misclassifiedPoint);
        }
        cout << "End of the training. Total iterations: " << i << endl;

        // Setting weights to the best weights founded.
        w = bestW;

        return bestError;
    }

    double Perceptron::classify(const Input& x) const
    {
        double y = as_scalar(w.t() * x);
        
        return sgn(y);  // sign function
    }

    double Perceptron::error(const DataSet& data) const
    {
        vec output = data.X * w;
        output.transform(sgn);
        uvec errors = find(output.t() * data.y < 0);

        return ((double) errors.size()) / data.N;
    }

}