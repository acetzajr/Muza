#pragma once
#include "muza/tsBool.hpp"
#include <alsa/asoundlib.h>
namespace muza {
class Midi {
public:
  Midi(const char *device);
  ~Midi();
  void thread();
  void terminate();

private:
  void process(unsigned char *message);

private:
  TSBool running;
  unsigned char buffer[1024];
  snd_rawmidi_t *midi;
};
} // namespace muza