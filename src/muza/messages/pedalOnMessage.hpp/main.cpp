#include "muza/messages/message.hpp"
#include "muza/messages/pedalOnMessage.hpp"
namespace muza {
MessageType PedalOnMessage::type() { return MessageType::PedalOn; }
} // namespace muza