#pragma once

#include "config.h"
#include "part.h"
#include "stmlib/stmlib.h"
#include "stmlib/system/storage.h"

struct PersistentData {
  uint8_t honor;
  uint8_t padding[7];
  enum { tag = 0x494C4143 }; // CALI
};

struct State {
  PartData part_datas[PART_COUNT];
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

  inline const PartData& part(int i) const
  {
    return state_.part_datas[i];
  }

  inline PartData* mutable_part(int i)
  {
    return &state_.part_datas[i];
  }

  inline bool is_first_start() {
    return this->first_start;
  }

  private:
  bool first_start;
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
