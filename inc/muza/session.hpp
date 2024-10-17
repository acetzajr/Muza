#pragma once
#include "muza/audio.hpp"
#include "muza/messages/message.hpp"
#include "muza/midi.hpp"
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
  TSQueue<Message *> messages;
  Audio audio;
  Midi midi;
  AcetzaSy synth;
  std::thread audioThread;
  std::thread midiThread;
  std::thread synthThread;
};
} // namespace muza