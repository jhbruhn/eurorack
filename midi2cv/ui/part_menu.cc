#include "part_menu.h"
#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include <u8g2.h>

static const char* kVoiceDetailStrings[] = { "S", "M", "L", "XL" };
static const char* kMidiChannelStrings[] = { "omni", "1", "2", "3", "4", "5", "6",
  "7", "8", "9", "10", "11", "12", "13",
  "14", "15", "16" };
static const char* kMidiInputStrings[] = { "omni", "midi", "usb" };
static const char* kMidiThruStrings[] = { "off", "on", "polychain" };

PartMenu::PartMenu(Part* _part)
    : part(_part)
    , item_voice_count("voice count", (uint32_t*)&_part->part_voice_count, 1, 4, 1)
    , item_voice_detail("voice detail", (uint8_t*)&_part->part_voice_detail, kVoiceDetailStrings, 4)
    , item_midi_filter_enabled("MIDI filter", &_part->midi_filter_channel_enabled, "on", "off")
    , item_midi_channel("MIDI channel", (uint8_t*)&_part->midi_filter_channel, kMidiChannelStrings, 17)
    , item_midi_input("MIDI input", (uint8_t*)&_part->midi_filter_input, kMidiInputStrings, 3)
    , item_midi_lowest_note("MIDI lowest", (uint8_t*)&_part->midi_filter_lowest_note)
    , item_midi_highest_note("MIDI highest", (uint8_t*)&_part->midi_filter_highest_note)
    , item_midi_thru_mode("MIDI thru", (uint8_t*)&_part->midi_thru_mode, kMidiThruStrings, 3)
{
  this->menu.add_item(&this->item_voice_count);
  this->menu.add_item(&this->item_voice_detail);
  this->menu.add_item(&this->item_midi_filter_enabled);
  this->menu.add_item(&this->item_midi_channel);
  this->menu.add_item(&this->item_midi_input);
  this->menu.add_item(&this->item_midi_lowest_note);
  this->menu.add_item(&this->item_midi_highest_note);
  this->menu.add_item(&this->item_midi_thru_mode);
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

void PartMenu::render(U8G2* u8g2, int x, int y, int width, int height)
{
  menu.render(u8g2, x, y, width, height);
}
