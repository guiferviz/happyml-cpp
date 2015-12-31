
#include "happyml/transformer.h"


namespace happyml
{

    void Transformer::addPower(unsigned feature, double power, bool create_new)
    {
        actions.push_back(POW);
        features.push_back(feature);
        param.push_back(power);
        creates.push_back(create_new);
    }

    void Transformer::addAddition(unsigned feature, double n, bool create_new)
    {
        actions.push_back(ADD);
        features.push_back(feature);
        param.push_back(n);
        creates.push_back(create_new);
    }

    void Transformer::addProduct(unsigned feature, double n, bool create_new)
    {
        actions.push_back(MUL);
        features.push_back(feature);
        param.push_back(n);
        creates.push_back(create_new);
    }

    void Transformer::remove(unsigned feature)
    {
        removeOrder.push_back(feature);
    }

    void Transformer::applyToMatrix(mat& x) const
    {
        colvec feature_i;
        
        unsigned nActions = actions.size();
        for (unsigned i = 0; i < nActions; ++i)
        {
            if (creates[i])
            {
                applyCreateNew(x, i);
            }
            else
            {
                applyNoCreateNew(x, i);
            }
        }
        // Last we remove features from higher to low.
        for(deque<unsigned>::const_reverse_iterator it = removeOrder.rbegin();
                it != removeOrder.rend(); ++it)
        {
            cout << *it << endl;
            x.shed_col(*it);
        }
    }

    void Transformer::applyCreateNew(mat& x, unsigned i) const
    {
        unsigned feature = features[i];
        colvec feature_i = x.col(feature);
        switch (actions[i])
        {
            case ADD:
                feature_i += param[i];
                break;
            case MUL:
                feature_i *= param[i];
                break;
            case POW:
                feature_i = pow(feature_i, param[i]);
                break;
        }
        x.insert_cols(x.n_cols, feature_i);
    }

    void Transformer::applyNoCreateNew(mat& x, unsigned i) const
    {
        unsigned feature = features[i];
        switch (actions[i])
        {
            case ADD:
                x.col(feature) += param[i];
                break;
            case MUL:
                x.col(feature) *= param[i];
                break;
            case POW:
                x.col(feature) = pow(x.col(feature), param[i]);
                break;
        }
    }

    void Transformer::apply(DataSet& dataset) const
    {
        applyToMatrix(dataset.X);
        dataset.d = dataset.X.n_cols - 1;
    }

    Input Transformer::apply(const Input& input) const
    {
        mat x = input.t();
        applyToMatrix(x);
        
        return x.t();
    }

}
