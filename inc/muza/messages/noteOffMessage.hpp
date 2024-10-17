#pragma once
#include "muza/messages/message.hpp"
namespace muza {
class NoteOffMessage : public Message {
public:
  NoteOffMessage(int key, int velocity);
  int getKey();
  int getVelocity();

private:
  int key;
  int velocity;
};
} // namespace muza