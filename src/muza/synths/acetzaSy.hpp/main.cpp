#include "muza/buffer.hpp"
#include "muza/frameRate.hpp"
#include "muza/midiMessage.hpp"
#include "muza/synths/acetzaSy.hpp"
#include "muza/synths/acetzaSy/keyState.hpp"
#include "muza/waveForms.hpp"
#include <cmath>
#include <mutex>
#include <thread>
namespace muza {
AcetzaSy::AcetzaSy(TSQueue<MidiMessage> *messages, TSQueue<Buffer *> *buffers)
    : messages(messages), buffers(buffers) {}
void AcetzaSy::processThread(int index) {
  // std::cout << "processThread " << index << "\n";
  TSQueue<KeyMessage> &keyQueue = keyQueues[index];
  while (true) {
    KeyMessage keyMessage = keyQueue.pop();
    if (keyMessage.buffer == nullptr) {
      break;
    }
    int key = keyMessage.key;
    Buffer *buffer = keyMessage.buffer;
    acetzaSy::KeyState &state = states[keyMessage.key];
    std::unique_lock<std::mutex> lock(*state.getMutex());
    float part{0};
    unsigned long long frame = state.getFrame();
    unsigned long long endFrame = frame + buffer->getFrames();
    for (int index = 0; frame < endFrame; ++frame) {
      float time = frameToTime(frame, 48'000);
      part = std::fmod(time * scale.frequencyOf(key), 1.0f);
      float sample = muza::saw(part) * 0.10f;
      writeQueue.push(Write{sample, index++});
      writeQueue.push(Write{sample, index++});
    }
    state.setFrame(frame);
    writeQueue.push(Write{0, -1});
  }
}
void AcetzaSy::bufferThread() {
  for (int i = 0; i < (int)processThreads.size(); ++i) {
    processThreads[i] = new std::thread(&AcetzaSy::processThread, this, i);
  }
  while (true) {
    Buffer *buffer = buffers.pop();
    // std::cout << "buffer received\n";
    if (buffer == nullptr) {
      break;
    }
    for (int key = 0, processCount = 0; key < (int)states.size(); ++key) {
      acetzaSy::KeyState &state = states[key];
      {
        std::unique_lock<std::mutex> lock(*state.getMutex());
        if (state.getPhase() == acetzaSy::KeyPhase::Idle ||
            state.getPhase() == acetzaSy::KeyPhase::Release) {
          continue;
        }
      }
      keyQueues[processCount++].push(KeyMessage{buffer, key});
      while (processCount > 0) {
        Write write = writeQueue.pop();
        int index = write.index;
        if (index < 0) {
          --processCount;
          continue;
        }
        float sample = write.sample;
        (*buffer)[index] += sample;
      }
    }
    buffer->setReady();
  }
  for (auto &keyQueue : keyQueues) {
    keyQueue.push(KeyMessage{nullptr, -1});
  }
  for (auto *thread : processThreads) {
    thread->join();
    delete thread;
  }
}
void AcetzaSy::thread() {
  std::thread bufferThread(&AcetzaSy::bufferThread, this);
  bool running = true;
  while (running) {
    MidiMessage message = messages.pop();
    // std::cout << "Message received\n";
    switch (message.type) {
    case MidiMessageType::Exit:
      running = false;
      break;
    case MidiMessageType::NoteOff:
      noteOff(message.noteMessage.key);
      break;
    case MidiMessageType::NoteOn:
      noteOn(message.noteMessage.key, message.noteMessage.velocity);
      break;
    case MidiMessageType::PedalOff:
      pedalOff();
      break;
    case MidiMessageType::PedalOn:
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