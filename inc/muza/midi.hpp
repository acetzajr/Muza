#pragma once
#include "muza/types.hpp"
#include <alsa/asoundlib.h>
#include <mutex>
namespace muza {
class Midi {
public:
  Midi(const char *device);
  ~Midi();
  void thread();
  void terminate();
  bool isRunning();

private:
  bool running = true;
  byte buffer[1024];
  std::mutex mutex;
  snd_rawmidi_t *midi;
};
} // namespace muza