#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class NoteMessage : public Message {
public:
  NoteMessage(int key, int velocity);
  virtual MessageType type() override;

public:
  int key;
  int velocity;
};
} // namespace muza