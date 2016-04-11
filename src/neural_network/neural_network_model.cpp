
#include "happyml/neural_network/neural_network_model.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> // std::setprecision
#include <cstdarg>


namespace happyml
{

    NeuralNetworkModel::NeuralNetworkModel(unsigned layers, ...) :
            L(layers - 1), weights(layers), d(layers)
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

    NeuralNetworkModel::NeuralNetworkModel(unsigned layers, bool unused) :
            L(layers - 1), weights(layers), d(layers)
    {
    }

    NeuralNetworkModel::NeuralNetworkModel(const vector<unsigned>& layers) :
            L(layers.size() - 1), weights(layers.size()), d(layers.size())
    {
        d[0] = layers[0];
        for (unsigned l = 1; l <= L; ++l)
        {
            d[l] = layers[l];
            weights[l] = mat(d[l - 1] + 1, d[l], fill::randn);
        }
    }

    NeuralNetworkModel::NeuralNetworkModel(const vector<mat>& w) :
            L(w.size() + 2), weights(w), d(w.size() + 2)
    {
        vector<mat>::iterator it = weights.begin();
        it = weights.insert(it, mat());
        
        d[0] = weights[1].n_rows;
        for (int i = 1; i <= L; ++i)
        {
            d[i] = weights[i].n_cols;
        }
        L = weights.size() - 1;
    }

    NeuralNetworkModel::NeuralNetworkModel(const NeuralNetworkModel& p) :
            L(p.L), weights(p.weights), d(p.d)
    {
    }

    NeuralNetworkModel::~NeuralNetworkModel()
    {
    }


    void NeuralNetworkModel::read(istream& stream)
    {
        field<mat> matrices;
        matrices.load(stream);
        
        weights.clear();
        weights.push_back(mat());
        d.clear();
        d.push_back(matrices[0].n_rows);
        for (int i = 0; i < matrices.size(); ++i)
        {
            d.push_back(matrices[i].n_cols);
            weights.push_back(matrices[i]);
        }
        L = weights.size() - 1;
    }

    void NeuralNetworkModel::write(ostream& stream) const
    {
        field<mat> matrices(L);
        
        for (int i = 0; i < L; ++i)
        {
            matrices[i] = weights[i + 1];
        }
        
        matrices.save(stream);
    }

}
