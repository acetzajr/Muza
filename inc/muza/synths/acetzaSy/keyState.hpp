#pragma once
#include <mutex>
namespace muza::acetzaSy {
enum class KeyPhase { Idle, Attack, Hold, Decay, Sustain, Release, End };
class KeyState {
public:
  KeyState();
  void press(int velocity);
  void release();
  KeyPhase getPhase();
  void setPhase(KeyPhase phase);
  float getAmp();
  void setAmp(float amp);
  float getPart();
  void setPart(float part);

private:
  float currentPart;
  float currentAmp;
  int velocity;
  std::mutex mutex;
  KeyPhase phase;
};
} // namespace muza::acetzaSy