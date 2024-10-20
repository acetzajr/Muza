#include "muza/synths/acetzaSy/keyState.hpp"
// #include <iostream>
#include <mutex>
namespace muza::acetzaSy {
KeyState::KeyState() {}
std::mutex *KeyState::getMutex() { return &mutex; }
void KeyState::press(int velocity) {
  // std::cout << "Press\n";
  std::unique_lock<std::mutex> lock(mutex);
  this->velocity = velocity;
  phase = KeyPhase::Attack;
}
void KeyState::release() {
  std::unique_lock<std::mutex> lock(mutex);
  phase = KeyPhase::Release;
  currentFrame = 0;
}
KeyPhase KeyState::getPhase() { return phase; }
void KeyState::setPhase(KeyPhase phase) { this->phase = phase; }
float KeyState::getAmp() { return currentAmp; }
void KeyState::setAmp(float amp) { this->currentAmp = amp; }
float KeyState::getPart() { return currentPart; }
void KeyState::setPart(float part) { this->currentPart = part; }
unsigned long long KeyState::getFrame() { return currentFrame; }
void KeyState::setFrame(unsigned long long frame) {
  this->currentFrame = frame;
}
} // namespace muza::acetzaSy