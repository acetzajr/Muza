#pragma once
#include "muza/buffer.hpp"
#include "muza/midiMessage.hpp"
#include "muza/scale.hpp"
#include "muza/synths/acetzaSy/keyState.hpp"
#include "muza/tsPop.hpp"
#include "muza/tsQueue.hpp"
#include <array>
#include <mutex>
#include <thread>
namespace muza {
class AcetzaSy {
public:
  AcetzaSy(TSQueue<MidiMessage> *messages, TSQueue<Buffer *> *buffers);
  void thread();
  void bufferThread();
  void processThread(int index);
  void noteOn(int key, int velocity);
  void noteOff(int key);
  void pedalOn();
  void pedalOff();
  bool pedalState();

private:
  struct Write {
    float sample;
    int index;
  };
  struct KeyMessage {
    Buffer *buffer;
    int key;
  };

private:
  std::array<TSQueue<KeyMessage>, 8> keyQueues;
  TSQueue<Write> writeQueue;
  std::array<std::thread *, 8> processThreads;
  std::mutex mutex;
  bool pedal{false};
  std::array<acetzaSy::KeyState, 128> states;
  Scale scale;
  TSPop<MidiMessage> messages;
  TSPop<Buffer *> buffers;
};
} // namespace muza