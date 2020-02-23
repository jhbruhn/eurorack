#ifndef MIDI2CV_UI_H
#define MIDI2CV_UI_H

#include "stmlib/stmlib.h"
#include "stmlib/ui/event_queue.h"

class UI {
  public:
  UI();
  ~UI() {}

  void Poll();
  void Flush();
  void DoEvents();

  private:
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
