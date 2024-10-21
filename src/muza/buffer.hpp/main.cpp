#include "muza/buffer.hpp"
#include <fftw3.h>
#include <iostream>
#include <stdexcept>
namespace muza {
Buffer::Buffer() : ready(true) {}
void Buffer::resize(int frames) {
  samples.resize(frames * 2, 0);
  this->frames = frames;
  complex =
      (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * samples.size());
  fftForwardPlan = fftwf_plan_dft_r2c_1d(
      samples.size(), (float *)samples.data(), complex, FFTW_ESTIMATE);
  fftBackwardPlan = fftwf_plan_dft_c2r_1d(
      samples.size(), complex, (float *)samples.data(), FFTW_ESTIMATE);
}
bool Buffer::isReady() { return ready.get(); }
int Buffer::getFrames() { return frames; }
void Buffer::use() {
  ready.set(false);
  for (auto &sample : samples) {
    sample = 0.0f;
  }
}
void Buffer::setReady() { ready.set(true); }
const void *Buffer::data() { return samples.data(); }
int Buffer::size() { return samples.size(); }
void Buffer::copyTo(Buffer &buffer) {
  if (size() != buffer.size()) {
    throw std::runtime_error("Buffer size not equal\n");
  }
  for (unsigned long i = 0; i < samples.size(); ++i) {
    buffer[i] = (*this)[i];
  }
}
float &Buffer::operator[](int index) {
  if (index < 0 && index >= size()) {
    throw std::runtime_error("Buffer access out of range\n");
  }
  return samples[index];
}
void Buffer::print() {
  for (auto &sample : samples) {
    std::cout << sample << "\n";
  }
}
void Buffer::fftTransform(fftTransformFuntcion function, void *userData) {
  fftwf_execute(fftForwardPlan);
  function(samples.size(), complex, userData);
  fftwf_execute(fftBackwardPlan);
  for (auto &sample : samples) {
    sample /= 1024.0f;
  }
}
} // namespace muza