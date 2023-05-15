/**
 ******************************************************************************
 * @file     : pwm.c
 * @author   : AW    Adrian.Wojcik@put.poznan.pl
 * @version  : 1.3.0
 * @date     : Nov 27, 2022
 * @brief    : Pulse Width Modulation outputs components driver.
 *
 ******************************************************************************
 */

/* Private includes ----------------------------------------------------------*/
#include "pwm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Initialize PWM output
 * @param[in/out] hpwm   : PWM output handler
 * @retval None
 */
void PWM_Init(PWM_Handle_TypeDef *hpwm) {
    PWM_SetDuty(hpwm, hpwm->Duty);
    HAL_TIM_PWM_Start(hpwm->Timer, hpwm->Channel);
}

/**
 * @brief Write PWM duty cycle
 * @param[in/out] hpwm   : PWM output handler
 * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
 * @retval None
 */
void PWM_SetDuty(PWM_Handle_TypeDef *hpwm, float duty) {
    // Saturate duty cycle value
    if (duty < 0.0f)
        duty = 0.0;
    else if (duty > 100.0f)
        duty = 100.0f;
    // Write duty to handle field
    hpwm->Duty = duty;
    // Compute Capture/Compare Register value
    int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hpwm->Timer) + 1)) / 100;
    // Write value to register
    __HAL_TIM_SET_COMPARE(hpwm->Timer, hpwm->Channel, COMPARE);
}

/**
 * @brief Get PWM duty cycle
 * @param[in]     hpwm   : PWM output handler
 * @retval PWM duty cycle in percents (0. - 100.)
 */
float PWM_GetDuty(const PWM_Handle_TypeDef *hpwm) {
    return hpwm->Duty;
}
