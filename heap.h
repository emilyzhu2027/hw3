#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_vector;
  int m;
  PComparator c;

  void heapify(int idx);

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m(m), c(c)
{

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("Error");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return heap_vector.front();

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("Error");
  }

  heap_vector[0] = heap_vector.back();
  heap_vector.pop_back();
  heapify(0);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx){
  int child_idx_idx = m * idx + 1;
  if (child_idx_idx >= (int)(heap_vector.size())){
    return;
  }

  int small_child = m * idx + 1;
  for (int i = 1; i < m; i++){
    int next_child = m * idx + (i + 1);
    if (next_child < (int)(heap_vector.size())){
      if (c(heap_vector[next_child], heap_vector[small_child])){
        small_child = next_child;
      }
    }
  }

  if (!c(heap_vector[idx], heap_vector[small_child])){
    T temp_item = heap_vector[idx];
    heap_vector[idx] = heap_vector[small_child];
    heap_vector[small_child] = temp_item;
    heapify(small_child);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  heap_vector.push_back(item);
  int loc = heap_vector.size()-1;
  int parent = (loc-1)/m;
  while (parent > -1 && c(heap_vector[loc], heap_vector[parent])){
    T temp_item = heap_vector[parent];
    heap_vector[parent] = heap_vector[loc];
    heap_vector[loc] = temp_item;

    loc = parent;
    parent = (loc-1)/m;
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  if (heap_vector.size() == 0){
    return true;
  }
  return false;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return (heap_vector.size());
}

#endif

