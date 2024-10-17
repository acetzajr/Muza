#pragma once
#include <mutex>
namespace muza {
class TSBool {
public:
  TSBool(bool value);
  bool get();
  void set(bool value);

private:
  bool value;
  std::mutex mutex;
};
} // namespace muza