
#include "happyml/knn/knn.h"

#include <map>


using namespace std;


namespace happyml
{

    double KNN::predict(const Input& x) const
    {
        // Thanks to sukharevd.
        mat distances = repmat(x.t(), dataset.N, 1) - dataset.X;
        distances = sqrt(sum(square(distances), 1));
        umat sortedDistIndicies = sort_index(distances);
        std::map<uword, int> classCount;
        int maxVotes = -1;
        int maxClass = -1;
        for (unsigned i = 0; i < k; ++i)
        {
            uword label = dataset.y[sortedDistIndicies[i]];
            if (!classCount.count(label))
                classCount.insert(std::make_pair(label, 0));
            classCount.at(label) += 1;
            if (classCount.at(label) > maxVotes)
            {
                maxVotes = classCount.at(label);
                maxClass = label;
            }
        }
        
        return maxClass;
    }

}
