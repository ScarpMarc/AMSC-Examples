/*
 * Fibonacci.hpp
 *
 *  Created on: Aug 26, 2022
 *      Author: forma
 */

#ifndef AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_OPENMP_FIBONACCI_FIBONACCI_HPP_
#define AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_OPENMP_FIBONACCI_FIBONACCI_HPP_
#include <vector>

namespace Fibonacci
{
// a namespace variable. Not very nice
inline int num_threads{1};
inline unsigned int par_limit{1u};
class Fibonacci
{
public:
  auto const &
  compute(long unsigned int n)
  {
    fibs.resize(n+1ul,0ul);
#pragma omp parallel num_threads(num_threads)
#pragma omp single
    fib(n);
return fibs;
  }

private:
  long unsigned int fib(long unsigned int n)
  {
    long unsigned int i{0ul};
    long unsigned int j{0ul};
    if(n<=1ul)
      {
        fibs[n]=n;
        return n;
      }

#pragma omp task shared(i) if (n>par_limit)
    i = fib(n-1ul);
#pragma omp task shared(j) if (n>par_limit)
    j = fib(n-2ul);
#pragma omp taskwait
    fibs[n]= i+j;
    return fibs[n];
  }
  std::vector<long unsigned int> fibs;
};

/*!
 * Serial version
 */
class Fibonacci_s
{
public:
 auto const &
  compute(long unsigned int n)
  {
    fibs.resize(n+1ul,0ul);
    fib(n);
return fibs;
  }

private:
  long unsigned int fib(long unsigned int n)
  {
    long unsigned int i{0ul};
    long unsigned int j{0ul};
    if(n<=1ul)
      {
        fibs[n]=n;
        return n;
      }

    i = fib(n-1ul);
    j = fib(n-2ul);
    fibs[n]= i+j;
    return fibs[n];
  }
  std::vector<long unsigned int> fibs;
};

}


#endif /* AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_OPENMP_FIBONACCI_FIBONACCI_HPP_ */
