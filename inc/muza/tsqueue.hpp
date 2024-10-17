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
  std::queue<T> queue;
  std::mutex mutex;
  std::condition_variable condition;
};
template <class T> void TSQueue<T>::push(T item) {
  {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(item);
  }
  condition.notify_one();
}
template <class T> T TSQueue<T>::pop() {
  std::unique_lock<std::mutex> lock(mutex);
  condition.wait(lock, [this]() { return !queue.empty(); });
  T item = queue.front();
  queue.pop();
  return item;
}
} // namespace muza