
#include "happyml/transformers/transformer.h"


namespace happyml
{

    TransformerCollection::~TransformerCollection()
    {
        for (unsigned i = 0; i < transformers.size(); ++i)
        {
            delete transformers[i];
            transformers[i] = NULL;
        }
    }

    void TransformerCollection::add(const Transformer* t)
    {
        transformers.push_back(t);
    }

    void TransformerCollection::apply(DataSet& dataset) const
    {
        for (unsigned i = 0; i < transformers.size(); ++i)
        {
            transformers[i]->apply(dataset);
        }
    }

    Input TransformerCollection::apply(const Input& x) const
    {
        Input newX = x;

        for (unsigned i = 0; i < transformers.size(); ++i)
        {
            newX = transformers[i]->apply(newX);
        }

        return newX;
    }


    namespace transforms
    {

        void Arithmetic::applyFeature(mat& x) const
        {
            if (newFeature)
            {
                int col = x.n_cols;
                x.insert_cols(col, x.col(feature));
                
                apply(x, col);
            }
            else
            {
                apply(x, feature);
            }
        }

        void Arithmetic::apply(DataSet& dataset) const
        {
            applyFeature(dataset.X);
            dataset.d = dataset.X.n_cols - 1;
        };

        Input Arithmetic::apply(const Input& input) const
        {
            mat x = input.t();
            applyFeature(x);
            return x.t();
        };

        void Pow::apply(mat& x, int col) const
        {
            x.col(col) = pow(x.col(col), param);
        }

        void Add::apply(mat& x, int col) const
        {
            x.col(col) += param;
        }

        void Mul::apply(mat& x, int col) const
        {
            x.col(col) *= param;
        }

        void Remove::apply(DataSet& dataset) const
        {
            apply(dataset.X);
            dataset.d = dataset.X.n_cols - 1;
        };

        Input Remove::apply(const Input& input) const
        {
            mat x = input.t();
            apply(x);
            return x.t();
        };

        void Remove::apply(mat& x) const
        {
            x.shed_col(feature);
        }

        // SIMPLE TRANSFORMER.
        
        void SimpleTransformer::apply(DataSet& dataset) const
        {
            // Remove x_0 feature.
            dataset.X = dataset.X.cols(1, dataset.X.n_cols - 1);
            
            apply(dataset.X);
            
            // Add x_0 = 1 feature.
            dataset.X = join_rows(vec(dataset.N, fill::ones), dataset.X);
        }

        Input SimpleTransformer::apply(const Input& x, bool hasX0) const
        {
            mat input = x.t();
            
            if (hasX0)
            {
                // Remove x_0 feature.
                input = input.cols(1, input.n_cols - 1);
            }
            
            apply(input);
            
            if (hasX0)
            {
                // Add x_0 = 1 feature.
                input = join_rows(vec(input.n_rows, fill::ones), input);
            }
            
            return input.t();
        }
    }

}
