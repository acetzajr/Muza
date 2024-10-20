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
KeyPhase KeyState::getPhase() {
  std::unique_lock<std::mutex> lock(mutex);
  return phase;
}
void KeyState::setPhase(KeyPhase phase) {
  std::unique_lock<std::mutex> lock(mutex);
  this->phase = phase;
}
float KeyState::getAmp() {
  std::unique_lock<std::mutex> lock(mutex);
  return currentAmp;
}
void KeyState::setAmp(float amp) {
  std::unique_lock<std::mutex> lock(mutex);
  this->currentAmp = amp;
}
float KeyState::getPart() {
  std::unique_lock<std::mutex> lock(mutex);
  return currentPart;
}
void KeyState::setPart(float part) {
  std::unique_lock<std::mutex> lock(mutex);
  this->currentPart = part;
}
unsigned long long KeyState::getFrame() {
  std::unique_lock<std::mutex> lock(mutex);
  return currentFrame;
}
void KeyState::setFrame(unsigned long long frame) {
  std::unique_lock<std::mutex> lock(mutex);
  this->currentFrame = frame;
}
} // namespace muza::acetzaSy