#include "muza/audio.hpp"
#include "muza/messages/exitMessage.hpp"
#include "muza/midi.hpp"
#include "muza/session.hpp"
#include "muza/synths/acetzaSy.hpp"
#include <iostream>
namespace muza {
Session::Session()
    : audio(&buffers, true), midi(&messages), synth(&messages, &buffers),
      audioThread(&Audio::thread, &audio), midiThread(&Midi::thread, &midi),
      synthThread(&AcetzaSy::thread, &synth) {
  std::cout << "Session started\n";
}
void Session::wait() {
  std::cout << "Press enter to terminate...\n";
  std::cin.get();
}
Session::~Session() {
  // messages.push(new NoteOnMessage(1, 2));
  buffers.push(nullptr);
  messages.push(new ExitMessage());
  synthThread.join();
  midi.terminate();
  midiThread.join();
  audio.terminate();
  audioThread.join();
  std::cout << "Session ended\n";
}
} // namespace muza