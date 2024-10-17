#include "muza/messages/message.hpp"
#include "muza/messages/noteMessage.hpp"
#include "muza/messages/noteOffMessage.hpp"
namespace muza {
NoteOffMessage::NoteOffMessage(int key, int velocity)
    : NoteMessage(key, velocity) {}
MessageType NoteOffMessage::type() { return MessageType::NoteOff; }
} // namespace muza