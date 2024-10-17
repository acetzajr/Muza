#include "muza/messages/message.hpp"
#include "muza/messages/noteOffMessage.hpp"
#include "muza/messages/noteOnMessage.hpp"
#include "muza/messages/pedalOffMessage.hpp"
#include "muza/messages/pedalOnMessage.hpp"
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
int Midi::getChannel(unsigned char *message) {
  return message[0] & 0b0000'1111;
}
int Midi::getKey(unsigned char *message) { return message[1]; }
int Midi::getVelocity(unsigned char *message) { return message[2]; }
void Midi::sendNoteOff(unsigned char *message) {
  queue.push(NoteOffMessage(getKey(message), getVelocity(message)));
}
void Midi::sendNoteOn(unsigned char *message) {
  queue.push(NoteOnMessage(getKey(message), getVelocity(message)));
}
void Midi::sendPedalOff() { queue.push(PedalOffMessage()); }
void Midi::sendPedalOn() { queue.push(PedalOnMessage()); }
void Midi::printMessage(unsigned char *message) {
  std::cout << "Message: ";
  std::cout << "[" << std::bitset<8>(message[0]) << "]";
  std::cout << "[" << std::bitset<8>(message[1]) << "]";
  std::cout << "[" << std::bitset<8>(message[2]) << "]";
  std::cout << "\n";
}
void Midi::process(unsigned char *message) {
  if (getChannel(message) != 0) {
    return;
  }
  int typeCode = message[0] & 0b1111'0000;
  switch (typeCode) {
  case 0b1000:
    sendNoteOff(message);
    break;
  case 0b1001:
    sendNoteOn(message);
    break;
  case 0b1011:
    if (message[1] != 0b0100'0000) {
      break;
    }
    if (message[2] >= 64) {
      sendPedalOn();
    }
    sendPedalOff();
    break;
  }
}
void Midi::terminate() { running.set(false); }
} // namespace muza