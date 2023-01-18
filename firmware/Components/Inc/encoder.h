/**
  ******************************************************************************
  * @file		  : encoder.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Rotary encoder
  *
  ******************************************************************************
  */
#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

/* Config --------------------------------------------------------------------*/
#define ENC_HARDWARE_COUNTER

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

#define ENC_TimerType TIM_HandleTypeDef*

typedef struct {
  ENC_TimerType Timer;
  uint32_t Counter;
  uint32_t CounterMax;
  uint32_t CounterMin;
  _Bool CounterInc;
  _Bool CounterDec;
  uint32_t TicksPerStep;
} ENC_Handle_TypeDef;

#else

#define ENC_PortType GPIO_TypeDef*
#define ENC_PinType uint16_t

typedef struct {
  ENC_PortType CLK_Port;
  ENC_PinType  CLK_Pin;
  ENC_PortType DT_Port;
  ENC_PinType  DT_Pin;
  int32_t Counter;
  int32_t CounterMax;
  int32_t CounterMin;
  int32_t CounterStep;
  _Bool CounterInc;
  _Bool CounterDec;
} ENC_Handle_TypeDef;

#endif

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

/**
 * @brief Rotary quadrature encoder hardware initialization.
 * @param[in] henc : Encoder handler
 * @return None
 */
void ENC_Init(ENC_Handle_TypeDef* henc);

/**
 * @brief Rotary quadrature encoder hardware counter read.
 * @param[in] henc : Encoder handler
 * @return Current counter value
 */
uint32_t ENC_GetCounter(ENC_Handle_TypeDef* henc);

/**
 * @brief Rotary quadrature encoder hardware counter read.
 * @param[in] henc    : Encoder handler
 * @param[in] counter : Current counter value
 */
void ENC_SetCounter(ENC_Handle_TypeDef* henc, uint32_t counter);

#else

/**
 * @brief Rotary quadrature encoder software counter update procedure.
 * @param[in] henc : Encoder handler
 * @return Current counter value
 */
int32_t ENC_UpdateCounter(ENC_Handle_TypeDef* henc);

#endif

#endif /* INC_ENCODER_H_ */
