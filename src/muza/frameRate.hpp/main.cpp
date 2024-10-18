
#include "muza/frameRate.hpp"
namespace muza {
int timeToFrame(float time, int frameRate) { return time * frameRate; }
float frameToTime(int frame, int frameRate) { return (float)frame / frameRate; }
} // namespace muza