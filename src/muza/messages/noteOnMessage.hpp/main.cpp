#include "muza/messages/message.hpp"
#include "muza/messages/noteOnMessage.hpp"
namespace muza {
NoteOnMessage::NoteOnMessage(int key, int velocity)
    : Message(MessageType::NoteOn), key(key), velocity(velocity) {}
int NoteOnMessage::getKey() { return key; }
int NoteOnMessage::getVelocity() { return velocity; }
} // namespace muza