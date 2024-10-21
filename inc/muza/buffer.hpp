#pragma once
#include "muza/tsBool.hpp"
#include <cstddef>
#include <fftw3.h>
#include <vector>
namespace muza {
using fftTransformFuntcion = void (*)(size_t size, fftwf_complex *complex,
                                      void *userData);
class Buffer {
public:
  Buffer();
  void resize(int frames);
  void copyTo(Buffer &buffer);
  int getFrames();
  int size();
  bool isReady();
  void use();
  void setReady();
  const void *data();
  float &operator[](int index);
  void print();
  void fftTransform(fftTransformFuntcion function, void *userData = nullptr);

private:
  fftwf_complex *complex;
  fftwf_plan fftForwardPlan;
  fftwf_plan fftBackwardPlan;
  int frames;
  std::vector<float> samples;
  TSBool ready;
};
} // namespace muza