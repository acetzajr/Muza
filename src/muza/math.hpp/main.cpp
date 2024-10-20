#include "muza/math.hpp"
#include <cmath>
namespace muza {
float ampToDB(float amp) { return 10.0f * std::log10(amp); }
float dbToAmp(float db) { return std::pow(10.0f, db / 10.0f); }
} // namespace muza