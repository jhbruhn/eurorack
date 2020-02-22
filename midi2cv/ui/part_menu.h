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
  UIntMenuItem item_voice_count;
  UIntMenuItem item_voice_detail;
  BoolMenuItem item_midi_filter_enabled;
  UIntMenuItem item_midi_channel;
  MidiNoteMenuItem item_midi_lowest_note;
  MidiNoteMenuItem item_midi_highest_note;
};
