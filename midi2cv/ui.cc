#include "ui.h"
#include "drivers/display.h"
#include "part.h"
#include "stmlib/utils/random.h"
#include <u8g2.h>

using namespace stmlib;

#define HEADER_HEIGHT 16

const char part_names[4][2] = { "A", "B", "C", "D" };

void UI::Update()
{

  switch (current_menu) {
  case MENU_PART_1:
  case MENU_PART_2:
  case MENU_PART_3:
  case MENU_PART_4:
    DrawHeader();
    DrawPartMenu(current_menu);
    break;
  default:

    break;
  }
}

void UI::DrawHeader()
{
  for (int i = 0; i < PART_COUNT; i++) {
    u8g2_SetFontMode(display.u8g2(), 1);
    u8g2_SetDrawColor(display.u8g2(), 1);
    if (current_menu == i)
      u8g2_DrawBox(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT), 0, (DISPLAY_WIDTH / PART_COUNT), HEADER_HEIGHT);
    else
      u8g2_DrawFrame(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT), 0, (DISPLAY_WIDTH / PART_COUNT), HEADER_HEIGHT);

    u8g2_SetDrawColor(display.u8g2(), 2);
    u8g2_DrawStr(display.u8g2(), i * (DISPLAY_WIDTH / PART_COUNT) + 2, 2, part_names[i]);
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
