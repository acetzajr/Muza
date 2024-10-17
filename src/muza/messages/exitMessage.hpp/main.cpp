#include "muza/messages/exitMessage.hpp"
#include "muza/messages/message.hpp"
namespace muza {
ExitMessage::ExitMessage() : Message(MessageType::Exit) {}
} // namespace muza