#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
namespace muza {
template <typename T> class TSQueue {
public:
  void push(T item);
  T pop();

private:
  // Underlying queue
  std::queue<T> queue;
  // mutex for thread synchronization
  std::mutex mutex;
  // Condition variable for signaling
  std::condition_variable condition;
};
template <class T> void TSQueue<T>::push(T item) {
  // Acquire lock
  std::unique_lock<std::mutex> lock(mutex);
  // Add item
  queue.push(item);
  // Notify one thread that
  // is waiting
  condition.notify_one();
}
template <class T> T TSQueue<T>::pop() {
  // acquire lock
  std::unique_lock<std::mutex> lock(mutex);
  // wait until queue is not empty
  condition.wait(lock, [this]() { return !queue.empty(); });
  // retrieve item
  T item = queue.front();
  queue.pop();
  // return item
  return item;
}
} // namespace muza