#Various Utilities#

In this directory you have utilities thay may be included and used in
other examples. So, you need to install them before moving to the other
examples.

You need to do

    make 
    make install

to install them. `make` will produce both a dynamic and a static library, called `libpacs.so` and `libpacs.a`, respectively. `make install` installs the header files in `AMSC_ROOT/include` and the libraries into `AMSC_ROOT/lib`. Use `make DEBUG=no` if you want the library code to be optimised.

After you have installed the libraries you can run

    make test

which produces tests for most of the utilities. All tests start with `test_`. You may have a look at the source to see what they do.

*Remember to install the utilities, they are used by other examples!.*

**Note**: some utilities are in a nested namespace of the namespace `apsc`. Check it out looking at the code or at the examples.

List of the utilities:

* `chrono`  An utility to take times, built on the chrono utilities of the standard library.


* `cxxversion` To test with which version of C++ you are compiling your code

* `GetPot`  GetPot command parser<http://getpot.sourceforge.net/>. I have simplified the version available on the given link, so you have just to so `#include <GetPot>` of `#include "GetPot"`, and have it available.

* `json/` An entire submodule (remember to clone the repo with `--recursive` or launch `install-git-submodule.sh` from the root directory). It contains a fork of the [json for modern c++](https://json.nlohmann.me/).

* `gnuplot-iostream` A stream to open gnuplot from within a program. Useful for simple visualizations within your code. You need[gnuplot](http://www.gnuplot.info/) installed in your system (it is available as debian package).

* `is_complex.hpp` A header file containing a type trait to interrogate is a type is a `std::complex<T>`

* `is_eigen.hpp` A header file containing a type trait to interrogate is a type is a `Eigen::Matrix`

* `readCSV` A class to read csv files. Useful if you have data in a speadsheet and you want to load it into a C++ code. There are better tools than this one around. But this is relativley simple and handy

* `scientific_precision` A function that sets the precision of a stream to the maximum value for a floating point. It contains also stream manipulators for the same purpose.

* `StatisticsComputations` Some tools to compute basic statistics of a sample.

* `string_utility` Some extra utilities for strings: trimming (eliminate useless blanks) and lower-upper conversion. We have recetly added utilities for reading a whole text file in a buffer (it is faster, though potentially memory consuming, and an utility that computed the Levenshtein edit distance between two strings).

* `toString` Converts anything for which there is the `<<` streming operator to a string. A use of `std::stringstream`.



## What you can learn from these examples##

The files in this directory illustrate the advantage of having little general utilities that can be integrated in different codes.
Some utilities are simple to understand, like `Chrono` or `StatisticsComputations`, others make use of more sophisticated generic programming 
techniques, like `is_complex`, `is_eigen`. 
Finally, some, like `gnuplot_iostream`, `json` and `GetPot` are just copies of tools available open source, copied here for simplicity.


