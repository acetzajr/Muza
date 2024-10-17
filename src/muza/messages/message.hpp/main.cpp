#include "muza/messages/message.hpp"
namespace muza {
Message::Message(MessageType type) : type(type) {}
Message::~Message() {}
MessageType Message::getType() { return type; }
} // namespace muza