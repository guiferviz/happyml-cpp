
#include "happyml/serializable.h"

#include <fstream>


using namespace std;


namespace happyml
{

    void Serializable::load(const string& filename)
    {
        ifstream file;
        file.open(filename.c_str());
        
        if (file.is_open())
        {
            read(file);
            file.close();
        }
    }

    void Serializable::save(const string& filename) const
    {
        ofstream file;
        file.open(filename.c_str());
        
        write(file);
        
        file.close();
    }

}
