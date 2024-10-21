#include "muza/fftTransforms.hpp"
#include <cstddef>
namespace muza {
void lowPass(size_t size, fftwf_complex *complex, void *) {
  // float base = 1024.0f;
  // float mul = 4.0f;
  for (size_t i = 0; i < size; i++) {
    float frequency = (float)i * 48'000 / (float)size / 2.0;
    if (frequency >= 48'000 / 2.0) {
      complex[i][0] = 0;
      complex[i + 1][1] = 0;
      continue;
    }
    // complex[i][0] /= frequency * mul + base;
    // complex[i + 1][1] /= frequency * mul + base;
  }
}
} // namespace muza