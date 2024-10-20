#include "RtMidi.h"
#include "muza/messages/message.hpp"
#include "muza/messages/noteOffMessage.hpp"
#include "muza/messages/noteOnMessage.hpp"
#include "muza/messages/pedalOffMessage.hpp"
#include "muza/messages/pedalOnMessage.hpp"
#include "muza/midi.hpp"
#include <alsa/rawmidi.h>
#include <bitset>
#include <iostream>
#include <stdexcept>
namespace muza {
namespace midi {
void callback(double, std::vector<unsigned char> *message, void *userData) {
  // std::cout << message->size() << "\n";
  Midi *midi = (Midi *)userData;
  midi->process(message->data());
}
void errorCallback(RtMidiError::Type, const std::string &errorText, void *) {
  throw std::runtime_error(errorText);
}
} // namespace midi
Midi::Midi(TSQueue<Message *> *queue) : midiIn(), pusher(queue), running(true) {
  midiIn.setErrorCallback(midi::errorCallback);
  midiIn.setCallback(midi::callback, this);
  for (int i = 0; i < (int)midiIn.getPortCount(); ++i) {
    std::cout << "Port No." << i << ": " << midiIn.getPortName(i) << "\n ";
  }
  midiIn.openPort(1);
}
void Midi::thread() {}
int Midi::getChannel(unsigned char *message) {
  return message[0] & 0b0000'1111;
}
int Midi::getKey(unsigned char *message) { return message[1]; }
int Midi::getVelocity(unsigned char *message) { return message[2]; }
void Midi::sendNoteOff(unsigned char *message) {
  pusher.push(new NoteOffMessage(getKey(message), getVelocity(message)));
}
void Midi::sendNoteOn(unsigned char *message) {
  pusher.push(new NoteOnMessage(getKey(message), getVelocity(message)));
}
void Midi::sendPedalOff() { pusher.push(new PedalOffMessage()); }
void Midi::sendPedalOn() { pusher.push(new PedalOnMessage()); }
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
  int typeCode = message[0] >> 4;
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
void Midi::terminate() { midiIn.closePort(); }
} // namespace muza