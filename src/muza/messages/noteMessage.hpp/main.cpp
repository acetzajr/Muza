#include "muza/messages/message.hpp"
#include "muza/messages/noteMessage.hpp"
namespace muza {
NoteMessage::NoteMessage(int key, int velocity)
    : key(key), velocity(velocity) {}
MessageType NoteMessage::type() { return MessageType::Note; }
} // namespace muza