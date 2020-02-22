#ifndef MIDI2CV_UI_H
#define MIDI2CV_UI_H

#include "stmlib/stmlib.h"
#include "stmlib/ui/event_queue.h"

typedef enum {
  MENU_PART_1 = 0,
  MENU_PART_2,
  MENU_PART_3,
  MENU_PART_4,
  MENU_COUNT
} Menu_t;

class UI {
  public:
  UI() {}
  ~UI() {}

  void Init();
  void Poll();
  void Flush();
  bool DoEvents();

  private:
  Menu_t current_menu;
  stmlib::EventQueue<16> input_queue;

  bool long_press_event_sent_;
  uint32_t start_stop_press_time_;
  bool encoder_long_press_event_sent_;
  uint32_t encoder_press_time_;

  void Draw();

  void OnClick();
  void OnLongClick();
  void OnIncrement(stmlib::Event& e);

  DISALLOW_COPY_AND_ASSIGN(UI);
};

extern UI ui;

#endif
