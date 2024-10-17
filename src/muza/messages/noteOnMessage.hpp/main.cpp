#include "muza/messages/message.hpp"
#include "muza/messages/noteMessage.hpp"
#include "muza/messages/noteOnMessage.hpp"
namespace muza {
NoteOnMessage::NoteOnMessage(int key, int velocity)
    : NoteMessage(key, velocity) {}
MessageType NoteOnMessage::type() { return MessageType::NoteOn; }
} // namespace muza