
/**
  ******************************************************************************
  * @file		  : encoder.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Simple rotary encoder driver library
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

#ifdef ENC_HARDWARE_COUNTER

/**
 * @brief Rotary quadrature encoder hardware initialization.
 * @param[in] henc : Encoder handler
 * @return None
 */
void ENC_Init(ENC_Handle_TypeDef* henc)
{
	HAL_TIM_Encoder_Start(henc->Timer, TIM_CHANNEL_ALL);
}

/**
 * @brief Rotary quadrature encoder hardware counter read.
 * @param[in] henc : Encoder handler
 * @return Current counter value
 */
uint32_t ENC_GetCounter(ENC_Handle_TypeDef* henc)
{
  uint32_t cnt = henc->Counter;
  henc->Counter = __HAL_TIM_GET_COUNTER(henc->Timer);
  henc->CounterInc = (henc->Counter > cnt);
  henc->CounterDec = (henc->Counter < cnt);
  return henc->Counter / henc->TicksPerStep;
}

/**
 * @brief Rotary quadrature encoder hardware counter read.
 * @param[in] henc    : Encoder handler
 * @param[in] counter : Current counter value
 */
void ENC_SetCounter(ENC_Handle_TypeDef* henc, uint32_t counter)
{
  henc->Counter = counter * henc->TicksPerStep;
  __HAL_TIM_SET_COUNTER(henc->Timer, henc->Counter);
}

#else

/**
 * @brief Rotary quadrature encoder software counter update procedure.
 * @param[in] henc : Encoder handler
 * @return Current counter value
 */
int32_t ENC_UpdateCounter(ENC_Handle_TypeDef* henc)
{
  GPIO_PinState dt = HAL_GPIO_ReadPin(henc->DT_Port, henc->DT_Pin);
  int32_t cnt = henc->Counter;
  if(dt == GPIO_PIN_RESET)
    henc->Counter = (henc->Counter >= henc->CounterMax) ? henc->CounterMax : (henc->Counter + henc->CounterStep);
  else
    henc->Counter = (henc->Counter <= henc->CounterMin) ? henc->CounterMin : (henc->Counter - henc->CounterStep);
  henc->CounterInc = (henc->Counter > cnt);
  henc->CounterDec = (henc->Counter < cnt);
  return henc->Counter;
}

#endif
