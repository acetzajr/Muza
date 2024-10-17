#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class NoteOnMessage : public Message {
public:
  NoteOnMessage(int key, int velocity);
  int getKey();
  int getVelocity();

private:
  int key;
  int velocity;
};
} // namespace muza