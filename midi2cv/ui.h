#ifndef MIDI2CV_UI_H
#define MIDI2CV_UI_H

#include "stmlib/stmlib.h"

typedef enum {
  MENU_PART_1,
  MENU_PART_2,
  MENU_PART_3,
  MENU_PART_4,
  MENU_COUNT
} Menu_t;

class UI {
  public:
  UI() {}
  ~UI() {}

  void Update();
  void Flush();

  private:
  Menu_t current_menu;

  void DrawHeader();
  void DrawPartMenu(Menu_t menu);

  DISALLOW_COPY_AND_ASSIGN(UI);
};

extern UI ui;

#endif
