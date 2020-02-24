#ifndef MIDI2CV_UI_H
#define MIDI2CV_UI_H

#include "stmlib/stmlib.h"
#include "stmlib/ui/event_queue.h"

#include "config.h"
#include "settings.h"
#include "ui/main_menu.h"
#include <array>

class UI {
  public:
  UI(Part** part_pointers, Settings* settings);
  ~UI() {}

  void Poll();
  void Flush();
  void DoEvents();

  private:
  stmlib::EventQueue<16> input_queue;

  Settings* settings;

  bool long_press_event_sent_;
  uint32_t start_stop_press_time_;
  bool encoder_long_press_event_sent_;
  uint32_t encoder_press_time_;

  MainMenu<PART_COUNT> main_menu;
  Part** parts;

  void LoadState();
  void SaveState();

  void Draw();

  void OnClick();
  void OnLongClick();
  void OnIncrement(stmlib::Event& e);

  DISALLOW_COPY_AND_ASSIGN(UI);
};

extern UI ui;

#endif
