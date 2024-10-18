#pragma once
#include "muza/buffer.hpp"
#include "muza/messages/message.hpp"
#include "muza/scale.hpp"
#include "muza/synths/acetzaSy/keyState.hpp"
#include "muza/tsPop.hpp"
#include "muza/tsQueue.hpp"
#include <array>
#include <mutex>
namespace muza {
class AcetzaSy {
public:
  AcetzaSy(TSQueue<Message *> *messages, TSQueue<Buffer *> *buffers);
  void thread();
  void bufferThread();
  void noteOn(int key, int velocity);
  void noteOff(int key);
  void pedalOn();
  void pedalOff();
  bool pedalState();

private:
  std::mutex mutex;
  bool pedal{false};
  std::array<acetzaSy::KeyState, 128> states;
  Scale scale;
  TSPop<Message *> messages;
  TSPop<Buffer *> buffers;
};
} // namespace muza