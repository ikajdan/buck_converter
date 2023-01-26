/**
 ******************************************************************************
 * @file		: encoder_config.c
 * @author  	: AW		Adrian.Wojcik@put.poznan.pl
 * @version 	: 1.0
 * @date    	: Oct 30, 2022
 * @brief   	: Simple rotary encoder driver library configuration file
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

#ifdef ENC_HARDWARE_COUNTER
#include "tim.h"
#else
#include "main.h"
#endif

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

ENC_Handle_TypeDef henc1 =
{ .Timer = &htim3, .Counter = 0, .CounterMax = 400, .CounterMin = 0,
		.CounterInc = 0, .CounterDec = 0, .TicksPerStep = 4 };

#else

ENC_Handle_TypeDef henc1 = {
	.CLK_Port = ENC_CLK_GPIO_Port,
	.CLK_Pin = ENC_CLK_Pin,
	.DT_Port  = ENC_DT_GPIO_Port,
	.DT_Pin  = ENC_DT_Pin,
	.Counter  = 0,
	.CounterMax = 400,
	.CounterMin = 0,
	.CounterStep = 1,
	.CounterInc = 0,
	.CounterDec = 0
};

#endif

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
