#include "menu.h"
#include <algorithm>
#include <u8g2.h>

#define MENU_ITEM_HEIGHT 8

void Menu::render(u8g2_t* u8g2_, uint8_t xStart, uint8_t yStart, uint8_t width, uint8_t height)
{
  this->width = width;
  this->height = height;

  uint8_t maxVisibleItems = height / MENU_ITEM_HEIGHT;

  uint8_t itemsToRender = std::min(maxVisibleItems, uint8_t(this->itemCount - currentScrollStart));

  for (uint8_t i = 0; i < itemsToRender; i++) {
    bool selected = this->selectedItem == (i + this->currentScrollStart);
    uint8_t yPosition = yStart + i * MENU_ITEM_HEIGHT;

    AbstractMenuItem* item = this->items[i + this->currentScrollStart];

    u8g2_SetDrawColor(u8g2_, selected ? 1 : 0);

    if (selected) {
      u8g2_DrawBox(u8g2_, xStart, yPosition, width, MENU_ITEM_HEIGHT);
    }

    u8g2_SetDrawColor(u8g2_, !selected ? 1 : 0);
    u8g2_DrawStr(u8g2_, xStart + 0, yPosition + MENU_ITEM_HEIGHT, item->get_label());

    uint8_t valueStringWidth = u8g2_GetStrWidth(u8g2_, item->get_string_representation());
    u8g2_DrawStr(u8g2_, xStart + width - valueStringWidth, yPosition + MENU_ITEM_HEIGHT, item->get_string_representation());
  }
}

void Menu::up()
{
  if (this->selectedItem > 0) {
    if (this->selectedItem - this->currentScrollStart == 1) { // keep scroll start one up
      this->currentScrollStart--;
    }

    this->selectedItem--;

    if (this->selectedItem == 0) {
      this->currentScrollStart = 0;
    }
  }
}

void Menu::down()
{
  uint8_t maxVisibleItems = height / MENU_ITEM_HEIGHT;
  if (this->selectedItem < this->itemCount - 1) {
    if (this->selectedItem - this->currentScrollStart == maxVisibleItems - 1) {
      this->currentScrollStart++;
    }

    this->selectedItem++;

    if (this->selectedItem >= this->itemCount - 1 - maxVisibleItems) { // last item
      this->currentScrollStart = this->itemCount - 1 - maxVisibleItems;
    }
  }
}
