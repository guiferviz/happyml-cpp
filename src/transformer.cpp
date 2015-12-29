
#include "happyml/transformer.h"


namespace happyml
{

    void Transformer::addPower(unsigned feature, double power)
    {
        featuresPower.push_back(feature);
        powerPower.push_back(power);
    }
    
    void Transformer::apply(DataSet& dataset) const
    {
        unsigned nPower = featuresPower.size();
        for (unsigned i = 0; i < nPower; ++i)
        {
            colvec feature_i = dataset.X.col(featuresPower[i]);
            // Raise to the power.
            feature_i = pow(feature_i, powerPower[i]);
            // Add the new feature to X (and increase dataset dimension).
            dataset.X.insert_cols(++dataset.d, feature_i);
        }
    }

}
