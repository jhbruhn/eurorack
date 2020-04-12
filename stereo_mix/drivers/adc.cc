#include "stereo_mix/drivers/adc.h"
#include "stm32f030x8.h"
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_dma_ex.h"

#include <stm32f0xx_hal.h>

extern "C" {
void DMA_TransferComplete(DMA_HandleTypeDef* dma); // declared in stereo_mix.cc
}

namespace stereo_mix {

void Adc::Init()
{
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();

  GPIO_InitTypeDef gpio_init;

  gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  gpio_init.Pin |= GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
  gpio_init.Pin |= GPIO_PIN_6 | GPIO_PIN_7;
  gpio_init.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &gpio_init);

  gpio_init.Pin = GPIO_PIN_0;
  gpio_init.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOB, &gpio_init);

  // Configure the address lines for the MUX.
  gpio_init.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &gpio_init);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);
  this->mux_index_ = 0;

  adc.Init.Resolution = ADC_RESOLUTION_12B;
  adc.Init.ContinuousConvMode = ENABLE;
  adc.Init.DiscontinuousConvMode = DISABLE;
  adc.Init.DataAlign = ADC_DATAALIGN_LEFT;
  adc.Init.ScanConvMode = ADC_SCAN_ENABLE;
  adc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  adc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  adc.Init.DMAContinuousRequests = DISABLE;
  adc.Instance = ADC1;
  HAL_ADC_Init(&adc);
  HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);

  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_1;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_2;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_3;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_4;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_5;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_6;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_7;
  HAL_ADC_ConfigChannel(&adc, &sConfig);
  sConfig.Channel = ADC_CHANNEL_8;
  HAL_ADC_ConfigChannel(&adc, &sConfig);

  dma.Init.Direction = DMA_PERIPH_TO_MEMORY;
  dma.Init.PeriphInc = DMA_PINC_DISABLE;
  dma.Init.MemInc = DMA_MINC_ENABLE;
  dma.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  dma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  dma.Init.Mode = DMA_CIRCULAR;
  dma.Init.Priority = DMA_PRIORITY_LOW;
  dma.Instance = DMA1_Channel1;
  HAL_DMA_Init(&dma);
  __HAL_LINKDMA(&adc, DMA_Handle, dma);

  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);

  HAL_ADC_Start_DMA(&adc, (uint32_t*)values_, ADC_CHANNEL_LAST);
}

void Adc::DeInit()
{
  HAL_ADC_DeInit(&adc);
}

void Adc::OnDMATransferComplete()
{
  this->values_[ADC_GROUP_POT + this->mux_index_] = this->values_[ADC_CHANNEL_MUX];

  this->mux_index_ = (this->mux_index_ + 1) % (ADC_CHANNEL_LAST - 1);
  uint8_t address = this->mux_index_;

  // Write the mux address.
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, static_cast<GPIO_PinState>(address & 1));
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, static_cast<GPIO_PinState>(address & 2));
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, static_cast<GPIO_PinState>(address & 4));
  HAL_ADC_Start_DMA(&adc, (uint32_t*)values_, ADC_CHANNEL_LAST);
}

} // namespace rings
