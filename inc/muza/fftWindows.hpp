#pragma once
#include <cmath>
#include <fftw3.h>
#include <vector>
namespace muza {
using fftWindowFunction = void (*)(std::vector<float> &wave, void *userData);
void hammingWindow(std::vector<float> &wave, void *userData = nullptr);
void hanningWindow(std::vector<float> &wave, void *userData = nullptr);
void blackmanWindow(std::vector<float> &wave, void *userData = nullptr);
} // namespace muza