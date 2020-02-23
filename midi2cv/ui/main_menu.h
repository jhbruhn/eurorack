#pragma once

#include "../config.h"
#include "part_menu.h"
#include <U8g2lib.h>

class MainMenu {
  public:
  void back();
  void enter();
  void up();
  void down();

  void render(U8G2* u8g2, int x, int y, int width, int height);

  MainMenu()
      : activePartMenu(0)
      , selectedPart(0) {};

  private:
  PartMenu partMenus[PART_COUNT];
  int activePartMenu;

  int selectedPart;
};
