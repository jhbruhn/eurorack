#include "menu.h"
#include <algorithm>
#include <u8g2.h>

#define MENU_ITEM_HEIGHT 12

void Menu::render(u8g2_t* u8g2_, uint8_t xStart, uint8_t yStart, uint8_t width, uint8_t height)
{
  this->width = width;
  this->height = height;

  uint8_t maxVisibleItems = height / MENU_ITEM_HEIGHT;

  uint8_t itemsToRender = std::min(maxVisibleItems, uint8_t(this->itemCount - currentScrollStart));
  u8g2_SetFont(u8g2_, u8g2_font_6x12_tf);
  for (uint8_t i = 0; i < itemsToRender; i++) {
    bool selected = this->selectedItem == (i + this->currentScrollStart);
    bool editing = this->currentEditingItem == (i + this->currentScrollStart);
    uint8_t yPosition = yStart + i * MENU_ITEM_HEIGHT;

    AbstractMenuItem* item = this->items[i + this->currentScrollStart];

    u8g2_SetDrawColor(u8g2_, selected ? 1 : 0);

    if(editing) {
      u8g2_DrawFrame(u8g2_, xStart, yPosition, width, MENU_ITEM_HEIGHT);
    } else if (selected) {
      u8g2_DrawBox(u8g2_, xStart, yPosition, width, MENU_ITEM_HEIGHT);
    }

    u8g2_SetDrawColor(u8g2_, editing || !selected ? 1 : 0);
    u8g2_DrawStr(u8g2_, xStart + 2, yPosition + MENU_ITEM_HEIGHT - 3, item->get_label());

    uint8_t valueStringWidth = u8g2_GetStrWidth(u8g2_, item->get_string_representation());
    u8g2_DrawStr(u8g2_, xStart + width - valueStringWidth - 2, yPosition + MENU_ITEM_HEIGHT - 3, item->get_string_representation());
  }
}

void Menu::up()
{
  if (this->currentEditingItem >= 0) {
    this->items[this->selectedItem]->decrease();
  } else if (this->selectedItem > 0) {
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
  if (this->currentEditingItem >= 0) {
    this->items[this->selectedItem]->increase();
  } else {
    uint8_t maxVisibleItems = height / MENU_ITEM_HEIGHT;
    if (this->selectedItem < this->itemCount - 1) {
      if (this->selectedItem - this->currentScrollStart == maxVisibleItems - 2 && this->itemCount - this->currentScrollStart > maxVisibleItems) {
        this->currentScrollStart++;
      }

      this->selectedItem++;
    }
  }
}

void Menu::enter()
{
  if (this->currentEditingItem >= 0) {
    this->currentEditingItem = -1;
    return;
  }
  this->currentEditingItem = this->selectedItem;
}
