#include "muza/tsBool.hpp"
namespace muza {
TSBool::TSBool(bool value) : value(value) {}
bool TSBool::get() {
  bool value;
  std::unique_lock<std::mutex> lock(mutex);
  value = this->value;
  return value;
}
void TSBool::set(bool value) {
  std::unique_lock<std::mutex> lock(mutex);
  this->value = value;
}
} // namespace muza