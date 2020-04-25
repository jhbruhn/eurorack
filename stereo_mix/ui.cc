#include "ui.h"
#include "pot_controller.h"
#include <stm32f0xx_hal.h>

const int kLongPressDuration = 2000;

void UI::Poll()
{
  for (size_t i = 0; i < SWITCH_COUNT; i++) {
    if (switches->just_pressed(Switch(i))) {
      queue.AddEvent(CONTROL_SWITCH, i, 0);
      press_time[i] = HAL_GetTick();
      ignore_release[i] = false;
      potControllers[0].Lock();
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
      potControllers[0].Unlock();
    }
  }

  for (size_t i = 0; i < kNumChannels * 2; i++) {
    potControllers[i].ProcessControlRate(adc->value(ADC_GROUP_POT + i));
  }
}

void UI::OnSwitchPressed(const Event& e)
{
}

void UI::OnSwitchReleased(const Event& e)
{
  mute[e.control_id] = !mute[e.control_id];
}

void UI::DoEvents()
{
  for (size_t i = 0; i < kNumChannels * 2; i++) {
    potControllers[i].ProcessUIRate();

    if (potControllers[i].editing_hidden_parameter()) {
      leds->set_intensity(i, abs(volume_att_pots[i] - 32767) >> 7);
      leds->set_blinking(i, volume_att_pots[i] - 32767 < 0);
    } else {
      leds->set_intensity(i, mute[i] ? 0 : volume_pots[i] >> 8);
      leds->set_blinking(i, false);
    }
  }
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
    default:
      break;
    }
  }
}
