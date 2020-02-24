#include "ui.h"
#include "drivers/display.h"
#include "midi2cv/drivers/encoder.h"
#include "midi2cv/menu/menu.h"
#include "midi2cv/menu/menu_items.h"
#include "part.h"
#include "settings.h"
#include "stmlib/utils/random.h"
#include "ui/main_menu.h"
#include <array>
#include <u8g2.h>

using namespace stmlib;

const uint32_t kEncoderLongPressTime = 600;

UI::UI(Part** part_pointers, Settings* settings)
    : main_menu(part_pointers)
    , parts(part_pointers)
{
  this->input_queue.Init();
  this->settings = settings;

  LoadState();
}

void UI::Poll()
{
  encoder.Debounce();

  if (encoder.just_pressed()) {
    encoder_press_time_ = system_clock.milliseconds();
    encoder_long_press_event_sent_ = false;
  }
  if (!encoder_long_press_event_sent_) {
    if (encoder.pressed()) {
      uint32_t duration = system_clock.milliseconds() - encoder_press_time_;
      if (duration >= kEncoderLongPressTime && !encoder_long_press_event_sent_) {
        input_queue.AddEvent(CONTROL_ENCODER_LONG_CLICK, 0, 0);
        encoder_long_press_event_sent_ = true;
      }
    }
    if (encoder.released()) {
      input_queue.AddEvent(CONTROL_ENCODER_CLICK, 0, 0);
    }
  }

  int32_t increment = encoder.increment();
  if (increment != 0) {
    input_queue.AddEvent(CONTROL_ENCODER, 0, increment);
  }
}

void UI::Draw()
{
  display.u8g2()->clearBuffer();

  main_menu.render(display.u8g2(), 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  display.Swap();
}

void UI::LoadState()
{
  for(size_t i = 0; i < PART_COUNT; i++)
    this->parts[i]->data = settings->part(i);
}

void UI::SaveState()
{
  for (size_t i = 0; i < PART_COUNT; i++) {
    *(settings->mutable_part(i)) = this->parts[i]->data;
  }

  settings->SaveState();
}

void UI::Flush()
{
  display.Flush();
}

void UI::DoEvents()
{
  bool refresh_display = false;
  while (input_queue.available()) {
    Event e = input_queue.PullEvent();
    if (e.control_type == CONTROL_ENCODER_CLICK) {
      OnClick();
    } else if (e.control_type == CONTROL_ENCODER_LONG_CLICK) {
      OnLongClick();
    } else if (e.control_type == CONTROL_ENCODER) {
      OnIncrement(e);
    }
    refresh_display = true;
  }

  if (input_queue.idle_time() > 1000) {
    refresh_display = true;
  }

  if (refresh_display) {
    input_queue.Touch();
    Draw();
  }
}

void UI::OnClick()
{
  main_menu.enter();
}

void UI::OnLongClick()
{
  main_menu.back();
}

void UI::OnIncrement(Event& e)
{
  if (e.data > 0)
    main_menu.down();
  else
    main_menu.up();

  SaveState();
}
