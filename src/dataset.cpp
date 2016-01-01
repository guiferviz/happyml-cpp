
#include "happyml/dataset.h"


namespace happyml
{

    void DataSet::read(istream& stream)
    {
        mat inputMat;
        inputMat.load(stream, csv_ascii);
        
        d = inputMat.n_cols - 1;
        N = inputMat.n_rows;
        
        X = mat(N, d + 1, fill::ones);
        X.cols(1, d) = inputMat.cols(0, d - 1);
        y = inputMat.col(d);
    }

    void DataSet::write(ostream& stream) const
    {
        mat outputMat = join_horiz(X.cols(1, d), y);
        outputMat.save(stream, csv_ascii);
    }

}
