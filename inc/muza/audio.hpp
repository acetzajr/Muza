#pragma once
#include "muza/tsbool.hpp"
#include <alsa/asoundlib.h>
#include <vector>
namespace muza {
class Audio {
public:
  Audio();
  ~Audio();
  void thread();
  void terminate();

private:
  TSBool running;
  std::vector<float> buffer;
  snd_pcm_t *handle;
  snd_pcm_uframes_t bufferSize;
  snd_pcm_uframes_t periodSize;
};
} // namespace muza