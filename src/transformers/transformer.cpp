
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

    }

}
