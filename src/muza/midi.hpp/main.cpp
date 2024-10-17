#include "muza/midi.hpp"
#include <bitset>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
namespace muza {
Midi::Midi(const char *device) : running(true) {
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
  while (running.get()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    // std::cout << "running\n";
    int count = snd_rawmidi_read(midi, &buffer, sizeof(buffer));
    int index{0};
    while (count > 0) {
      process(&buffer[index]);
      index += 3;
      count -= 3;
    }
  }
}
void Midi::process(unsigned char *message) {
  int channel = message[0] & 0b0000'1111;
  if (channel != 0) {
    return;
  }
  std::cout << "Message: ";
  std::cout << "[" << std::bitset<8>(message[0]) << "]";
  std::cout << "[" << std::bitset<8>(message[1]) << "]";
  std::cout << "[" << std::bitset<8>(message[2]) << "]";
  std::cout << "\n";
  std::cout << "channel: " << channel << "\n";
}
void Midi::terminate() { running.set(false); }
} // namespace muza