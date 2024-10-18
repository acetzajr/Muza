#pragma once
#include "muza/tsBool.hpp"
#include <vector>
namespace muza {
class Buffer {
public:
  Buffer();
  Buffer(int frames);
  void resize(int frames);
  void copyTo(Buffer &buffer);
  int getFrames();
  int size();
  bool isReady();
  void use();
  void setReady();
  const void *data();
  float &operator[](int index);

private:
  int frames;
  std::vector<float> samples;
  TSBool ready;
};
} // namespace muza