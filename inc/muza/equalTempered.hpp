#pragma once
namespace muza {
class EqualTempered {
public:
  static float frequencyOf(float noteIndex, float base = 440.0f);
};
} // namespace muza