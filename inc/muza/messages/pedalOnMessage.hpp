#pragma once
#include "muza/messages/pedalMessage.hpp"
namespace muza {
class PedalOnMessage : public PedalMessage {
public:
  virtual MessageType type() override;
};
} // namespace muza