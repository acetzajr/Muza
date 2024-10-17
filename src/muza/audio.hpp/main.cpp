#include "muza/audio.hpp"
#include "muza/buffer.hpp"
#include <alsa/pcm.h>
#include <iostream>
#include <stdexcept>
#include <vector>
namespace muza {
Audio::Audio() : index(0), running(true) {
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
  std::cout << "Buffer size: " << bufferSize << "\n";
  // std::cout << "Period size: " << periodSize << "\n";
  guardBuffer = Buffer(bufferSize);
  buffer = Buffer(bufferSize);
  buffers = std::vector<Buffer>(3);
  for (unsigned long i = 0; i < buffers.size(); ++i) {
    buffers[i] = Buffer(bufferSize);
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
void Audio::terminate() { running.set(false); }
void Audio::request(Buffer *buffer) {
  buffer->copyTo(this->buffer);
  buffer->use();
  queue.push(buffer);
  ++index;
  index %= buffers.size();
}
Buffer *Audio::getBuffer() {
  Buffer *current = &buffers[index];
  if (current->isReady()) {
    request(current);
    return &buffer;
  }
  return &guardBuffer;
}
void Audio::thread() {
  while (running.get()) {
    Buffer *buffer = getBuffer();
    snd_pcm_sframes_t count =
        snd_pcm_writei(handle, buffer->data(), bufferSize);
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