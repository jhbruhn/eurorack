#include "drivers/adc.h"
#include "drivers/dac.h"
#include "resources.h"

using namespace stereo_mix;

Dac dacs[8];
Adc adc;

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

void DMA1_Channel1_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC1) == SET) /* Test if transfer completed on DMA channel 1 */
  {
    adc.OnDMAFinish();
    DMA_ClearITPendingBit(DMA1_IT_TC1);
  }
}
}

int main(void)
{
  SystemInit();


  dacs[0].Init(GPIOB, GPIO_Pin_8);
  dacs[1].Init(GPIOB, GPIO_Pin_9);
  dacs[2].Init(GPIOB, GPIO_Pin_10);
  dacs[3].Init(GPIOB, GPIO_Pin_11);
  dacs[4].Init(GPIOA, GPIO_Pin_8);
  dacs[5].Init(GPIOA, GPIO_Pin_9);
  dacs[6].Init(GPIOA, GPIO_Pin_10);
  dacs[7].Init(GPIOA, GPIO_Pin_11);

  adc.Init();
  while (true) {
    for(int i = 0; i < 4; i++) {
      uint32_t value_l;
      uint32_t value_r;

      uint16_t pan_pot = adc.value(ADC_CHANNEL_POT_PAN_1 + i) >> (16 - 12); // adc is only 12 bit anyways
      uint16_t vol_pot = adc.value(ADC_CHANNEL_POT_VOL_1 + i) >> (16 - 12);
      int16_t pan_cv = (adc.value(ADC_CHANNEL_CV_PAN_1 - i) - 32768) >> (16 - 12);
      uint16_t vol_cv = adc.value(ADC_CHANNEL_CV_VOL_1 - i) >> (16 - 12);
      int32_t pan = pan_pot + pan_cv;
      int32_t vol = vol_pot + vol_cv;

      CONSTRAIN(pan, 0, (1 << 12) - 1);
      CONSTRAIN(vol, 0, (1 << 12) - 1);

      value_l = (lut_left_sin_pan[pan] * lut_linear_to_exp[vol]) >> 16;
      value_r = (lut_right_cos_pan[pan] * lut_linear_to_exp[vol]) >> 16;

      dacs[i].Write16(0, value_r);
      dacs[i + 4].Write16(0, value_r);
      dacs[i].Write16(1, value_l);
      dacs[i + 4].Write16(1, value_l);
    }
  }
}
