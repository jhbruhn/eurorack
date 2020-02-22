#include "part_menu.h"
#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include <u8g2.h>

PartMenu::PartMenu()
    : menu(128, 64)
    , item1("wolle", 0, 0, 100, 1)
    , item2("petry", 0, 0, 100, 1)
    , item3("schale", 0, 0, 100, 1)
    , item4("eine", 0, 0, 100, 1)
    , item5("schale?", 0, 0, 100, 1)
{
  this->menu.add_item(&this->item1);
  this->menu.add_item(&this->item2);
  this->menu.add_item(&this->item3);
  this->menu.add_item(&this->item4);
  this->menu.add_item(&this->item5);
}

void PartMenu::up()
{
  menu.up();
}

void PartMenu::down()
{
  menu.down();
}

bool PartMenu::back()
{
  if (menu.back())
    return true;
  return false;
}

bool PartMenu::enter()
{
  menu.enter();
  return false;
}

void PartMenu::render(u8g2_t* u8g2, int x, int y, int width, int height)
{
  menu.render(u8g2, x, y, width, height);
}
