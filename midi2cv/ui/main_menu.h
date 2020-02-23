#pragma once

#include "part_menu.h"
#include "stmlib/stmlib.h"
#include <U8g2lib.h>

static const int kHeaderHeight = 13;
static const char* kPartNames[] = { "A", "B", "C", "D" };

template <size_t part_count>
class MainMenu {
  public:
  void back()
  {
    if (this->activePartMenu >= 0) {
      if (this->partMenus[this->activePartMenu].back())
        this->activePartMenu = -1;
    }
  };
  void enter()
  {
    if (this->activePartMenu >= 0) {
      if (this->partMenus[this->activePartMenu].enter())
        this->activePartMenu = -1;
    } else {
      this->activePartMenu = this->selectedPart;
    }
  };
  void up()
  {
    if (this->activePartMenu >= 0) {
      this->partMenus[this->activePartMenu].up();
    } else {
      this->selectedPart--;
      CONSTRAIN(this->selectedPart, 0, (int)part_count - 1);
    }
  };
  void down()
  {
    if (this->activePartMenu >= 0) {
      this->partMenus[this->activePartMenu].down();
    } else {
      this->selectedPart++;
      CONSTRAIN(this->selectedPart, 0, (int)part_count - 1);
    }
  };

  void render(U8G2* u8g2, int x, int y, int width, int height)
  {
    u8g2->setFont(/*u8g2_font_5x8_tf*/ u8g2_font_pcsenior_8u);
    for (size_t i = 0; i < part_count; i++) {
      u8g2->setFontMode(1);
      u8g2->setDrawColor(1);

      if (this->selectedPart == (int)i) {
        if (this->activePartMenu == (int)i) {
          u8g2->drawBox(x + 1 + i * (width / part_count), y + 1, (width / part_count) - 3, kHeaderHeight - 2);
        } else {
          u8g2->drawFrame(x + 1 + i * (width / part_count), y + 1, (width / part_count) - 3, kHeaderHeight - 2);
          u8g2->drawFrame(x + i * (width / part_count), y, (width / part_count) - 1, kHeaderHeight);
        }
      } else {
        u8g2->drawFrame(x + 1 + i * (width / part_count), y + 1, (width / part_count) - 3, kHeaderHeight - 2);
      }

      u8g2->setDrawColor(2);
      u8g2->drawStr(x + i * (width / part_count) + 5, y + 9, kPartNames[i]);
      u8g2->setDrawColor(1);
    }

    u8g2->drawHLine(0, kHeaderHeight + 1, width);

    this->partMenus[this->selectedPart].render(u8g2, x, y + kHeaderHeight + 3, width, height - kHeaderHeight - 3);
  }

  MainMenu(Part** parts)
      : partMenus()
      , activePartMenu(0)
      , selectedPart(0)
  {
    for (size_t i = 0; i < part_count; i++) { // This is quite hacky, but it works.. we call the constructor again, this time with our parameters (Part*), as we cant do so directly from the default constructor for the array (thanks c++...)
      new (&partMenus[i]) PartMenu(parts[i]);
    }
  };

  private:
  PartMenu partMenus[part_count];
  int activePartMenu;

  int selectedPart;
};
