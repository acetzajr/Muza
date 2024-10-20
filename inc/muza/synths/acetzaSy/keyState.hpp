#pragma once
#include <mutex>
namespace muza::acetzaSy {
enum class KeyPhase { Idle, Attack, Hold, Decay, Sustain, Release, End };
class KeyState {
public:
  KeyState();
  std::mutex *getMutex();
  void press(int velocity);
  void release();
  KeyPhase getPhase();
  void setPhase(KeyPhase phase);
  float getAmp();
  void setAmp(float amp);
  float getPart();
  void setPart(float part);
  unsigned long long getFrame();
  void setFrame(unsigned long long frame);

private:
  unsigned long long currentFrame;
  float currentPart;
  float currentAmp;
  int velocity;
  std::mutex mutex;
  KeyPhase phase;
};
} // namespace muza::acetzaSy