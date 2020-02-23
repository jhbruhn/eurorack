#include "ui.h"
#include "ui/main_menu.h"
#include "drivers/display.h"
#include "midi2cv/drivers/encoder.h"
#include "midi2cv/menu/menu.h"
#include "midi2cv/menu/menu_items.h"
#include "part.h"
#include "stmlib/utils/random.h"
#include <u8g2.h>

using namespace stmlib;

#define HEADER_HEIGHT 14
const uint32_t kEncoderLongPressTime = 600;

MainMenu mainMenu;

void UI::Init()
{
  input_queue.Init();
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
  u8g2_ClearBuffer(display.u8g2());

  mainMenu.render(display.u8g2(), 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  display.Swap();
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
  mainMenu.enter();
}

void UI::OnLongClick()
{
  mainMenu.back();
}

void UI::OnIncrement(Event& e)
{
  if (e.data > 0)
    mainMenu.down();
  else
    mainMenu.up();
  //current_menu = (Menu_t) (((uint32_t)current_menu + e.data) % MENU_COUNT);
}
