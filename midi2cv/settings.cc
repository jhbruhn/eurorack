#include "settings.h"
#include "midi2cv/part.h"

Settings::Settings()
{
  persistent_data_.honor = 1;

  for (int i = 0; i < PART_COUNT; i++) {
    PartState* part = &state_.part_states[i];

    part->midi_filter_channel = 1;
    part->midi_filter_channel_enabled = true;
    part->midi_filter_lowest_note = 0;
    part->midi_filter_highest_note = 127;
    part->midi_filter_input = MIDI_INPUT_OMNI;
    part->part_voice_count = VOICE_COUNT_1;
    part->part_voice_detail = VOICE_DETAIL_S;
  }

  /*bool success =*/chunk_storage_.Init(&persistent_data_, &state_);
}

void Settings::SavePersistentData()
{
  chunk_storage_.SavePersistentData();
}

void Settings::SaveState()
{
  chunk_storage_.SaveState();
}
