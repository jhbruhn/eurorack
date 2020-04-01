#include "stereo_mix/drivers/adc.h"

#include <stm32f0xx.h>

namespace stereo_mix {

void Adc::Init()
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_InitTypeDef adc_init;
  GPIO_InitTypeDef gpio_init;

  gpio_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  gpio_init.GPIO_Pin |= GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  gpio_init.GPIO_Pin |= GPIO_Pin_6 | GPIO_Pin_7;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_init.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOA, &gpio_init);

  gpio_init.GPIO_Pin = GPIO_Pin_0;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_init.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOB, &gpio_init);

  // Configure the address lines for the MUX.
  gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  gpio_init.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &gpio_init);
  GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
  this->mux_index_ = 0;

  adc_init.ADC_Resolution = ADC_Resolution_12b;
  adc_init.ADC_ContinuousConvMode = ENABLE;
  adc_init.ADC_DataAlign = ADC_DataAlign_Left;
  adc_init.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &adc_init);

  ADC_ClockModeConfig(ADC1, ADC_ClockMode_SynClkDiv2);
  ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_6, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_7, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_8, ADC_SampleTime_239_5Cycles);

  ADC_Cmd(ADC1, ENABLE);
  ADC_DMACmd(ADC1, ENABLE);

  DMA_InitTypeDef dma_init;
  DMA_StructInit(&dma_init);
  dma_init.DMA_DIR = DMA_DIR_PeripheralSRC;
  dma_init.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  dma_init.DMA_MemoryBaseAddr = (uint32_t)&values_[0];
  dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  dma_init.DMA_BufferSize = ADC_CHANNEL_NUM_DIRECT;
  dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma_init.DMA_Mode = DMA_Mode_Circular;
  dma_init.DMA_Priority = DMA_Priority_High;
  dma_init.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &dma_init);

  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
  DMA_Cmd(DMA1_Channel1, ENABLE);
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_OneShot);

  /*NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
*/
  ADC_StartOfConversion(ADC1);
}

void Adc::DeInit()
{
  ADC_Cmd(ADC1, DISABLE);
  ADC_DeInit(ADC1);
}

void Adc::OnDMAFinish()
{
  this->values_[ADC_CHANNEL_FIRST_MUXED + this->mux_index_] = this->values_[ADC_CHANNEL_MUX];

  this->mux_index_ = (this->mux_index_ + 1) % ADC_CHANNEL_NUM_MUXED;
  uint8_t address = this->mux_index_;

  // Write the mux address.
  GPIO_WriteBit(GPIOB, GPIO_Pin_12, static_cast<BitAction>(address & 1));
  GPIO_WriteBit(GPIOB, GPIO_Pin_13, static_cast<BitAction>(address & 2));
  GPIO_WriteBit(GPIOB, GPIO_Pin_14, static_cast<BitAction>(address & 4));
  ADC_StartOfConversion(ADC1);
}

} // namespace rings
