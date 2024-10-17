#include "muza/audio.hpp"
#include <alsa/pcm.h>
#include <iostream>
#include <stdexcept>
#include <vector>
namespace muza {
Audio::Audio() : running(true) {
  int code = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
  code =
      snd_pcm_set_params(handle, SND_PCM_FORMAT_FLOAT,
                         SND_PCM_ACCESS_RW_INTERLEAVED, 2, 48'000, 1, 10'000);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
  code = snd_pcm_get_params(handle, &bufferSize, &periodSize);
  if (code < 0) {
    throw std::runtime_error(snd_strerror(code));
  }
  std::cout << "bufferSize " << bufferSize << "\n";
  std::cout << "periodSize " << periodSize << "\n";
  buffer = std::vector<float>(bufferSize * 2, 0);
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
void Audio::terminate() { running.set(false); }
void Audio::thread() {
  while (running.get()) {
    snd_pcm_sframes_t count = snd_pcm_writei(handle, buffer.data(), bufferSize);
    if (count < 0) {
      count = snd_pcm_recover(handle, count, 0);
    }
    if (count < 0) {
      throw std::runtime_error((snd_strerror(count)));
    }
    if (count > 0 && count < (long)bufferSize) {
      std::cerr << "Short write (expected " << bufferSize << ", wrote " << count
                << ")\n";
    }
  }
  //
}
} // namespace muza