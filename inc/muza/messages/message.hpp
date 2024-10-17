#pragma once
namespace muza {
enum class MessageType { Exit, Message, NoteOff, NoteOn, PedalOff, PedalOn };
class Message {
public:
  Message(MessageType type);
  ~Message();
  MessageType getType();

protected:
  MessageType type;
};
} // namespace muza