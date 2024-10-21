#pragma once
#include "muza/fftTransforms.hpp"
#include "muza/fftWindows.hpp"
#include "muza/tsBool.hpp"
#include <array>
#include <fftw3.h>
#include <vector>
namespace muza {

class Buffer {
public:
  Buffer();
  ~Buffer();
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
  void fftTransform(fftTransformFuntcion function,
                    fftWindowFunction window = nullptr,
                    void *userData = nullptr);

private:
  std::array<fftwf_complex *, 2> complex;
  std::array<fftwf_plan, 2> fftForwardPlans;
  std::array<fftwf_plan, 2> fftBackwardPlans;
  int frames;
  std::vector<float> samples;
  std::array<std::vector<float>, 2> channels;
  std::vector<float> window;
  TSBool ready;
};
} // namespace muza