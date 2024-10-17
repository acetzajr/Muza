#pragma once
#include <array>
namespace muza {
class Scale {
public:
  Scale(float base = 1.0f);
  float frequencyOf(int note);
  void print();

private:
  std::array<float, 128> frequencies;
};
} // namespace muza