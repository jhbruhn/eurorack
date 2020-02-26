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

  uint8_t itemIndex = this->currentScrollStart;

  for (uint8_t i = 0; i < itemsToRender; i++) {
    uint8_t yPosition = yStart + i * kMenuItemHeight;

    AbstractMenuItem* item;

    while (!(item = this->items[itemIndex])->visible()) {
      itemIndex++;
      if (itemIndex >= this->itemCount)
        break;
    }

    if (itemIndex >= this->itemCount)
      break;

    bool selected = this->selectedItem == itemIndex;
    bool editing = this->currentEditingItem == itemIndex;

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

    itemIndex++;
  }
}

void Menu::up()
{
  if (this->currentEditingItem >= 0) {
    // we store the amount of visible items before the counter before
    // changing and then compare afterwards to move the cursor back to
    // its intended position if necessary
    uint8_t visible_count_before = this->visible_item_count_before_selection();

    this->items[this->selectedItem]->decrease();

    uint8_t visible_count_after = this->visible_item_count_before_selection();

    this->selectedItem += visible_count_after - visible_count_before;
  } else if (this->selectedItem > 0) {
    uint8_t newItem = this->selectedItem;
    int8_t i;
    for (i = this->selectedItem - 1; i >= 0; i--) {
      if (this->items[i]->visible()) {
        newItem = i;
        break;
      }
    }

    if (newItem - this->currentScrollStart == i) { // keep scroll start one up
      this->currentScrollStart--;
    }

    this->selectedItem = newItem;

    if (this->selectedItem == 0) {
      this->currentScrollStart = 0;
    }
  }
}

void Menu::down()
{
  if (this->currentEditingItem >= 0) {
    uint8_t visible_count_before = this->visible_item_count_before_selection();

    this->items[this->selectedItem]->increase();

    uint8_t visible_count_after = this->visible_item_count_before_selection();

    this->selectedItem += visible_count_after - visible_count_before;
  } else {
    uint8_t maxVisibleItems = height / kMenuItemHeight;
    if (this->selectedItem < this->itemCount - 1) {
      if (this->items[this->selectedItem + 1]->visible()) {
        if (this->selectedItem - this->currentScrollStart == maxVisibleItems - 2 && this->itemCount - this->currentScrollStart > maxVisibleItems) {
          this->currentScrollStart++;
        }

        this->selectedItem++;
      } else {
        for (size_t i = this->selectedItem + 1; i < this->itemCount; i++) {
          if (this->items[i]->visible()) {
            this->selectedItem = i;
            break;
          }
        }
      }
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
