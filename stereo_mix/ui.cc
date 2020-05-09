#include "ui.h"
#include "pot_controller.h"
#include <stm32f0xx_hal.h>

const int kLongPressDuration = 2000;
const int kShowChangedValueMilliseconds = 1000;

void UI::Poll()
{
  for (size_t i = 0; i < SWITCH_COUNT; i++) {
    if (switches->just_pressed(Switch(i))) {
      queue.AddEvent(CONTROL_SWITCH, i, 0);
      press_time[i] = HAL_GetTick();
      ignore_release[i] = false;
      for (size_t j = 0; j < kNumChannels * 2; j++)
        potControllers[j].Lock(i);
    }
    if (switches->pressed(Switch(i)) && !ignore_release[i]) {
      bool suppress_release_hidden_parameters = false;
      for (size_t j = 0; j < kNumChannels * 2; j++) {
        suppress_release_hidden_parameters |= potControllers[j].editing_hidden_parameter();
      }
      int32_t pressed_time = HAL_GetTick() - press_time[i];
      if (!suppress_release_hidden_parameters && pressed_time > kLongPressDuration) {
        queue.AddEvent(CONTROL_SWITCH, i, pressed_time);
        ignore_release[i] = true;
      }
    }
    if (switches->released(Switch(i))) {
      bool suppress_release_hidden_parameters = false;
      for (size_t j = 0; j < kNumChannels * 2; j++) {
        suppress_release_hidden_parameters |= potControllers[j].editing_hidden_parameter();
      }
      if (!suppress_release_hidden_parameters && !ignore_release[i]) {
        queue.AddEvent(
            CONTROL_SWITCH,
            i,
            system_clock.milliseconds() - press_time[i] + 1);
        ignore_release[i] = true;
      }
      for (size_t j = 0; j < kNumChannels * 2; j++)
        potControllers[j].Unlock();
    }
  }

  for (size_t i = 0; i < kNumChannels * 2; i++) {
    potControllers[i].ProcessControlRate(adc->value(ADC_GROUP_POT + i));
  }

  for (size_t i = 0; i < kNumChannels * 2; i++) {
    if (i >= kNumChannels) {
      processors[i - kNumChannels].set_pan_offset(adc->value(ADC_GROUP_POT + i) - 32767L);
    } else {
      processors[i].set_volume_offset(adc->value(ADC_GROUP_POT + i));
    }
    if (abs(previous_pot_values[i] - adc->value(ADC_GROUP_POT + i)) > 1900) {
      previous_pot_values[i] = adc->value(ADC_GROUP_POT + i);
      queue.AddEvent(CONTROL_POT, i, previous_pot_values[i]);
    }
  }
}

void UI::OnSwitchPressed(const Event& e)
{
}

void UI::OnPotChanged(const Event& e)
{
  if (e.control_id >= kNumChannels) {
    // a pan pot was touched!
    last_pan_pot_touch[e.control_id - kNumChannels] = system_clock.milliseconds();
  } else {
    // a vol pot was touched!
    last_vol_pot_touch[e.control_id] = system_clock.milliseconds();
  }
}

void UI::OnSwitchReleased(const Event& e)
{
  mute[e.control_id] = !mute[e.control_id];
  processors[e.control_id].set_muted(mute[e.control_id]);

  for (size_t i = 0; i < kNumChannels; i++) {
    last_pan_pot_touch[i] = last_vol_pot_touch[i] = 0;
  }
}

void UI::TaskProcessPotControllers()
{
  for (size_t i = 0; i < kNumChannels; i++) {
    potControllers[i].ProcessUIRate();
    potControllers[i + kNumChannels].ProcessUIRate();
  }
}

void UI::TaskDrawLeds()
{
  for (size_t i = 0; i < kNumChannels; i++) {
    if (potControllers[i].editing_hidden_parameter()) {
      leds->set_intensity(i, abs(volume_att_pots[i] - 32767) >> 7);
      leds->set_blinking(i, volume_att_pots[i] - 32767 < 0);
    } else if (potControllers[i + kNumChannels].editing_hidden_parameter()) {
      leds->set_intensity(i, abs(pan_att_pots[i] - 32767) >> 7);
      leds->set_blinking(i, pan_att_pots[i] - 32767 < 0);
    } else {
      if (system_clock.milliseconds() - last_vol_pot_touch[i] < kShowChangedValueMilliseconds) {
        // show volume
        leds->set_intensity(i, volume_pots[i] >> 8);
        leds->set_blinking(i, false);
      } else if (system_clock.milliseconds() - last_pan_pot_touch[i] < kShowChangedValueMilliseconds) {
        // show panning
        leds->set_intensity(i, abs(pan_pots[i] - 32767) >> 7);
        leds->set_blinking(i, pan_pots[i] - 32767 < 0);
      } else {
        // show volume if not muted
        leds->set_intensity(i, processors[i].linear_volume() >> (8));
        leds->set_blinking(i, false);
      }
    }
  }
}

void UI::TaskProcessEvents()
{
  while (queue.available()) {
    Event ev = queue.PullEvent();
    switch (ev.control_type) {
    case CONTROL_SWITCH:
      if (ev.data != 0) {
        OnSwitchReleased(ev);
      } else {
        OnSwitchPressed(ev);
      }
      break;
    case CONTROL_POT:
      OnPotChanged(ev);
    default:
      break;
    }
  }
}

void UI::DoEvents()
{
  switch (ui_task) {
  case 1:
    TaskProcessEvents();
    break;
  case 2:
    TaskDrawLeds();
    break;
  case 3:
    TaskProcessPotControllers();
    break;
  default:
    ui_task = 0;
    break;
  }
  ui_task++;
}
