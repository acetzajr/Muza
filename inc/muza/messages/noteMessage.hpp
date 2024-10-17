#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class NoteMessage : public Message {
public:
  NoteMessage(int key, int velocity);

public:
  int key;
  int velocity;
};
} // namespace muza