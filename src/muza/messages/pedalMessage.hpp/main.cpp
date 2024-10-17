#include "muza/messages/message.hpp"
#include "muza/messages/pedalMessage.hpp"
namespace muza {
MessageType PedalMessage::type() { return MessageType::Pedal; }
} // namespace muza