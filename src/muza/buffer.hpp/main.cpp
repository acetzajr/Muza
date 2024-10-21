#include "muza/buffer.hpp"
#include <cstddef>
#include <fftw3.h>
#include <iostream>
#include <stdexcept>
namespace muza {
Buffer::~Buffer() {
  fftwf_destroy_plan(fftForwardPlans[0]);
  fftwf_destroy_plan(fftForwardPlans[1]);
  fftwf_destroy_plan(fftBackwardPlans[0]);
  fftwf_destroy_plan(fftBackwardPlans[1]);
  fftwf_free(complex[0]);
  fftwf_free(complex[1]);
}
Buffer::Buffer() : ready(true) {}
void Buffer::resize(int frames) {
  size_t size = frames * 2;
  samples.resize(size, 0);
  window.resize(size, 0);
  channels[0].resize(frames, 0);
  channels[1].resize(frames, 0);
  this->frames = frames;
  complex[0] = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * frames);
  complex[1] = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * frames);
  fftForwardPlans[0] =
      fftwf_plan_dft_r2c_1d(channels[0].size(), (float *)channels[0].data(),
                            complex[0], FFTW_ESTIMATE);
  fftForwardPlans[1] =
      fftwf_plan_dft_r2c_1d(channels[1].size(), (float *)channels[1].data(),
                            complex[1], FFTW_ESTIMATE);
  fftBackwardPlans[0] =
      fftwf_plan_dft_c2r_1d(channels[0].size(), complex[0],
                            (float *)channels[0].data(), FFTW_ESTIMATE);
  fftBackwardPlans[1] =
      fftwf_plan_dft_c2r_1d(channels[1].size(), complex[1],
                            (float *)channels[1].data(), FFTW_ESTIMATE);
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
void Buffer::fftTransform(fftTransformFuntcion function,
                          fftWindowFunction window, void *userData) {
  size_t i = 0;
  size_t f = 0;
  while (i < samples.size()) {
    channels[0][f] = samples[i];
    channels[1][f] = samples[i + 1];
    i += 2;
    ++f;
  }
  if (window != nullptr) {
    window(channels[0], userData);
    window(channels[1], userData);
  }
  fftwf_execute(fftForwardPlans[0]);
  fftwf_execute(fftForwardPlans[1]);
  function(channels[0].size(), complex[0], userData);
  function(channels[1].size(), complex[1], userData);
  fftwf_execute(fftBackwardPlans[0]);
  fftwf_execute(fftBackwardPlans[1]);
  i = 0;
  f = 0;
  while (i < samples.size()) {
    samples[i] = channels[0][f];
    samples[i + 1] = channels[1][f];
    i += 2;
    ++f;
  }
  for (auto &sample : samples) {
    sample /= 512.0f;
  }
}
} // namespace muza