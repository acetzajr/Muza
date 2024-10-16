#pragma once
#include "muza/tsbool.hpp"
#include "muza/types.hpp"
#include <alsa/asoundlib.h>
namespace muza {
class Midi {
public:
  Midi(const char *device);
  ~Midi();
  void thread();
  void terminate();

private:
  TSBool running;
  byte buffer[1024];
  snd_rawmidi_t *midi;
};
} // namespace muza