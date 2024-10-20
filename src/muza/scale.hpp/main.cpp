#include "muza/constants.hpp"
#include "muza/scale.hpp"
#include "muza/types.hpp"
#include <iostream>
#include <vector>
namespace muza {
void normalizeRation(Rational &rational) {
  while (rational > kRationTwo) {
    rational /= kRationTwo;
  }
  while (rational < kRationOne) {
    rational *= kRationTwo;
  }
}
auto fillScale(std::vector<Rational> &rations) -> void {
  rations[0] = kRationOne;
  int scaleIdx = 1;
  Rational r = kRationOne;
  for (int i = 0; i < 5; i++) {
    r *= kRationUp;
    normalizeRation(r);
    rations[scaleIdx++] = r;
  }
  r = kRationOne;
  for (int i = 0; i < 5; i++) {
    r *= kRationDown;
    normalizeRation(r);
    rations[scaleIdx++] = r;
  }
  std::sort(rations.begin(), rations.end());
}
void printRations(std::vector<Rational> &rations) {
  std::cout << "rations: { ";
  for (const auto &ration : rations) {
    std::cout << ration << " ";
  }
  std::cout << "}\n";
}
float rationalToFloat(Rational rational) {
  return (float)rational.numerator() / rational.denominator();
}
Scale::Scale(float base) {
  std::vector<Rational> rations(11);
  fillScale(rations);
  // printRations(rations);
  int note = 10;
  float power = 1.0f;
  float sqrOfTwo = std::pow(2.0f, 1.0f / 2.0f);
  // std::cout << "sqrOfTwo " << sqrOfTwo << "\n";
  for (int i = 0; i < 128; ++i, ++note) {
    if (note == 12) {
      note = 0;
      power *= 2;
    }
    if (note == 6) {
      frequencies[i] = base * power * sqrOfTwo;
      continue;
    }
    int ri = note < 6 ? note : note - 1;
    frequencies[i] = base * power * rationalToFloat(rations[ri]);
  }
  // print();
}
float Scale::frequencyOf(int note) { return frequencies[note]; }
void Scale::print() {
  std::cout << "Scale:\n";
  for (int key = 0; key < (int)frequencies.size(); ++key) {
    std::cout << "Key " << key << " = " << frequencies[key] << "\n";
  }
}
} // namespace muza