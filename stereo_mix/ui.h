#pragma once

#include "drivers/adc.h"
#include "drivers/leds.h"
#include "drivers/switches.h"
#include "pot_controller.h"
#include "processor.h"
#include "stmlib/ui/event_queue.h"

using namespace stmlib;

extern const uint8_t kNumChannels; // TODO

class UI {
  public:
  UI(Adc* adc_, Switches* switches_, Leds* leds_, Processor* processors_)
      : adc(adc_)
      , switches(switches_)
      , leds(leds_)
      , processors(processors_)
  {
    queue.Init();

  };
  void Init() {
    for (size_t i = 0; i < kNumChannels; i++) {
      uint16_t* volume_hidden_params[kNumChannels] = {&volume_att_pots[i], &volume_att_pots[i], &volume_att_pots[i], &volume_att_pots[i]};
      potControllers[i].Init(&volume_pots[i], volume_hidden_params);
      uint16_t* pan_hidden_params[kNumChannels] = {&pan_att_pots[i], &pan_att_pots[i], &pan_att_pots[i], &pan_att_pots[i]};
      potControllers[i + kNumChannels].Init(&pan_pots[i], pan_hidden_params);

      volume_att_pots[i] = pan_att_pots[i] = 32767 + (32767 / 2);
    }

  }
  void Poll();
  void DoEvents();

  private:
  void OnSwitchPressed(const Event&);
  void OnSwitchReleased(const Event&);
  void OnPotChanged(const Event&);

  void TaskProcessEvents(void);
  void TaskDrawLeds(void);
  void TaskProcessPotControllers(void);

  uint8_t ui_task = 0;

  EventQueue<> queue;
  uint32_t press_time[SWITCH_COUNT];
  bool ignore_release[SWITCH_COUNT];
  Adc* adc;
  Switches* switches;
  Leds* leds;

  Processor* processors;

  uint16_t previous_pot_values[kNumChannels * 2];

  uint16_t volume_pots[kNumChannels];
  uint16_t pan_pots[kNumChannels];
  uint16_t volume_att_pots[kNumChannels];
  uint16_t pan_att_pots[kNumChannels];
  bool mute[kNumChannels];

  uint32_t last_pan_pot_touch[kNumChannels];
  uint32_t last_vol_pot_touch[kNumChannels];

  PotController<kNumChannels> potControllers[kNumChannels * 2]; // todo: count
};
