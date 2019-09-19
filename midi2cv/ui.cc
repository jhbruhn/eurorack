#include "ui.h"
#include "drivers/display.h"
#include "stmlib/utils/random.h"
#include <u8g2.h>
using namespace stmlib;

void UI::Update()
{
    u8g2_t* u8g2_ = display.u8g2();
    static float x = 0, y = 16, dx = 1, dy = 1, ddx = .2, ddy = .2;
    u8g2_ClearBuffer(u8g2_);
    u8g2_SetFont(u8g2_, u8g2_font_6x10_mf);
    u8g2_DrawStr(u8g2_, (int)x, (int)y, "send nudes");
    x += dx * ddx;
    y += dy * ddy;
    if (x >= 70 || x <= 0) {
	ddx = Random::GetFloat() / 4.0 + 0.1;
    }
    if (x >= 70)
	dx = -1;
    if (x <= 0)
	dx = 1;
    if (y >= 64 || y <= 7) {
	ddy = Random::GetFloat() / 4.0 + 0.1;
    }
    if (y >= 64)
	dy = -1;
    if (y <= 7)
	dy = 1;
    display.Swap();
}

void UI::Flush()
{
    display.Flush();
}
