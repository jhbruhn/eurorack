#pragma once

#include "menu_items.h"

#include <u8g2.h>

#define MAXIMUM_MENU_ITEM_COUNT 16

class Menu {
  private:
  AbstractMenuItem* items[MAXIMUM_MENU_ITEM_COUNT];
  uint8_t itemCount;
  uint8_t selectedItem;
  uint8_t currentScrollStart; // index we start rendering the menu from (for scrolling)
  int8_t currentEditingItem;
  uint8_t width, height;

  public:
  Menu(uint8_t width_, uint8_t height_)
      : selectedItem(0)
      , currentScrollStart(0)
      , currentEditingItem(-1)
      , width(width_)
      , height(height_) {};

  void up();
  void down();
  bool back(); // returns true true if nothing happened here and the action can be delegated to up
  bool enter(); // returns true if it wants to give up control

  void add_item(AbstractMenuItem* item)
  {
    if (itemCount < MAXIMUM_MENU_ITEM_COUNT) {
      items[itemCount++] = item;
    }
  }

  void render(u8g2_t* u8g2_, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
};
