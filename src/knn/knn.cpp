
#include "happyml/knn/knn.h"


using namespace std;


namespace happyml
{

    // TODO: use k, only 1-NN is implemented.
    double KNN::predict(const Input& x) const
    {
        double minDistance = 9e99;
        int argmin = -1;
        for (int i = 0; i < dataset.N; ++i)
        {
            vec aux = dataset.X.row(i).t() - x;
            aux %= aux;
            double distance = sum(aux);
            if (distance < minDistance)
            {
                minDistance = distance;
                argmin = i;
            }
        }
        
        if (argmin != -1)
            return dataset.y[argmin];
        
        return 0;
    }

}
