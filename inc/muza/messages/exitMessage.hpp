#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class ExitMessage : public Message {
public:
  ExitMessage();
};
} // namespace muza