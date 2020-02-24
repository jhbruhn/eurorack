#pragma once

#include "config.h"
#include "part.h"
#include "stmlib/stmlib.h"
#include "stmlib/system/storage.h"

struct PersistentData {
  uint8_t honor;
  uint8_t padding[15];
  enum { tag = 0x494C4143 }; // CALI
};

struct PartState { // 8 bytes, TODO: can these be pointers to the actual values, or can we do some other copying magic?
  PartVoiceCount_t part_voice_count;
  PartVoiceDetail_t part_voice_detail;
  uint8_t midi_filter_channel_enabled;
  uint8_t midi_filter_channel;
  uint8_t midi_filter_lowest_note;
  uint8_t midi_filter_highest_note;
  MIDIInput_t midi_filter_input;
  MIDIThruMode_t midi_thru_mode;
};

struct State {
  PartState part_states[PART_COUNT]; // 4 * 8 bytes
  //uint8_t padding[4];
  enum { tag = 0x54415453 }; // STAT
};

class Settings {
  public:
  Settings();
  ~Settings() {}

  void SavePersistentData();
  void SaveState();

  /*inline const ChannelCalibrationData& calibration_data(int channel) const
  {
    return persistent_data_.channel_calibration_data[channel];
  }

  inline ChannelCalibrationData* mutable_calibration_data(int channel)
  {
    return &persistent_data_.channel_calibration_data[channel];
  }*/

  inline const State& state() const
  {
    return state_;
  }

  inline State* mutable_state()
  {
    return &state_;
  }

  inline const PartState& part(int i) const
  {
    return state_.part_states[i];
  }

  inline PartState* mutable_part(int i)
  {
    return &state_.part_states[i];
  }

  private:
  PersistentData persistent_data_;
  State state_;

  stmlib::ChunkStorage<
      0x08004000,
      0x08008000,
      PersistentData,
      State>
      chunk_storage_;

  DISALLOW_COPY_AND_ASSIGN(Settings);
};

extern Settings settings;
