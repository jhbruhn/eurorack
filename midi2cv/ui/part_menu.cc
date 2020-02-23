#include "part_menu.h"
#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include <u8g2.h>

static const char* kVoiceDetailStrings[] = { "S", "M", "L", "XL" };
static const char* kMidiChannelStrings[] = { "omni", "1", "2", "3", "4", "5", "6",
  "7", "8", "9", "10", "11", "12", "13",
  "14", "15", "16" };
static const char* kMidiInputStrings[] = { "omni", "usb", "midi" };

PartMenu::PartMenu()
    : item_voice_count("voice count", 1, 1, 4, 1)
    , item_voice_detail("voice detail", 0, kVoiceDetailStrings, 4)
    , item_midi_filter_enabled("MIDI filter", 1, "on", "off")
    , item_midi_channel("MIDI channel", 0, kMidiChannelStrings, 17)
    , item_midi_input("MIDI input", 0, kMidiInputStrings, 3)
    , item_midi_lowest_note("MIDI lowest", 0)
    , item_midi_highest_note("MIDI highest", 127)
{
  this->menu.add_item(&this->item_voice_count);
  this->menu.add_item(&this->item_voice_detail);
  this->menu.add_item(&this->item_midi_filter_enabled);
  this->menu.add_item(&this->item_midi_channel);
  this->menu.add_item(&this->item_midi_input);
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
