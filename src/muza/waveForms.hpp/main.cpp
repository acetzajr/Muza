#include "muza/constants.hpp"
#include "muza/waveForms.hpp"
#include <cmath>
namespace muza {
float sin(float partP) { return std::sin(partP * kTwoPi); }
float sqr(float part) { return part < 0.5 ? 1 : -1; }
float saw(float part) { return 2 * (1 - part) - 1; }
} // namespace muza