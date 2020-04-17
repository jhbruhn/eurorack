#include "voice.h"
#include "stmlib/algorithms/note_stack.h"

using namespace stmlib;

void Voice::NoteOn(uint8_t note, uint8_t velocity)
{
  this->noteStack.NoteOn(note, velocity);
}

void Voice::NoteOff(uint8_t note, uint8_t velocity)
{
  this->noteStack.NoteOff(note);
}

void Voice::PitchBend(uint16_t pitch_bend)
{
  this->pitchBend = pitch_bend;
}

float Voice::PitchOutputSemitones()
{
  if (this->noteStack.size() == 0)
    return 0;

  NoteEntry note = this->noteStack.note_by_priority(NOTE_STACK_PRIORITY_LAST);

  // insanely temporary stuff ahead

  // ULTRA NAIVE pitch to cv assuming max value is 10V
  float semitones = note.note;

  float pitch_bend = (this->pitchBend - 32768.0) / 65536.0 * 2.0; // -1 to 1

  semitones += pitch_bend * 1.5f; // pitch bend range: 1.5 semitones

  return semitones;
};

void Voice::Reset()
{
  this->noteStack.Clear();
}
