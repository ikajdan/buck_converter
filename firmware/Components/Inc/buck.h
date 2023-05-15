/**
 ******************************************************************************
 * @file		: buck.h
 * @author  	: IK		ignacy.kajdan@gmail.com
 * @version 	: 1.0.0
 * @date    	: Jan 21, 2022
 * @brief   	: Buck components driver
 *
 ******************************************************************************
 */
#ifndef INC_BUCK_H_
#define INC_BUCK_H_

/* Public includes -----------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief Buck handle structure definition
 */
typedef struct {
    unsigned int Voltage;
    unsigned int Current;
    unsigned int TargetVoltage;
    unsigned int CurrentLimit;
    _Bool OutputMode; // TODO: Use enums here
    _Bool Output;
} Buck_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Returns measured voltage in mV
 * @param[in] hbuck : Buck handler
 * @retval Voltage in mV
 */
unsigned int Buck_GetVoltage(Buck_Handle_TypeDef *hbuck);

/**
 * @brief Sets measured voltage in mV
 * @param[in] hbuck 			: Buck handler
 * @param[in] targetVoltage	: Voltage in mV
 * @retval None
 */
void Buck_SetVoltage(Buck_Handle_TypeDef *hbuck, unsigned int voltage);

/**
 * @brief Returns reference voltage in mV
 * @param[in] hbuck : Buck handler
 * @retval Voltage in mV
 */
unsigned int Buck_GetTargetVoltage(Buck_Handle_TypeDef *hbuck);

/**
 * @brief Sets the reference voltage in mV
 * @param[in] hbuck : Buck handler
 * @param[in] targetVoltage	: Voltage in mV
 * @retval None
 */
void Buck_SetTargetVoltage(Buck_Handle_TypeDef *hbuck, unsigned int targetVoltage);

/**
 * @brief Returns measured current in mA
 * @param[in] hbuck : Buck handler
 * @retval Current in mA
 */
unsigned int Buck_GetCurrent(Buck_Handle_TypeDef *hbuck);

/**
 * @brief Sets measured current in mA
 * @param[in] hbuck 	: Buck handler
 * @param[in] current	: Current in mA
 * @retval None
 */
void Buck_SetCurrent(Buck_Handle_TypeDef *hbuck, unsigned int current);

/**
 * @brief Returns current limit in mA
 * @param[in] hbuck : Buck handler
 * @retval Current in mA
 */
unsigned int Buck_GetCurrentLimit(Buck_Handle_TypeDef *hbuck);

/**
 * @brief Sets the current limit in mA
 * @param[in] hbuck : Buck handler
 * @param[in] currentLimit	: Current in mA
 * @retval None
 */
void Buck_SetCurrentLimit(Buck_Handle_TypeDef *hbuck, unsigned int currentLimit);

/**
 * @brief Returns the output state
 * @param[in] hbuck : Buck handler
 * @retval Output state (true or false)
 */
_Bool Buck_GetOutput(Buck_Handle_TypeDef *hbuck);

/**
 * @brief Toggles the output on or off
 * @param[in] hbuck : Buck handler
 * @retval None
 */
void Buck_ToggleOutput(Buck_Handle_TypeDef *hbuck);

#endif /* INC_BUCK_H_ */
