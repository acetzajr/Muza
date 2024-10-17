#pragma once
#include "muza/messages/noteMessage.hpp"
namespace muza {
class NoteOffMessage : public NoteMessage {
public:
  NoteOffMessage(int key, int velocity);
  virtual MessageType type() override;
};
} // namespace muza