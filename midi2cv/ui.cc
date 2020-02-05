#include "ui.h"
#include "drivers/display.h"
#include "midi2cv/drivers/encoder.h"
#include "midi2cv/menu/menu.h"
#include "midi2cv/menu/menu_items.h"
#include "part.h"
#include "stmlib/utils/random.h"
#include <u8g2.h>

using namespace stmlib;

#define HEADER_HEIGHT 16

const char part_names[4][2] = { "A", "B", "C", "D" };

Menu menu(128, 64);
UIntMenuItem item1("wolfgang", 0, 0, 100, 1);
UIntMenuItem item2("joerg", 0, 0, 100, 1);
UIntMenuItem item3("ralle", 0, 0, 100, 1);
UIntMenuItem item4("ralle1", 0, 0, 100, 1);
UIntMenuItem item5("ralle2", 0, 0, 100, 1);
UIntMenuItem item6("ralle3", 0, 0, 100, 1);
UIntMenuItem item7("ralle4", 0, 0, 100, 1);

void UI::Init()
{
  input_queue.Init();

  menu.add_item((AbstractMenuItem*)&item1);
  menu.add_item((AbstractMenuItem*)&item2);
  menu.add_item((AbstractMenuItem*)&item3);
  menu.add_item((AbstractMenuItem*)&item4);
  menu.add_item((AbstractMenuItem*)&item5);
  menu.add_item((AbstractMenuItem*)&item6);
  menu.add_item((AbstractMenuItem*)&item7);
}

void UI::Poll()
{
  encoder.Debounce();
  int32_t increment = encoder.increment();
  if (increment != 0) {
    input_queue.AddEvent(CONTROL_ENCODER, 0, increment);
  }
}

void UI::Draw()
{
  u8g2_ClearBuffer(display.u8g2());

  switch (current_menu) {
  case MENU_PART_1:
  case MENU_PART_2:
  case MENU_PART_3:
  case MENU_PART_4:
    //DrawHeader();
    //DrawPartMenu(current_menu);
    menu.render(display.u8g2(), 0, 0, 128, 64);
    break;
  default:

    break;
  }

  display.Swap();
}

void UI::DrawHeader()
{
  u8g2_SetFont(display.u8g2(), u8g2_font_6x12_tf);
  for (int i = 0; i < PART_COUNT; i++) {
    u8g2_SetFontMode(display.u8g2(), 1);
    u8g2_SetDrawColor(display.u8g2(), 1);
    if (current_menu == i)
      u8g2_DrawBox(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT), 0, (DISPLAY_WIDTH / PART_COUNT) - 1, HEADER_HEIGHT);
    else
      u8g2_DrawFrame(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT), 0, (DISPLAY_WIDTH / PART_COUNT) - 1, HEADER_HEIGHT);

    u8g2_SetDrawColor(display.u8g2(), 2);
    u8g2_DrawStr(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT) + 5, 2 + 10, part_names[i]);
    u8g2_SetDrawColor(display.u8g2(), 1);
  }
}

void UI::DrawPartMenu(Menu_t menu)
{
}

void UI::Flush()
{
  display.Flush();
}

bool UI::DoEvents()
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

  return refresh_display;
}

void UI::OnClick()
{
}

void UI::OnLongClick()
{
}

void UI::OnIncrement(Event& e)
{
  if (e.data > 0)
    menu.down();
  else
    menu.up();
  //current_menu = (Menu_t) (((uint32_t)current_menu + e.data) % MENU_COUNT);
}
