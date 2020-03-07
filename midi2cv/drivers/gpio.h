#ifndef MIDI2CV_DRIVERS_GPIO_H
#define MIDI2CV_DRIVERS_GPIO_H


#include "stmlib/stmlib.h"
#include <stm32f37x_conf.h>

#define PORT_RST_OLED GPIOB
#define PIN_RST_OLED GPIO_Pin_0
#define PORT_SS_DAC0 GPIOB
#define PIN_SS_DAC0 GPIO_Pin_6
#define PORT_SS_DAC1 GPIOB
#define PIN_SS_DAC1 GPIO_Pin_7
#define PORT_RST_USB GPIOB
#define PIN_RST_USB GPIO_Pin_8
#define PORT_SS_USB GPIOB
#define PIN_SS_USB GPIO_Pin_9
#define PORT_SS_OLED GPIOB
#define PIN_SS_OLED GPIO_Pin_11
#define PORT_SDC_OLED GPIOB
#define PIN_SDC_OLED GPIO_Pin_12

#define PORT_GATE_OUT_1 GPIOA
#define PIN_GATE_OUT_1 GPIO_Pin_0
#define PORT_GATE_OUT_2 GPIOA
#define PIN_GATE_OUT_2 GPIO_Pin_1
#define PORT_GATE_OUT_3 GPIOA
#define PIN_GATE_OUT_3 GPIO_Pin_2
#define PORT_GATE_OUT_4 GPIOA
#define PIN_GATE_OUT_4 GPIO_Pin_3
#define PORT_GATE_OUT_5 GPIOA
#define PIN_GATE_OUT_5 GPIO_Pin_4
#define PORT_GATE_OUT_6 GPIOA
#define PIN_GATE_OUT_6 GPIO_Pin_5

#define GPIO_PIN(x) PORT_##x, PIN_##x

class GPIO {
  public:
    GPIO() { }
    ~GPIO() {}

    void Init();
    void Write(GPIO_TypeDef* port, uint16_t pin, bool state);
  private:
    DISALLOW_COPY_AND_ASSIGN(GPIO);
};

extern GPIO gpio;

#endif

