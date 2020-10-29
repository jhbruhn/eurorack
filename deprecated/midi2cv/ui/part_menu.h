#pragma once

#include "../menu/menu.h"
#include "../menu/menu_items.h"
#include "../part.h"
#include <U8g2lib.h>

class PartMenu {
  public:
  PartMenu(Part* _part);
  PartMenu() {}
  bool enter();
  bool back();
  void up();
  void down();

  void render(U8G2* u8g2, int x, int y, int width, int height);

  private:
  Part* part;

  Menu menu;
  UInt8MenuItem item_voice_count;
  StringListMenuItem item_voice_detail;
  BoolMenuItem item_midi_filter_enabled;
  StringListMenuItem item_midi_channel;
  StringListMenuItem item_midi_input;
  MidiNoteMenuItem item_midi_lowest_note;
  MidiNoteMenuItem item_midi_highest_note;
  StringListMenuItem item_midi_thru_mode;
};
