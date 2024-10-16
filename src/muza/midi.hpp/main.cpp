#include "muza/midi.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
namespace muza {
Midi::Midi(const char *device) {
  midi = nullptr;
  int code = snd_rawmidi_open(&midi, nullptr, device, 0);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
  code = snd_rawmidi_nonblock(midi, 1);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
}
Midi::~Midi() {
  if (midi != nullptr) {
    int code = snd_rawmidi_drain(midi);
    if (code < 0) {
      std::cerr << snd_strerror(code);
    }
    code = snd_rawmidi_close(midi);
    if (code < 0) {
      std::cerr << snd_strerror(code);
    }
  }
}
void Midi::thread() {
  while (isRunning()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    // std::cout << "running\n";
    int count = snd_rawmidi_read(midi, &buffer, sizeof(buffer));
    if (count >= 0) {
      std::cout << count << "\n";
    }
  }
}
void Midi::terminate() {
  mutex.lock();
  running = false;
  mutex.unlock();
}
bool Midi::isRunning() {
  bool running;
  mutex.lock();
  running = this->running;
  mutex.unlock();
  return running;
}
} // namespace muza