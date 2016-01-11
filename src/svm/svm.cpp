
#include "happyml/svm/svm.h"

#include <math.h>

#include "happyml/utils.h"


namespace happyml
{

    double SVM::train(DataSet& dataset, double C, unsigned iter,
            double tolerance)
    {
        // Output message.
        cout << colors::BLUE << "Training SVM (" << iter << " loops)."
                << colors::RESET << endl;
        
        // Remove x_0 feature.
        dataset.X = dataset.X.cols(1, dataset.d);
        
        // Init values.
        vec alphas(dataset.N, fill::zeros);
        vec errors(dataset.N);
        w = vec(dataset.d);
        b = 0;
        
        // Linear Kernel computation. All to all dot product.
        // Inefficient: symmetric matrix, wasted time and space.
        mat K = dataset.X * dataset.X.t();
        
        for (int i = 0; i < iter; ++i)
        {
            unsigned updatedAlphas = 0;
            for (int n = 0; n < dataset.N; ++n)
            {
                errors(n) = b + sum(alphas % dataset.y % K.row(n).t()) - dataset.y(n);
                
                // If misclassified and alpha not satisfy constraint
                // or well classified but not alpha 0.
                if ((dataset.y(n) * errors(n) < -tolerance && alphas(n) < C)
                    || (dataset.y(n) * errors(n) > tolerance && alphas(n) > 0))
                {
                    // Random x not equal to n.
                    int m;
                    do
                    {
                        m = rand() % dataset.N;
                    }
                    while (n == m);
                    
                    // Error of the new x.
                    errors(m) = b + sum(alphas % dataset.y % K.row(m).t()) - dataset.y(m);
                    
                    // Save old alphas.
                    double alpha_n = alphas(n);
                    double alpha_m = alphas(m);
                    
                    // Compute L and H.
                    double L = 0;
                    double H = 0;
                    if (dataset.y(n) == dataset.y(m))
                    {
                        L = max(0.0, alpha_m + alpha_n - C);
                        H = min(C, alpha_m + alpha_n);
                    }
                    else
                    {
                        L = max(0.0, alpha_m - alpha_n);
                        H = min(C, C + alpha_m - alpha_n);
                    }
                    
                    if (H == L) continue;
                    
                    double eta = 2 * K(n, m) - K(n, n) - K(m, m);
                    if (eta >= 0) continue;
                    
                    // Compute new value for alpha m.
                    alphas(m) = alphas(m) - (dataset.y(m) * (errors(n) - errors(m))) / eta;
                    
                    // Clip.
                    alphas(m) = min(H, alphas(m));
                    alphas(m) = max(L, alphas(m));
                    
                    // Check if change in alpha is significant.
                    if (abs(alphas(m) - alpha_m) < tolerance)
                    {
                        alphas(m) = alpha_m;
                        continue;
                    }
                    
                    // Determine value for alpha n.
                    alphas(n) = alphas(n) + dataset.y(n) * dataset.y(m)
                            * (alpha_m - alphas(m));
                    
                    // Compute b1 and b2.
                    double b1 = b - errors(n) - dataset.y(n) * (alphas(n)
                            - alpha_n) *  K(n, m)/*.t()*/ - dataset.y(m) * (alphas(m)
                            - alpha_m) *  K(n, m)/*.t()*/;
                    double b2 = b - errors(m) - dataset.y(n) * (alphas(n)
                            - alpha_n) *  K(n, m)/*.t()*/ - dataset.y(m) * (alphas(m)
                            - alpha_m) *  K(m, m)/*.t()*/;

                    // Compute b.
                    if (0 < alphas(n) && alphas(n) < C)
                    {
                        b = b1;
                    }
                    else if (0 < alphas(m) && alphas(m) < C)
                    {
                        b = b2;
                    }
                    else
                    {
                        b = (b1 + b2) / 2.0;
                    }
                    
                    updatedAlphas++;
                }
            }
            
            if (updatedAlphas != 0)
            {
                i = -1;
            }
        }

        // Save the model
        uvec idx = find(alphas > 0);
        vec supportAlpha = alphas(idx);
        w = ((alphas % dataset.y).t() * dataset.X).t();
        cout << b << endl << w << endl;
        
        // Add x_0 = 1 feature.
        dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        /*model.X= X(idx,:);
        model.y= Y(idx);
        model.kernelFunction = kernelFunction;
        model.b= b;
        model.alphas= alphas(idx);
        model.w = ((alphas.*Y)'*X)';*/
    }
    
    double SVM::predict(const Input& input) const
    {
        // Extract x_0.
        vec x = input.rows(1, input.n_rows - 1);
        
        double output = as_scalar(w.t() * x) + b;
        
        return sgn(output);
    }
    
    double SVM::error(const DataSet& data) const
    {
        return 1;
    }

}
