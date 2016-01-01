
#ifndef _HAPPY_ML_SERIALIZABLE_H_
#define _HAPPY_ML_SERIALIZABLE_H_


#include <string>


using namespace std;


namespace happyml
{

    /**
     * Abstract class that represent an object that can be loaded from a file
     * and saved to a file.
     */
    class Serializable
    {
        public:

            /**
             * Fills an object using the data in the given file.
             *
             * @param filename Name of the file to load.
             * 
             * @see save(const string&)
             */
            virtual void load(const string& filename);

            /**
             * Saves the object to a specific file. After this call you can
             * load new objects using the load method and that filename.
             * 
             * @param filename Output filename.
             * 
             * @see load(const string&)
             */
            virtual void save(const string& filename) const;

            /**
             * Read the object from an input stream.
             * 
             * @param stream Input stream.
             */
            virtual void read(istream& stream) = 0;

            /**
             * Write the object to an output stream.
             * 
             * @param stream Output stream.
             */
            virtual void write(ostream& stream) const = 0;

    };

}


#endif  // _HAPPY_ML_SERIALIZABLE_H_
