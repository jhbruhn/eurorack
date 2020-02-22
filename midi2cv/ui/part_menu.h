#pragma once

#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include <u8g2.h>

class PartMenu {
  public:
  PartMenu();

  bool enter();
  bool back();
  void up();
  void down();

  void render(u8g2_t* u8g2, int x, int y, int width, int height);

  private:
  Menu menu;
  UIntMenuItem item1;
  UIntMenuItem item2;
  UIntMenuItem item3;
  UIntMenuItem item4;
  UIntMenuItem item5;
};
