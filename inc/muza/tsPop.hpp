#pragma once
#include "muza/tsQueue.hpp"
namespace muza {
template <typename T> class TSPop {
public:
  TSPop(TSQueue<T> *queue);
  T pop();

private:
  TSQueue<T> *queue;
};
template <typename T> TSPop<T>::TSPop(TSQueue<T> *queue) : queue(queue) {}
template <typename T> T TSPop<T>::pop() { return queue->pop(); }
} // namespace muza