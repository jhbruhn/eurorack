#include "menu.h"
#include <algorithm>
#include <u8g2.h>

const int kMenuItemHeight = 12;

void Menu::render(U8G2* u8g2_, uint8_t xStart, uint8_t yStart, uint8_t width, uint8_t height)
{
  this->width = width;
  this->height = height;

  uint8_t maxVisibleItems = height / kMenuItemHeight;

  uint8_t itemsToRender = std::min(maxVisibleItems, uint8_t(this->itemCount - currentScrollStart));
  u8g2_->setFont(u8g2_font_6x10_tf);
  for (uint8_t i = 0; i < itemsToRender; i++) {
    bool selected = this->selectedItem == (i + this->currentScrollStart);
    bool editing = this->currentEditingItem == (i + this->currentScrollStart);
    uint8_t yPosition = yStart + i * kMenuItemHeight;

    AbstractMenuItem* item = this->items[i + this->currentScrollStart];

    u8g2_->setDrawColor(selected ? 1 : 0);

    if (editing) {
      u8g2_->drawFrame(xStart, yPosition, width, kMenuItemHeight);
    } else if (selected) {
      u8g2_->drawBox(xStart, yPosition, width, kMenuItemHeight);
    }

    u8g2_->setDrawColor(editing || !selected ? 1 : 0);
    u8g2_->drawStr(xStart + 2, yPosition + kMenuItemHeight - 3, item->get_label());

    uint8_t valueStringWidth = u8g2_->getStrWidth(item->get_string_representation());
    u8g2_->drawStr(xStart + width - valueStringWidth - 2, yPosition + kMenuItemHeight - 3, item->get_string_representation());
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
    uint8_t maxVisibleItems = height / kMenuItemHeight;
    if (this->selectedItem < this->itemCount - 1) {
      if (this->selectedItem - this->currentScrollStart == maxVisibleItems - 2 && this->itemCount - this->currentScrollStart > maxVisibleItems) {
        this->currentScrollStart++;
      }

      this->selectedItem++;
    }
  }
}

bool Menu::enter()
{
  if (this->currentEditingItem >= 0) {
    this->currentEditingItem = -1;
    return true;
  }
  this->currentEditingItem = this->selectedItem;
  return false;
}

bool Menu::back()
{
  if (this->currentEditingItem >= 0) {
    this->currentEditingItem = -1;
    return false;
  }
  return true;
}
