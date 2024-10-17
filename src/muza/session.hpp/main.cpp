#include "muza/audio.hpp"
#include "muza/midi.hpp"
#include "muza/session.hpp"
#include <iostream>
namespace muza {
Session::Session()
    : audio(), midi("hw:3,0,0"), audioThread(&Audio::thread, &audio),
      midiThread(&Midi::thread, &midi) {
  std::cout << "Session started\n";
}
Session::~Session() {
  midi.terminate();
  midiThread.join();
  audio.terminate();
  audioThread.join();
  std::cout << "Session ended\n";
}
void Session::wait() {
  std::cout << "Press enter to terminate...\n";
  std::cin.get();
}
} // namespace muza