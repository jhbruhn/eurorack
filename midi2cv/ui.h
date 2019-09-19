#ifndef MIDI2CV_UI_H
#define MIDI2CV_UI_H

#include "stmlib/stmlib.h"

class UI {
public:
    UI() {}
    ~UI() {}

    void Update();

private:
    DISALLOW_COPY_AND_ASSIGN(UI);
};

extern UI ui;

#endif
