#pragma once
#include <alsa/asoundlib.h>
namespace muza {
class Audio {
public:
  Audio();
  ~Audio();
  void thread();

private:
  snd_pcm_t *handle;
  snd_pcm_sframes_t frames;
};
} // namespace muza