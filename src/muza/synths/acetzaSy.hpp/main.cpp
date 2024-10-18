#include "muza/buffer.hpp"
#include "muza/frameRate.hpp"
#include "muza/messages/message.hpp"
#include "muza/messages/noteOffMessage.hpp"
#include "muza/messages/noteOnMessage.hpp"
#include "muza/synths/acetzaSy.hpp"
#include "muza/synths/acetzaSy/keyState.hpp"
#include "muza/waveForms.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
namespace muza {
AcetzaSy::AcetzaSy(TSQueue<Message *> *messages, TSQueue<Buffer *> *buffers)
    : messages(messages), buffers(buffers) {}
void AcetzaSy::bufferThread() {
  std::cout << "bufferThread\n";
  while (true) {
    Buffer *buffer = buffers.pop();
    // std::cout << "buffer received\n";
    if (buffer == nullptr) {
      return;
    }
    int frames = buffer->getFrames();
    for (int key = 0; key < (int)states.size(); ++key) {
      acetzaSy::KeyState &state = states[key];
      if (state.getPhase() == acetzaSy::KeyPhase::Idle) {
        continue;
      }
      int index{0};
      float initialPart{state.getPart()};
      float part{0};
      for (int frame = 0; frame < frames; ++frame) {
        float time = frameToTime(frame, 48'000);
        part = std::fmod(time * scale.frequencyOf(key), 1.0f);
        float sample = muza::sin(initialPart + part) * 0.5f;
        (*buffer)[index++] += sample;
        (*buffer)[index++] += sample;
      }
      state.setPart(initialPart + part);
    }
    buffer->setReady();
  }
}
void AcetzaSy::thread() {
  std::thread bufferThread(&AcetzaSy::bufferThread, this);
  NoteOnMessage *noteOnMessage;
  NoteOffMessage *noteOffMessage;
  bool running = true;
  while (running) {
    std::unique_ptr<Message> message(messages.pop());
    std::cout << "Message received\n";
    switch (message->getType()) {
    case MessageType::Exit:
      running = false;
      break;
    case MessageType::Message:
      break;
    case MessageType::NoteOff:
      noteOffMessage = (NoteOffMessage *)message.get();
      noteOff(noteOffMessage->getKey());
      break;
    case MessageType::NoteOn:
      noteOnMessage = (NoteOnMessage *)message.get();
      noteOn(noteOnMessage->getKey(), noteOnMessage->getVelocity());
      break;
    case MessageType::PedalOff:
      pedalOff();
      break;
    case MessageType::PedalOn:
      pedalOn();
      break;
    }
  }
  bufferThread.join();
}
void AcetzaSy::noteOn(int key, int velocity) { states[key].press(velocity); }
void AcetzaSy::noteOff(int key) { states[key].release(); }
void AcetzaSy::pedalOn() {
  std::unique_lock<std::mutex> lock(mutex);
  pedal = true;
}
void AcetzaSy::pedalOff() {
  std::unique_lock<std::mutex> lock(mutex);
  pedal = false;
}
bool AcetzaSy::pedalState() {
  std::unique_lock<std::mutex> lock(mutex);
  return pedal;
}
} // namespace muza