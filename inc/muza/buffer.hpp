#pragma once
#include <vector>
namespace muza {
class Buffer {
public:
  Buffer() = default;
  Buffer(int frames);
  void copyTo(Buffer &buffer);
  int size();
  bool isReady();
  void use();
  const void *data();
  float &operator[](int index);

private:
  std::vector<float> samples;
  bool ready;
};
} // namespace muza