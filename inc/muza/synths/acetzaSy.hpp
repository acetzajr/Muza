#pragma once
#include "muza/buffer.hpp"
#include "muza/messages/message.hpp"
#include "muza/scale.hpp"
#include "muza/tsPop.hpp"
#include "muza/tsQueue.hpp"
namespace muza {
class AcetzaSy {
public:
  AcetzaSy(TSQueue<Message *> *messages, TSQueue<Buffer *> *buffers);
  void thread();

private:
  Scale scale;
  TSPop<Message *> messages;
  TSPop<Buffer *> buffers;
};
} // namespace muza