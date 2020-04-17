#include "part.h"

bool Part::is_message_handled(uint8_t channel, uint8_t note) // TODO: add origin
{
  if (this->part_data().midi_filter_channel_enabled && channel != this->part_data().midi_filter_channel)
    return false;
  if (this->part_data().midi_filter_lowest_note > note || this->part_data().midi_filter_highest_note < note)
    return false;
  return true;
}

bool Part::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  if (!is_message_handled(channel, note))
    return false;

  if (velocity == 0)
    return NoteOff(channel, note, velocity);

  uint8_t voiceIndex = 0;
  if (this->part_data().part_voice_count > 1) { // only use voiceallocator for polyphonic config
    voiceIndex = voiceAllocator.NoteOn(note);
  }

  Voice* voice = &voices[voiceIndex];

  voice->NoteOn(note, velocity);

  return true;
}

bool Part::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  if (!is_message_handled(channel, note))
    return false;

  uint8_t voiceIndex = 0;
  if (this->part_data().part_voice_count > 1) { // only use voiceallocator for polyphonic config
    voiceIndex = voiceAllocator.NoteOff(note);
  }

  Voice* voice = &voices[voiceIndex];
  voice->NoteOff(note, velocity);

  return true;
}

bool Part::PitchBend(uint8_t channel, uint16_t pitch_bend)
{
  if (!is_message_handled(channel, this->part_data().midi_filter_lowest_note))
    return false;

  for (size_t i = 0; i < this->part_data().part_voice_count; i++)
    voices[i].PitchBend(pitch_bend);

  return true;
}

bool Part::Aftertouch(uint8_t channel, uint8_t note, uint8_t velocity) {
  if(!is_message_handled(channel, note)) return false;

  uint8_t voiceIndex = 0;
  if(this->part_data().part_voice_count > 1)
    voiceIndex = this->voiceAllocator.Find(note);
  voices[voiceIndex].Aftertouch(velocity);

  return true;
}

bool Part::Aftertouch(uint8_t channel, uint8_t velocity) {
  if(!is_message_handled(channel, this->part_data().midi_filter_lowest_note)) return false;

  for(size_t i = 0; i < this->part_data().part_voice_count; i++)
    voices[i].Aftertouch(velocity);

  return true;
}
