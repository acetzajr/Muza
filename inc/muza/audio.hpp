#pragma once
#include "muza/buffer.hpp"
#include "muza/tsBool.hpp"
#include "muza/tsPush.hpp"
#include "muza/tsQueue.hpp"
#include <alsa/asoundlib.h>
#include <sndfile.h>
#include <vector>
namespace muza {
class Audio {
public:
  Audio(TSQueue<Buffer *> *queue, bool save = false);
  ~Audio();
  void thread();
  void terminate();

private:
  Buffer *getBuffer();
  void request(Buffer *buffer);

private:
  int index;
  TSPush<Buffer *> pusher;
  TSBool running;
  std::vector<Buffer> buffers;
  Buffer buffer;
  Buffer guardBuffer;
  snd_pcm_t *handle;
  snd_pcm_uframes_t bufferSize;
  snd_pcm_uframes_t periodSize;
  bool save;
  SNDFILE *file;
};
} // namespace muza