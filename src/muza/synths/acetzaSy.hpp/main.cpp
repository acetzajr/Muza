#include "muza/messages/exitMessage.hpp"
#include "muza/messages/message.hpp"
#include "muza/messages/noteOnMessage.hpp"
#include "muza/synths/acetzaSy.hpp"
#include <iostream>
#include <memory>
namespace muza {
AcetzaSy::AcetzaSy(TSQueue<Message *> *messages, TSQueue<Buffer *> *buffers)
    : messages(messages), buffers(buffers) {}

void AcetzaSy::thread() {
  while (true) {
    std::unique_ptr<Message> message(messages.pop());
    std::cout << "Message received\n";
    if (message->getType() == MessageType::Exit) {
      return;
    }
    if (message->getType() == MessageType::NoteOn) {
      NoteOnMessage *noteOn = (NoteOnMessage *)message.get();
      std::cout << "key " << noteOn->getKey() << "\n";
      std::cout << "velocity " << noteOn->getVelocity() << "\n";
    }
  }
}
} // namespace muza