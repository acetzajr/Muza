#pragma once
#include "muza/messages/message.hpp"
#include "muza/tsBool.hpp"
#include "muza/tsPush.hpp"
#include "muza/tsQueue.hpp"
#include <alsa/asoundlib.h>
namespace muza {
class Midi {
public:
  Midi(TSQueue<Message *> *queue, const char *device);
  ~Midi();
  void thread();
  void terminate();

private:
  void printMessage(unsigned char *message);
  void process(unsigned char *message);
  void sendNoteOff(unsigned char *message);
  void sendNoteOn(unsigned char *message);
  int getChannel(unsigned char *message);
  int getKey(unsigned char *message);
  int getVelocity(unsigned char *message);
  void sendPedalOff();
  void sendPedalOn();

private:
  TSPush<Message *> pusher;
  TSBool running;
  unsigned char buffer[1024];
  snd_rawmidi_t *midi;
};
} // namespace muza