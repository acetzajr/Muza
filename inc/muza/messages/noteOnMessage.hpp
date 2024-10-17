#pragma once
#include "muza/messages/noteMessage.hpp"
namespace muza {
class NoteOnMessage : public NoteMessage {
public:
  NoteOnMessage(int key, int velocity);
  virtual MessageType type() override;
};
} // namespace muza