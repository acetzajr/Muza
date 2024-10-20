#pragma once
namespace muza {
enum class MidiMessageType { Exit, NoteOff, NoteOn, PedalOff, PedalOn };
struct NoteMessage {
  int key;
  int velocity;
};
struct MidiMessage {
  MidiMessageType type;
  NoteMessage noteMessage;
};
} // namespace muza