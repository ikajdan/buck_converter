/**
 ******************************************************************************
 * @file		: buck.c
 * @author  	: IK		ignacy.kajdan@gmail.com
 * @version 	: 1.0.0
 * @date    	: Jan 21, 2022
 * @brief   	: Buck components driver
 *
 ******************************************************************************
 */

/* Includes ----------------------------------------------------------*/
#include "gpio.h"
#include "tim.h"
#include "buck.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/

/* Macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int8_t COUNTER;
/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Returns measured voltage in mV
 * @param[in] hbuck : Buck handler
 * @retval Voltage in mV
 */
unsigned int Buck_GetVoltage(Buck_Handle_TypeDef *hbuck)
{
	return hbuck->Voltage;
}

/**
 * @brief Sets measured voltage in mV
 * @param[in] hbuck 			: Buck handler
 * @param[in] targetVoltage	: Voltage in mV
 * @retval None
 */
void Buck_SetVoltage(Buck_Handle_TypeDef *hbuck, unsigned int voltage)
{
	hbuck->Voltage = voltage;
}

/**
 * @brief Returns reference voltage in mV
 * @param[in] hbuck : Buck handler
 * @retval Voltage in mV
 */
unsigned int Buck_GetTargetVoltage(Buck_Handle_TypeDef *hbuck)
{
	return hbuck->TargetVoltage;
}

/**
 * @brief Sets the reference voltage in mV
 * @param[in] hbuck : Buck handler
 * @param[in] targetVoltage	: Voltage in mV
 * @retval None
 */
void Buck_SetTargetVoltage(Buck_Handle_TypeDef *hbuck,
		unsigned int targetVoltage)
{
	hbuck->TargetVoltage = targetVoltage;
}

/**
 * @brief Returns measured current in mA
 * @param[in] hbuck : Buck handler
 * @retval Current in mA
 */
unsigned int Buck_GetCurrent(Buck_Handle_TypeDef *hbuck)
{
	return hbuck->Current;
}

/**
 * @brief Sets measured current in mA
 * @param[in] hbuck 	: Buck handler
 * @param[in] current	: Current in mA
 * @retval None
 */
void Buck_SetCurrent(Buck_Handle_TypeDef *hbuck, unsigned int current)
{
	hbuck->Current = current;
}

/**
 * @brief Returns current limit in mA
 * @param[in] hbuck : Buck handler
 * @retval Current in mA
 */
unsigned int Buck_GetCurrentLimit(Buck_Handle_TypeDef *hbuck)
{
	return hbuck->CurrentLimit;
}

/**
 * @brief Sets the current limit in mA
 * @param[in] hbuck : Buck handler
 * @param[in] currentLimit	: Current in mA
 * @retval None
 */
void Buck_SetCurrentLimit(Buck_Handle_TypeDef *hbuck, unsigned int currentLimit)
{
	hbuck->CurrentLimit = currentLimit;
}

/**
 * @brief Returns the output state
 * @param[in] hbuck : Buck handler
 * @retval Output state (0 or 1)
 */
_Bool Buck_GetOutput(Buck_Handle_TypeDef *hbuck)
{
	return hbuck->Output;
}

/**
 * @brief Toggles the output on or off
 * @param[in] hbuck : Buck handler
 * @retval None
 */
void Buck_ToggleOutput(Buck_Handle_TypeDef *hbuck)
{
	if (hbuck->Output == 1)
	{
		hbuck->Output = 0;
		HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, 0);
	}
	else
	{
		hbuck->Output = 1;
		HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, 1);
	}
}
