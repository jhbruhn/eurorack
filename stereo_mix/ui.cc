#include "ui.h"
#include "pot_controller.h"
#include <stm32f0xx_hal.h>

const int kLongPressDuration = 2000;
const int kShowChangedValueMilliseconds = 600;

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
    if (i < kNumChannels) {
      processors[i].set_pan_offset(pan_pots[i] - 32767);
      processors[i].set_volume_offset(volume_pots[i]);
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

    processors[i].set_volume_attenuverter(this->volume_att_pots[i] - 32767);
    processors[i].set_pan_attenuverter(this->pan_att_pots[i] - 32767);
  }
}

void UI::TaskDrawLeds()
{
  for (size_t i = 0; i < kNumChannels; i++) {
    if (potControllers[i].editing_hidden_parameter()) {
      leds->set_intensity_signed(i, volume_att_pots[i] - 32767);
    } else if (potControllers[i + kNumChannels].editing_hidden_parameter()) {
      leds->set_intensity_signed(i, pan_att_pots[i] - 32767);
    } else {
      // TODO: refactor
      if (system_clock.milliseconds() - last_pan_pot_touch[i] < kShowChangedValueMilliseconds) {
        // show panning
        leds->set_intensity_signed(i, pan_pots[i] - 32767);
      } else {
        // show volume if not muted
        leds->set_intensity_unsigned(i, processors[i].linear_volume(), processors[i].is_muted() ? LED_COLOR_RED : LED_COLOR_GREEN);
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
