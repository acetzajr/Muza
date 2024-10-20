#pragma once
#include "muza/audio.hpp"
#include "muza/midi.hpp"
#include "muza/midiMessage.hpp"
#include "muza/synths/acetzaSy.hpp"
#include "muza/tsQueue.hpp"
#include <thread>
namespace muza {
class Session {
public:
  Session();
  ~Session();
  void wait();

public:
  TSQueue<Buffer *> buffers;
  TSQueue<MidiMessage> messages;
  Audio audio;
  Midi midi;
  AcetzaSy synth;
  std::thread audioThread;
  std::thread synthThread;
};
} // namespace muza