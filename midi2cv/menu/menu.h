#pragma once

#include "menu_items.h"

#include <U8g2lib.h>

#define MAXIMUM_MENU_ITEM_COUNT 16

class Menu {
  private:
  AbstractMenuItem* items[MAXIMUM_MENU_ITEM_COUNT];
  AbstractMenuItem* visibleItems[MAXIMUM_MENU_ITEM_COUNT];
  uint8_t itemCount;
  uint8_t visibleItemCount;
  uint8_t selectedVisibleItem;
  uint8_t currentVisibleScrollStart; // index we start rendering the menu from (for scrolling)
  int8_t currentEditingVisibleItem;

  uint8_t width, height;

  void update_visible_items();

  public:
  Menu()
      : selectedVisibleItem(0)
      , currentVisibleScrollStart(0)
      , currentEditingVisibleItem(-1)
      , width(10)
      , height(10) {};

  void up();
  void down();
  bool back();  // returns true true if nothing happened here and the action can be delegated to up
  bool enter(); // returns true if it wants to give up control
  void add_item(AbstractMenuItem* item)
  {
    if (itemCount < MAXIMUM_MENU_ITEM_COUNT) {
      items[itemCount++] = item;
    }
    this->update_visible_items();
  }

  void render(U8G2* u8g2_, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
};
