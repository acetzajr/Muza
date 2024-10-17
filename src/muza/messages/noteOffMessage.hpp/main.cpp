#include "muza/messages/noteOffMessage.hpp"
namespace muza {
NoteOffMessage::NoteOffMessage(int key, int velocity)
    : Message(MessageType::NoteOff), key(key), velocity(velocity) {}
int NoteOffMessage::getKey() { return key; }
int NoteOffMessage::getVelocity() { return velocity; }
} // namespace muza