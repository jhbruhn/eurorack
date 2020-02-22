#pragma once

#include "../config.h"
#include "part_menu.h"
#include <u8g2.h>

class MainMenu {
  public:
  void back();
  void enter();
  void up();
  void down();

  void render(u8g2_t* u8g2, int x, int y, int width, int height);

  MainMenu()
      : activePartMenu(-1)
      , selectedPart(0) {};

  private:
  PartMenu partMenus[PART_COUNT];
  int activePartMenu;

  int selectedPart;
};
