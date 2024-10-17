#pragma once
#include "muza/types.hpp"
#include <cmath>
#include <numbers>
namespace muza {
constexpr int kFrameRate = 48'000;
constexpr Rational kRationTwo = Rational(2, 1);
constexpr Rational kRationOne = Rational(1, 1);
constexpr Rational kRationUp(3, 2);
constexpr Rational kRationDown(2, 3);
constexpr float kTwoPi = 2 * std::numbers::pi;
constexpr float kHalfPi = std::numbers::pi / 2;
} // namespace muza