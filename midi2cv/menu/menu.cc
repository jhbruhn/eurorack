#include "menu.h"
#include <algorithm>
#include <u8g2.h>
const int kMenuItemHeight = 12;

void Menu::render(U8G2* u8g2_, uint8_t xStart, uint8_t yStart, uint8_t width, uint8_t height)
{
  this->width = width;
  this->height = height;

  uint8_t maxVisibleItems = height / kMenuItemHeight;

  uint8_t itemsToRender = std::min(maxVisibleItems, uint8_t(this->visibleItemCount - currentVisibleScrollStart));
  u8g2_->setFont(u8g2_font_6x10_tf);

  for (uint8_t i = 0; i < itemsToRender; i++) {
    uint8_t yPosition = yStart + i * kMenuItemHeight;

    uint8_t itemIndex = this->currentVisibleScrollStart + i;

    AbstractMenuItem* item = this->visibleItems[itemIndex];

    bool selected = this->selectedVisibleItem == itemIndex;
    bool editing = this->currentEditingVisibleItem == itemIndex;

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

void Menu::update_visible_items()
{
  // set all visibleItems to null
  this->visibleItemCount = 0;
  for (size_t i = 0; i < MAXIMUM_MENU_ITEM_COUNT; i++) {
    this->visibleItems[i] = NULL;
  }

  // find out which items are visible and only add these to the list.
  for (size_t i = 0; i < itemCount; i++) {
    if (this->items[i]->visible()) {
      this->visibleItems[this->visibleItemCount++] = this->items[i];
    }
  }
}

void Menu::up()
{
  this->update_visible_items();
  if (this->currentEditingVisibleItem >= 0) {
    // we store the amount of visible items before the counter before
    // changing and then compare afterwards to move the cursor back to
    // its intended position if necessary
    this->visibleItems[this->selectedVisibleItem]->decrease();

  } else if (this->selectedVisibleItem > 0) {
    uint8_t newItem = this->selectedVisibleItem - 1;

    if (newItem - this->currentVisibleScrollStart == 0) { // keep scroll start one up
      this->currentVisibleScrollStart--;
    }

    this->selectedVisibleItem = newItem;

    if (this->selectedVisibleItem == 0) {
      this->currentVisibleScrollStart = 0;
    }
  }
  this->update_visible_items();
}

void Menu::down()
{
  this->update_visible_items();
  if (this->currentEditingVisibleItem >= 0) {
    this->visibleItems[this->selectedVisibleItem]->increase();
  } else {
    uint8_t maxVisibleItems = height / kMenuItemHeight;
    if (this->selectedVisibleItem < this->visibleItemCount - 1) {
      if (this->selectedVisibleItem - this->currentVisibleScrollStart == maxVisibleItems - 2 && this->visibleItemCount - this->currentVisibleScrollStart > maxVisibleItems) {
        this->currentVisibleScrollStart++;
      }

      this->selectedVisibleItem++;
    }
  }
  this->update_visible_items();
}

bool Menu::enter()
{
  if (this->currentEditingVisibleItem >= 0) {
    this->currentEditingVisibleItem = -1;
    return true;
  }
  this->currentEditingVisibleItem = this->selectedVisibleItem;
  return false;
}

bool Menu::back()
{
  if (this->currentEditingVisibleItem >= 0) {
    this->currentEditingVisibleItem = -1;
    return false;
  }
  return true;
}
