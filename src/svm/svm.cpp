
#include "happyml/svm/svm.h"
#include "happyml/utils.h"

#include <math.h>
#include <iomanip> // std::setprecision


namespace happyml
{

    double SVM::train(const DataSet& dataset, double C, unsigned iter,
            double tolerance)
    {
        // Output message.
        cout << colors::BLUE << "Training SVM (" << iter << " loops)."
                << colors::RESET << endl;
        
        // Clone dataset and remove x_0 feature.
        DataSet d = dataset;
        d.X = d.X.cols(1, d.d);
        
        // Init values.
        vec alphas(d.N, fill::zeros);
        vec errors(d.N);
        w = vec(d.d);
        double b = 0;
        
        // Linear Kernel computation. All to all dot product.
        // Inefficient: symmetric matrix, wasted time and space.
        mat K = d.X * d.X.t();
        
        int i;
        for (i = 0; i < iter; ++i)
        {
            if (i % 10) cout << "." << flush;
            
            unsigned updatedAlphas = 0;
            for (int n = 0; n < d.N; ++n)
            {
                errors(n) = b + sum(alphas % d.y % K.row(n).t()) - d.y(n);
                
                // If misclassified and alpha not satisfy constraint
                // or well classified but not alpha 0.
                if ((d.y(n) * errors(n) < -tolerance && alphas(n) < C)
                    || (d.y(n) * errors(n) > tolerance && alphas(n) > 0))
                {
                    // Random x not equal to n.
                    int m;
                    do
                    {
                        m = rand() % dataset.N;
                    }
                    while (n == m);
                    
                    // Error of the new x.
                    errors(m) = b + sum(alphas % d.y % K.row(m).t()) - d.y(m);
                    
                    // Save old alphas.
                    double alpha_n = alphas(n);
                    double alpha_m = alphas(m);
                    
                    // Compute L and H.
                    double L = 0;
                    double H = 0;
                    if (d.y(n) == d.y(m))
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
                    alphas(m) = alphas(m) - (d.y(m) * (errors(n) - errors(m))) / eta;
                    
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
                    alphas(n) = alphas(n) + d.y(n) * d.y(m)
                            * (alpha_m - alphas(m));
                    
                    // Compute b1 and b2.
                    double b1 = b - errors(n) - d.y(n) * (alphas(n)
                            - alpha_n) *  K(n, m)/*.t()*/ - d.y(m) * (alphas(m)
                            - alpha_m) *  K(n, m)/*.t()*/;
                    double b2 = b - errors(m) - d.y(n) * (alphas(n)
                            - alpha_n) *  K(n, m)/*.t()*/ - d.y(m) * (alphas(m)
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

        // Save the model.
        uvec idx = find(alphas > 0);
        vec supportAlpha = alphas(idx);
        w = ((alphas % d.y).t() * d.X).t();
        vec bVec(1);
        bVec[0] = b;
        w = join_cols(bVec, w);
        sv.X = dataset.X.rows(idx);
        sv.y = dataset.y.rows(idx);
        sv.d = sv.X.n_cols - 1;
        sv.N = sv.X.n_rows;
        sv.k = 1;

        double currentError = error(dataset);

        cout << endl << colors::RED << "End of the training. " << i
                << " iterations. Error: " << setprecision(4) << currentError
                << colors::RESET << endl;

        return currentError;
    }
    
    double SVM::predict(const Input& input) const
    {
        // Bias term is included on weights.
        double output = as_scalar(w.t() * input);
        
        return sgn(output);
    }

}
