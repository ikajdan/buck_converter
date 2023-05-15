/**
 ******************************************************************************
 * @file		: buck_config.c
 * @author  	: IK		ignacy.kajdan@gmail.com
 * @version 	: 1.0.0
 * @date    	: Jan 21, 2022
 * @brief   	: Buck configuration file
 *
 ******************************************************************************
 */

/* Includes ----------------------------------------------------------*/
#include "buck.h"
#include "buck_config.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/

/* Macro -------------------------------------------------------------*/

/* Variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
Buck_Handle_TypeDef hbuck1 = { .Voltage = 0, .Current = 0, .TargetVoltage = 1000, .CurrentLimit = 1000, .OutputMode = 0, .Output = 0 };

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
