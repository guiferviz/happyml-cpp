
<p align="center">
  <img width="200px" src="happyml-logo.png" alt="HappyML logo">
</p>

  C++ Machine Learning Library For Academic Purposes
=======================================================

*HappyML* is a little project supposed to be used by beginners in the machine learning field. It uses simple implementations of the more common algorithms. Depends on *armadillo* library for linear algebra operations. The high level of this library make easy to write and read the code. It also uses *octave* for visualizations tools.


Build and Install
-----------------

First install *armadillo* library for linear algebra (http://arma.sourceforge.net/). If you are using *Ubuntu* you can install it with `sudo apt-get install libarmadillo-dev`.

Then compile and install *HappyML*.

```
git clone https://github.com/guiferviz/happyml.git
cd happyml
mkdir build
cd build
cmake ..
make
sudo make install
```

Getting Started
---------------

Onces compiled and installed, create an empty file and write

```c++
#include <happyml.h>

int main()
{
    happyml::greet();
}
```

Compile with: `g++ -o happyworld happyworld.cpp -lhappyml` and execute the program with `./happyworld`. You will see the output:

> Those about to learn we salute you.

If you get that, congrats, you have installed *HappyML* successfully.

Contact
-------

Mail me ([guiferviz](mailto:guiferviz@gmail.com)) or create an issue.

<br />
<br />
<br />

**REMEMBER TO BE HAPPY :smile: :blush: :relaxed:**

