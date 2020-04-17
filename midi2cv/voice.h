#pragma once

#include "stmlib/algorithms/note_stack.h"

const int kMaximumNoteStackSize = 16;

using namespace stmlib;

class Voice {
  public:
  Voice()
  {
    noteStack.Init();
  }

  void NoteOn(uint8_t note, uint8_t velocity);
  void NoteOff(uint8_t note, uint8_t velocity);
  void Aftertouch(uint8_t velocity);
  void ControlChange(uint8_t controller, uint8_t value);
  void ProgramChange(uint8_t program);
  void PitchBend(uint16_t pitch_bend);

  void Reset();

  float PitchOutputSemitones(); //


  private:
  NoteStack<kMaximumNoteStackSize> noteStack;
  uint16_t pitchBend;
};
