#pragma once
#include "muza/messages/pedalMessage.hpp"
namespace muza {
class PedalOffMessage : public PedalMessage {
public:
  virtual MessageType type() override;
};
} // namespace muza