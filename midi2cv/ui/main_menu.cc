#include "main_menu.h"
#include "stmlib/stmlib.h"
#include <u8g2.h>

const int kHeaderHeight = 13;
const char* kPartNames[] = { "A", "B", "C", "D" };

void MainMenu::back()
{
  if (this->activePartMenu >= 0) {
    if (this->partMenus[this->activePartMenu].back())
      this->activePartMenu = -1;
  }
}

void MainMenu::enter()
{
  if (this->activePartMenu >= 0) {
    if (this->partMenus[this->activePartMenu].enter())
      this->activePartMenu = -1;
  } else {
    this->activePartMenu = this->selectedPart;
  }
}

void MainMenu::up()
{
  if (this->activePartMenu >= 0) {
    this->partMenus[this->activePartMenu].up();
  } else {
    this->selectedPart--;
    CONSTRAIN(this->selectedPart, 0, PART_COUNT - 1);
  }
}

void MainMenu::down()
{
  if (this->activePartMenu >= 0) {
    this->partMenus[this->activePartMenu].down();
  } else {
    this->selectedPart++;
    CONSTRAIN(this->selectedPart, 0, PART_COUNT - 1);
  }
}

void MainMenu::render(U8G2* u8g2, int x, int y, int width, int height)
{
  u8g2->setFont(/*u8g2_font_5x8_tf*/ u8g2_font_pcsenior_8u);
  for (int i = 0; i < PART_COUNT; i++) {
    u8g2->setFontMode(1);
    u8g2->setDrawColor(1);

    if (this->selectedPart == i) {
      if (this->activePartMenu == i) {
        u8g2->drawBox(x + 1 + i * (width / PART_COUNT), y + 1, (width / PART_COUNT) - 3, kHeaderHeight - 2);
      } else {
        u8g2->drawFrame(x + 1 + i * (width / PART_COUNT), y + 1, (width / PART_COUNT) - 3, kHeaderHeight - 2);
        u8g2->drawFrame(x + i * (width / PART_COUNT), y, (width / PART_COUNT) - 1, kHeaderHeight);
      }
    } else {
      u8g2->drawFrame(x + 1 + i * (width / PART_COUNT), y + 1, (width / PART_COUNT) - 3, kHeaderHeight - 2);
    }

    u8g2->setDrawColor(2);
    u8g2->drawStr(x + i * (width / PART_COUNT) + 5, y + 9, kPartNames[i]);
    u8g2->setDrawColor(1);
  }

  u8g2->drawHLine(0, kHeaderHeight + 1, width);

  this->partMenus[this->selectedPart].render(u8g2, x, y + kHeaderHeight + 3, width, height - kHeaderHeight - 3);
}
