
#include "happyml/dataset.h"

#include <map>


namespace happyml
{

    void DataSet::read(istream& stream)
    {
        mat inputMat;
        inputMat.load(stream, csv_ascii);
        
        d = inputMat.n_cols - k;
        N = inputMat.n_rows;
        
        X = mat(N, d + 1, fill::ones);
        X.cols(1, d) = inputMat.cols(0, d - 1);
        y = inputMat.cols(d, inputMat.n_cols - 1);
    }
    
    void DataSet::read(istream& stream, int nOutputs)
    {
        k = nOutputs;
        
        read(stream);
    }
    
    void DataSet::load(const string& filename, int nOutputs)
    {
        k = nOutputs;
        
        Serializable::load(filename);
    }

    void DataSet::load(const string& filename, bool oneHotOutput)
    {
        k = 1;
        
        Serializable::load(filename);
        
        if (oneHotOutput)
        {
            map<double, unsigned> count;
            for (int i = 0; i < N; ++i)
            {
                count[y[i]] = count[y[i]] + 1;
            }
            k = count.size();
            mat oneHot(N, k, fill::zeros);
            
            int i;
            map<double, unsigned>::iterator it;
            for (it = count.begin(), i = 0; it != count.end(); ++it, ++i)
            {
                uvec pos = find(y == it->first);
                vec col(N, fill::zeros);
                col(pos).fill(1);
                
                oneHot.col(i) = col;
            }
            y = oneHot;
        }
    }

    void DataSet::write(ostream& stream) const
    {
        mat outputMat = join_horiz(X.cols(1, d), y);
        outputMat.save(stream, csv_ascii);
    }

    void DataSet::shuffle()
    {
        uvec all = find(X.col(0) > 0);
        all = arma::shuffle(all);

        X = X.rows(all);
        y = y.rows(all);
    }

}
