
#include "happyml/transformers/transformer.h"


namespace happyml
{

    void TransformerCollection::add(const Transformer& t)
    {
        transformers.push_back(t);
    }

    void TransformerCollection::apply(DataSet& dataset)
    {
        for (unsigned i = 0; i < transformers.size(); ++i)
        {
            transformers[i].apply(dataset);
        }
    }

    Input TransformerCollection::apply(const Input& x) const
    {
        Input newX = x;

        for (unsigned i = 0; i < transformers.size(); ++i)
        {
            newX = transformers[i].apply(newX);
        }

        return newX;
    }

}
