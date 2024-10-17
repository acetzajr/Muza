#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
std::mutex mutex;
std::condition_variable condition;
void wait(int i) {
  std::unique_lock<std::mutex> lock(mutex);
  std::cout << "waiting " << i << " ...\n";
  condition.wait(lock);
  std::cout << "ending " << i << " ...\n";
}
int _main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 16; ++i) {
    threads.push_back(std::thread(wait, i));
  }
  for (int i = 0; i < 8; ++i) {
    condition.notify_one();
  }
  for (auto &thread : threads) {
    thread.join();
  }
  return 0;
}
