/**
  ******************************************************************************
  * @file     : dio.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Digital inputs/outputs components driver.
  *
  ******************************************************************************
  */

#ifndef INC_DIO_H_
#define INC_DIO_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief Digital I/O handle structure definition
 */
#ifdef USE_HAL_DRIVER
typedef GPIO_TypeDef* DIO_Port_TypeDef;
typedef uint16_t DIO_Pin_TypeDef;
#endif

typedef struct {
  DIO_Port_TypeDef Port;
  DIO_Pin_TypeDef Pin;
} DIO_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
 * @brief Digital I/O handle structure initialization with pin user label
 */
#ifdef USE_HAL_DRIVER
#define DIO_INIT_HANDLE(USER_NAME)      \
        {                               \
          .Port = USER_NAME##_GPIO_Port,\
          .Pin = USER_NAME##_Pin,       \
        }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Resets digital output (writes '0')
 * @param[in] hdio  : Digital I/O handler
 * @retval None
 */
void DIO_WriteLow(const DIO_Handle_TypeDef* hdio);

/**
 * @brief Sets digital output (writes '1')
 * @param[in] hdio  : Digital I/O handler
 * @retval None
 */
void DIO_WriteHigh(const DIO_Handle_TypeDef* hdio);

/**
 * @brief Writes gieven state to digital output
 * @param[in] hdio  : Digital I/O handler
 * @param[in] state : Digital output state (0 or 1)
 * @retval None
 */
void DIO_Write(const DIO_Handle_TypeDef* hdio, _Bool state);

/**
 * @brief Toggles digital output ('0' to '1' or '1' to '0')
 * @param[in] hdio  : Digital I/O handler
 * @retval None
 */
void DIO_Toggle(const DIO_Handle_TypeDef* hdio);

/**
 * @brief Reads digital input
 * @param[in] hdio  : Digital I/O handler
 * @retval Input state (0 or 1)
 */
_Bool DIO_Read(const DIO_Handle_TypeDef* hdio);

#endif /* INC_DIO_H_ */
