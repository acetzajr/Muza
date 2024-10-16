#pragma once
#include "muza/audio.hpp"
#include "muza/midi.hpp"
#include <thread>
namespace muza {
class Session {
public:
  Session();
  ~Session();
  void wait();

public:
  Audio audio;
  Midi midi;
  std::thread audioThread;
  std::thread midiThread;
};
extern Session session;
} // namespace muza