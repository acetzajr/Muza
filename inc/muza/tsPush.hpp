#pragma once
#include "muza/tsQueue.hpp"
namespace muza {
template <typename T> class TSPush {
public:
  TSPush(TSQueue<T> *queue);
  void push(T item);

private:
  TSQueue<T> *queue;
};
template <typename T> TSPush<T>::TSPush(TSQueue<T> *queue) : queue(queue) {}
template <typename T> void TSPush<T>::push(T item) { queue->push(item); }
} // namespace muza