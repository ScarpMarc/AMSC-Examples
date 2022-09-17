/*
 * partitioner.hpp
 *
 *  Created on: Sep 17, 2022
 *      Author: forma
 */

#ifndef AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_UTILITIES_PARTITIONER_HPP_
#define AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_UTILITIES_PARTITIONER_HPP_
#include <algorithm>
#include <array>
#include <vector>
namespace apsc
{
/*!
 * Partitions num_elements elements into num_tasks chunks
 *
 * Ths partition is equilibrated, the difference in size
 * between the chunks is at most i
 *
 * It implements a grouped partitioner: chunks of larger size are the last ones
 */
class GroupedPartitioner
{
public:
  GroupedPartitioner(unsigned int num_tasks, unsigned int num_elements)
    : num_tasks{num_tasks}, num_elements{num_elements},
      rest{num_elements % num_tasks}, chunk_size{num_elements / num_tasks} {};
  /*!
   * The first element of chunk t
   * @param t the chunk index
   * @return the first elements
   */
  auto
  first(unsigned int t) const
  {
    return t * chunk_size + std::min(t, rest);
  }
  /*!
   * The last element +1 of chunk t
   * @param t The chunk index
   * @return The lst elements
   */
  auto
  last(unsigned int t) const
  {
    return this->first(t + 1u);
  }
  /*!
   * The chunk index of element i in the partition
   * @param i the element index
   * @return the chunk index
   */
  auto
  loc(unsigned int i) const
  {
    return std::min(i / (chunk_size + 1u), (i - rest) / (chunk_size + 1u));
  }

  auto
  get_NumTasks() const
  {
    return num_tasks;
  }

private:
  unsigned int num_tasks;
  unsigned int num_elements;
  unsigned int rest;
  unsigned int chunk_size;
};

/*!
 * Partitions num_elements elements into num_tasks chunks
 *
 * Ths partition is equilibrated, the difference in size
 * between the chunks is at most i
 *
 * It implements a distributed partitioner
 */
class DistributedPartitioner
{
public:
  DistributedPartitioner(unsigned int num_tasks, unsigned int num_elements)
    : num_tasks{num_tasks}, num_elements{num_elements},
      rest{num_elements % num_tasks}, chunk_size{num_elements / num_tasks} {};
  /*!
   * The first element of chunk t
   * @param t the chunk index
   * @return the first elements
   */
  auto
  first(unsigned int t) const
  {
    return (t * num_elements) / num_tasks;
  }
  /*!
   * The last element +1 of chunk t
   * @param t The chunk index
   * @return The lst elements
   */
  auto
  last(unsigned int t) const
  {
    return this->first(t + 1u);
  }
  /*!
   * The chunk index of element i in the partition
   * @param i the element index
   * @return the chunk index
   */
  auto
  loc(unsigned int i) const
  {
    return (num_tasks * (i + 1u) - 1u) / num_elements;
  }
  auto
  get_NumTasks() const
  {
    return num_tasks;
  }

private:
  unsigned int num_tasks;
  unsigned int num_elements;
  unsigned int rest;
  unsigned int chunk_size;
};

/*!
 * This utility takes a partitioner object and produces counts and
 * displacements as needed for MPI gatherv or scatterv routines
 * @tparam Partitioner The type of a partitioner
 * @param partitioner The partitioner
 * @return An array with counts and displacements
 */
template <class Partitioner>
std::array<std::vector<unsigned int>, 2>
counts_and_displacements(Partitioner const &partitioner)
{
  auto                      num_tasks = partitioner.get_NumTasks();
  std::vector<unsigned int> counts;
  std::vector<unsigned int> displacements;
  counts.reserve(num_tasks);
  displacements.reserve(num_tasks);
  for(auto i = 0u; i < num_tasks; ++i)
    {
      counts.emplace_back(partitioner.last(i) - partitioner.first(i));
    }
  displacements.emplace_back(0u);
  for(auto i = 1u; i < num_tasks; ++i)
    {
      displacements.emplace_back(displacements.back() + counts[i - 1u]);
    }
  return {counts, displacements};
}

} // namespace apsc

#endif /* AMSC_EXAMPLES_EXAMPLES_SRC_PARALLEL_UTILITIES_PARTITIONER_HPP_ */
