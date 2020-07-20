#pragma once

#include "stmlib/stmlib.h"
#include "stmlib/system/storage.h"
#include "config.h"

#define SETTINGS_START (0x08001800)
#define SETTINGS_END (0x08002000)

struct ChannelData {
  bool mute;
  int16_t vol_att;
  int16_t pan_att;
  uint8_t padding[3];
};

struct PersistentData {
  uint8_t honor;
  uint8_t padding[7];
  enum { tag = 0x494C4143 }; // CALI
};

struct State {
  ChannelData channel_datas[CHANNEL_COUNT];
  //uint8_t padding[4];
  enum { tag = 0x54415453 }; // STAT
};

class Settings {
  public:
  Settings();
  ~Settings() {}

  void SavePersistentData();
  void SaveState();

  inline const State& state() const
  {
    return state_;
  }

  inline State* mutable_state()
  {
    return &state_;
  }

  inline const ChannelData& channel(int i) const
  {
    return state_.channel_datas[i];
  }

  inline ChannelData* mutable_channel(int i)
  {
    return &state_.channel_datas[i];
  }

  inline bool is_first_start() {
    return this->first_start;
  }

  private:
  bool first_start;
  PersistentData persistent_data_;
  State state_;

  stmlib::ChunkStorage<
      SETTINGS_START,
      SETTINGS_END,
      PersistentData,
      State>
      chunk_storage_;

  DISALLOW_COPY_AND_ASSIGN(Settings);
};

