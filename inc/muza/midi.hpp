#pragma once
#include "RtMidi.h"
#include "muza/messages/message.hpp"
#include "muza/tsBool.hpp"
#include "muza/tsPush.hpp"
#include "muza/tsQueue.hpp"
#include <alsa/asoundlib.h>
namespace muza {
namespace midi {
void callback(double timeStamp, std::vector<unsigned char> *message,
              void *userData);
void errorCallback(RtMidiError::Type type, const std::string &errorText,
                   void *userData);
} // namespace midi
class Midi {
public:
  Midi(TSQueue<Message *> *queue);
  void thread();
  void terminate();
  void process(unsigned char *message);

private:
  void printMessage(unsigned char *message);
  void sendNoteOff(unsigned char *message);
  void sendNoteOn(unsigned char *message);
  int getChannel(unsigned char *message);
  int getKey(unsigned char *message);
  int getVelocity(unsigned char *message);
  void sendPedalOff();
  void sendPedalOn();

private:
  RtMidiIn midiIn;
  TSPush<Message *> pusher;
  TSBool running;
  unsigned char buffer[1024];
  snd_rawmidi_t *midi;
  snd_rawmidi_t *midiOut;
};
} // namespace muza