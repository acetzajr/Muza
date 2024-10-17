#include "muza/messages/message.hpp"
#include "muza/messages/pedalOffMessage.hpp"
namespace muza {
MessageType PedalOffMessage::type() { return MessageType::PedalOff; }
} // namespace muza