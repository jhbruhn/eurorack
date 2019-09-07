#include <stm32f37x_conf.h>

#include "drivers/display.h"
#include "drivers/gpio.h"

using namespace stmlib;

GPIO gpio;
Display display;

// Default interrupt handlers.
extern "C" {
void NMI_Handler() {}
void HardFault_Handler()
{
    while (1)
	;
}
void MemManage_Handler()
{
    while (1)
	;
}
void BusFault_Handler()
{
    while (1)
	;
}
void UsageFault_Handler()
{
    while (1)
	;
}
void SVC_Handler() {}
void DebugMon_Handler() {}
void PendSV_Handler() {}

// called every 1ms
void SysTick_Handler()
{
}
}

void Init(void)
{
    SystemInit();
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x1000);

    RCC_APB2PeriphClockCmd(
	RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM1 | RCC_APB2Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    TIM_TimeBaseInitTypeDef timer_init;
    timer_init.TIM_Period = F_CPU / (48000 * 4) - 1;
    timer_init.TIM_Prescaler = 0;
    timer_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_InternalClockConfig(TIM1);
    TIM_TimeBaseInit(TIM1, &timer_init);
    TIM_Cmd(TIM1, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 2.2 priority split.

    // DAC interrupt is given highest priority
    NVIC_InitTypeDef timer_interrupt;
    timer_interrupt.NVIC_IRQChannel = TIM1_UP_IRQn;
    timer_interrupt.NVIC_IRQChannelPreemptionPriority = 0;
    timer_interrupt.NVIC_IRQChannelSubPriority = 0;
    timer_interrupt.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&timer_interrupt);

    SysTick_Config(F_CPU / 8000);

    gpio.Init();
//    asm("bkpt #0");
    display.Init();
}

int main(void)
{
    Init();
    while (1) {
	for (int x = 0; x < DISPLAY_WIDTH; x++)
	    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
		display.WritePixel(x, y, 0xff);
		display.WritePixel(DISPLAY_WIDTH - x, DISPLAY_WIDTH - y, 0xff);
	    }
	display.Update();
	// hi
	gpio.Write(GPIO_PIN(GATE_OUT_1), 0);
	gpio.Write(GPIO_PIN(GATE_OUT_2), 0);
	gpio.Write(GPIO_PIN(GATE_OUT_3), 0);
	gpio.Write(GPIO_PIN(GATE_OUT_4), 0);
	gpio.Write(GPIO_PIN(GATE_OUT_5), 0);
	gpio.Write(GPIO_PIN(GATE_OUT_6), 0);
    }
}
