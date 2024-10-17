#pragma once
namespace muza {
using WaveForm = float (*)(float part);
float sin(float part);
float sqr(float part);
float saw(float part);
} // namespace muza