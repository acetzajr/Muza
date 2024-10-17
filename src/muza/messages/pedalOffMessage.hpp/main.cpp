#include "muza/messages/message.hpp"
#include "muza/messages/pedalOffMessage.hpp"
namespace muza {
PedalOffMessage::PedalOffMessage() : Message(MessageType::PedalOff) {}
} // namespace muza