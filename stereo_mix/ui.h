#pragma once

#include "drivers/adc.h"
#include "drivers/leds.h"
#include "drivers/switches.h"
#include "pot_controller.h"
#include "processor.h"
#include "stmlib/ui/event_queue.h"
#include "config.h"
#include "settings.h"

using namespace stmlib;

const uint8_t kNumChannels = CHANNEL_COUNT;

class UI {
  public:
  UI(Adc* adc_, Switches* switches_, Leds* leds_, Processor* processors_, Settings* settings)
      : adc(adc_)
      , switches(switches_)
      , leds(leds_)
      , processors(processors_)
      , settings(settings)
  {
    queue.Init();
  };

  void Init() {
    LoadState();

    for (size_t i = 0; i < kNumChannels; i++) {
      uint16_t* volume_hidden_params[] = {&volume_att_pots[i], &volume_att_pots[i], &volume_att_pots[i], &volume_att_pots[i]};
      potControllers[i].Init(&volume_pots[i], volume_hidden_params);
      uint16_t* pan_hidden_params[] = {&pan_att_pots[i], &pan_att_pots[i], &pan_att_pots[i], &pan_att_pots[i]};
      potControllers[i + kNumChannels].Init(&pan_pots[i], pan_hidden_params);

      last_pan_pot_touch[i] = last_vol_pot_touch[i] = -1;
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

  void LoadState();
  void SaveState();

  uint8_t ui_task = 0;

  EventQueue<> queue;
  uint32_t press_time[SWITCH_COUNT];
  bool ignore_release[SWITCH_COUNT];
  Adc* adc;
  Switches* switches;
  Leds* leds;

  Processor* processors;

  Settings* settings;

  uint16_t previous_pot_values[kNumChannels * 2];

  uint16_t volume_pots[kNumChannels];
  uint16_t pan_pots[kNumChannels];
  uint16_t volume_att_pots[kNumChannels];
  uint16_t pan_att_pots[kNumChannels];
  bool mute[kNumChannels];

  int64_t last_pan_pot_touch[kNumChannels];
  int64_t last_vol_pot_touch[kNumChannels];
  bool pots_touched;

  PotController<kNumChannels> potControllers[kNumChannels * 2]; // todo: count
};
