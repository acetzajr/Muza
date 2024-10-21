#include "muza/fftWindows.hpp"
#include <vector>
namespace muza {
void hammingWindow(std::vector<float> &wave, void *) {
  size_t size = wave.size();
  for (size_t n = 0; n < size; ++n) {
    wave[n] *= 0.54 - 0.46 * std::cos(2 * std::numbers::pi * n / (size - 1));
  }
}
void hanningWindow(std::vector<float> &wave, void *) {
  size_t size = wave.size();
  for (size_t n = 0; n < size; ++n) {
    wave[n] *= 0.5 - 0.5 * cos(2 * std::numbers::pi * n / (size - 1));
  }
}
void blackmanWindow(std::vector<float> &wave, void *) {
  size_t size = wave.size();
  for (size_t n = 0; n < size; ++n) {
    wave[n] *= 0.42 - 0.5 * cos(2 * std::numbers::pi * n / (size - 1)) +
               0.08 * cos(4 * std::numbers::pi * n / (size - 1));
  }
}
} // namespace muza