#include "part_menu.h"
#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include <u8g2.h>

PartMenu::PartMenu()
    : menu(128, 64)
    , item_voice_count("voice count", 1, 1, 4, 1)
    , item_voice_detail("voice detail", 1, 1, 4, 1)
    , item_midi_filter_enabled("MIDI filter", 0, "on", "off")
    , item_midi_channel("MIDI channel", 0, 0, 100, 1)
    , item_midi_lowest_note("MIDI lowest", 0)
    , item_midi_highest_note("MIDI highest", 127)
{
  this->menu.add_item(&this->item_voice_count);
  this->menu.add_item(&this->item_voice_detail);
  this->menu.add_item(&this->item_midi_filter_enabled);
  this->menu.add_item(&this->item_midi_channel);
  this->menu.add_item(&this->item_midi_lowest_note);
  this->menu.add_item(&this->item_midi_highest_note);
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
