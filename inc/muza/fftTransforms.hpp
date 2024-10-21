#pragma once
#include <cstddef>
#include <fftw3.h>
namespace muza {
using fftTransformFuntcion = void (*)(size_t frames, fftwf_complex *complex,
                                      void *userData);
void lowCut(size_t frames, fftwf_complex *complex, void *userData = nullptr);
} // namespace muza