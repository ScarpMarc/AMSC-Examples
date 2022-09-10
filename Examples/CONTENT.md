# Content of the Examples/src directory #

We give here an overview of the content of the `src` directory where all the sources of the examples are stored. *All examples have a `README.md` file with a more detailed description*.


## Utilities##
  - `Utilities` A set of utilities that you may use also in your code. All described in the local `README.md` file. 
  **You should go in the directory and type**

``` 
    make
    make install
```

since several examples make use of the utilities.
  
## Basic Examples ##
  * `Aggregates` Show some feature of *aggregates*, a particular type of classes that have to satisfy some requirements, see [here for instance](https://en.cppreference.com/w/cpp/language/aggregate_initialization), and allow very useful constructs.
  * `Arrays` Some examples of the use of std::array
  * `Functors` An example of use of callable objects (functors).
  * `LambdaExpr` Some examples of lambda expressions.
  * `Numeric_limits`. It uses almost all the facilities provided by `numeric_limits<>`, just to show what they do.
  * `Polygon`. A classic example of *polymorphism*: a hierarchy of polygon classes.
  * `Rational`. An example on operator overloading: a class for rational numbers.
  * `SmartPointers` An example on the use of smart pointers. 
  * `Vector` Examples of use of `std::vector`.
  *`Vector/Basics` As the name says.
  *`Vector/Remove` What it means removing elements from a vector.
  *`tuple` The use of tuple. 

## Advanced examples
  A different Function Factory is present in `Factory` as a specialization of the generic factory contained therein.
  * `Parallel` Some examples of parallelization
    * `Parallel/MPI` MPI Examples
    * `Parallel/OpenMP` OpenMO Examples
    * `Parallel/STL` Some examples of STL parallel algorithms.


## Full examples
  * `HeatExchange` A simple finite element code that solves a 1D problem. An example also of use of *GetPot*, *json file reader* and *GnuPlot*
## A DISCLAIMER ##

The code is provided as-is, without any claim of correctness or fitness for any purpose, a part learning C++. Of
course I have tried to find and fix all bugs I have found, but I cannot guarantee that
errors aren't still present (actually, it is very likely that they are).

If you find a mistake, of you think that an example can be bettered, **please tell me!**. I will be happy to include your corrections/suggestions, and give credits to you.

-------------------------------------------------------------------------------


