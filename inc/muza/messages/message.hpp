#pragma once
namespace muza {
enum class MessageType { Note, NoteOff, NoteOn };
class Message {
public:
  virtual MessageType type() = 0;
};
} // namespace muza