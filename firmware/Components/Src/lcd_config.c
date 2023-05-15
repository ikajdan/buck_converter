/**
 ******************************************************************************
 * @file    lcd_config.c
 * @author  AW
 * @version V2.0
 * @date    30-Oct-2020
 * @brief   Simple HD44780 driver library for STM32F7 configuration file.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "lcd_config.h"
#include "main.h"

#ifdef LCD_USE_TIMER
#include "tim.h"
#endif

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
DIO_Handle_TypeDef __hlcd1_DATA[] = {
DIO_INIT_HANDLE(LCD_D4),
DIO_INIT_HANDLE(LCD_D5),
DIO_INIT_HANDLE(LCD_D6),
DIO_INIT_HANDLE(LCD_D7) };

/* Public variables ----------------------------------------------------------*/
LCD_DIO_HandleTypeDef hlcd1 = { .DATA = __hlcd1_DATA, .RS = DIO_INIT_HANDLE(LCD_RS), .E =
DIO_INIT_HANDLE(LCD_EN), .Mode = LCD_4_BIT_MODE, .Timer = &htim7 };

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
