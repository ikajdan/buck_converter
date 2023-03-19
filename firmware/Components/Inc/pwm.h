/**
 ******************************************************************************
 * @file     : pwm.h
 * @author   : AW    Adrian.Wojcik@put.poznan.pl
 * @version  : 1.3.0
 * @date     : Nov 27, 2022
 * @brief    : Pulse Width Modulation outputs components driver.
 *
 ******************************************************************************
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief PWM output handle structure definition
 */
#ifdef USE_HAL_DRIVER
typedef TIM_HandleTypeDef *PWM_TIM_TypeDef;
typedef uint32_t PWM_Channel_TypeDef;
#endif

typedef struct
{
	PWM_TIM_TypeDef Timer;
	PWM_Channel_TypeDef Channel;
	float Duty;
} PWM_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
 * @brief PWM output handle structure initialization with TIM handle
 *        and channel label
 */
#ifdef USE_HAL_DRIVER
#define PWM_INIT_HANDLE(TIMER_HANDLE, CHANNEL) \
  {                                            \
    .Timer = TIMER_HANDLE,                     \
    .Channel = CHANNEL,                        \
    .Duty = 0.0f                               \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Initialize PWM output
 * @param[in/out] hpwm   : PWM output handler
 * @retval None
 */
void PWM_Init(PWM_Handle_TypeDef *hpwm);

/**
 * @brief Write PWM duty cycle
 * @param[in/out] hpwm   : PWM output handler
 * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
 * @retval None
 */
void PWM_SetDuty(PWM_Handle_TypeDef *hpwm, float duty);

/**
 * @brief Get PWM duty cycle
 * @param[in]     hpwm   : PWM output handler
 * @retval PWM duty cycle in percents (0. - 100.)
 */
float PWM_GetDuty(const PWM_Handle_TypeDef *hpwm);

#endif /* INC_PWM_H_ */
