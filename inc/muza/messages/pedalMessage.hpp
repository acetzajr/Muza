#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class PedalMessage : public Message {
public:
  virtual MessageType type() override;
};
} // namespace muza