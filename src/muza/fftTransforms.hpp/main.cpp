#include "muza/fftTransforms.hpp"
#include <cstddef>
namespace muza {
void lowCut(size_t frames, fftwf_complex *complex, void *) {
  // float base = 512.0f;
  for (size_t i = 0; i < frames; i++) {
    float frequency = (float)i * 48'000 / (float)frames;
    if (frequency >= 48'000 / 2.0) {
      complex[i][0] = 0;
      complex[i][1] = 0;
      continue;
    }
    // complex[i][0] /= frequency + base;
    // complex[i][1] /= frequency + base;
  }
}
} // namespace muza