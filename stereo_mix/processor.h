#pragma once
#include "resources.h"

class Processor {
  public:
  Processor() {};

  void Process(int16_t cvs[], uint16_t* outs);

  inline void set_volume_offset(uint16_t volume_offset_)
  {
    volume_offset = volume_offset_;
  }

  inline void set_pan_offset(int16_t pan_offset_)
  {
    pan_offset = pan_offset_;
  }

  inline void set_muted(bool m)
  {
    mute = m;
  }

  uint16_t linear_volume() {
    return linear_vol;
  }

  private:
  uint16_t volume_offset = 0;
  int16_t pan_offset = 0;
  uint16_t previous_vol;
  uint16_t linear_vol;

  uint16_t log_exp_mix_cv  = 32767; // -> linear
  uint16_t log_exp_mix_pot = 0;

  bool mute = false;
};
