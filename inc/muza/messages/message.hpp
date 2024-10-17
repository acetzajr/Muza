#pragma once
namespace muza {
enum class MessageType {
  Message,
  Note,
  NoteOff,
  NoteOn,
  Pedal,
  PedalOff,
  PedalOn
};
class Message {
public:
  virtual MessageType type();
};
} // namespace muza