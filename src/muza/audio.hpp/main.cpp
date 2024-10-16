#include "muza/audio.hpp"
#include <alsa/pcm.h>
#include <iostream>
#include <stdexcept>
namespace muza {
Audio::Audio() {
  int code = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
  code =
      snd_pcm_set_params(handle, SND_PCM_FORMAT_FLOAT,
                         SND_PCM_ACCESS_RW_INTERLEAVED, 1, 48'000, 1, 500'000);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
}
Audio::~Audio() {
  int code = snd_pcm_drain(handle);
  if (code < 0) {
    std::cerr << snd_strerror(code);
  }
  code = snd_pcm_close(handle);
  if (code < 0) {
    std::cerr << snd_strerror(code);
  }
}
void Audio::thread() {}

} // namespace muza