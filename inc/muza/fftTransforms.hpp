#pragma once
#include <cstddef>
#include <fftw3.h>
namespace muza {
void lowPass(size_t size, fftwf_complex *complex, void *userData = nullptr);
}