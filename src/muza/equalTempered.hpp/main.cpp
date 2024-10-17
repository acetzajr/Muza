#include "muza/equalTempered.hpp"
#include <cmath>
namespace muza {
float EqualTempered::frequencyOf(float noteIndex, float base) {
  return base * std::pow(2.0f, noteIndex / 12.0f);
}
} // namespace muza