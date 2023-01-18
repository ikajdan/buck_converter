/**
  ******************************************************************************
  * @file     : lcd.c
  * @author   : Olivier Van den Eede [ https://github.com/4ilo/HD44780-Stm32HAL ]
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 3.0
  * @date     : 10-Jun-2018
  * @brief    : Simple HD44780 driver library for STM32F7.
  *             NOTE!: This code provides only WRITE features, no READ features.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define LCD_NUMBER_BUF_SIZE 21
#define LCD_PRINTF_BUF_SIZE 64

/* Macro ---------------------------------------------------------------------*/
#ifdef LCD_USE_TIMER
#define __lcd_dio_delay(__HANDLE__, delay_ms)  __lcd_dio_delay_us((__HANDLE__),(float)delay_ms * 1000.0)
#else
#define __lcd_dio_delay(__HANDLE__, delay_ms)  HAL_Delay((uint32_t)delay_ms);
#endif


/* Private variables ---------------------------------------------------------*/
const uint8_t LCD_ROW_16[] = {0x00, 0x40, 0x10, 0x50};
const uint8_t LCD_ROW_20[] = {0x00, 0x40, 0x14, 0x54};

/* Public variables ----------------------------------------------------------*/


/* Private function ----------------------------------------------------------*/
#ifdef LCD_USE_TIMER
/**
 * @brief LCD delay function
 * @param[in] hlcd     : LCD handler
 * @param[in] delay_us : Delay period in microseconds
 * @return None
 */
void __lcd_dio_delay_us(LCD_DIO_HandleTypeDef* hlcd, uint16_t delay_us)
{
  __HAL_TIM_SET_COUNTER(hlcd->Timer, 0);
  HAL_TIM_Base_Start(hlcd->Timer);
  while(__HAL_TIM_GET_COUNTER(hlcd->Timer) < delay_us);
  HAL_TIM_Base_Stop(hlcd->Timer);
}
#endif

/**
 * @brief Set len bits on the bus and toggle the enable line
 * @param[in] hlcd : LCD handler
 * @param[in] data : Data byte
 * @param[in] len  : Data port size (length): 4 ( LCD_NIB )or 8 ( LCD_BYTE ) bits
 * @return None
 */
void __lcd_dio_write(LCD_DIO_HandleTypeDef* hlcd, uint8_t data, uint8_t len)
{
  DIO_WriteHigh(&(hlcd->E));

  for(uint8_t i = 0; i < len; i++)
    DIO_Write(&(hlcd->DATA[i]), (data >> i) & 0x01);

  DIO_WriteLow(&(hlcd->E)); // Data receive on falling edge
  __lcd_dio_delay(hlcd, 0.05);  // > 41 us
}

/**
 * @brief Write a byte to the command register
 * @param[in] hlcd    : LCD handler
 * @param[in] command : Display command @see lcd.h/Define
 * @return None
 */
void __lcd_dio_write_command(LCD_DIO_HandleTypeDef* hlcd, uint8_t command)
{
  DIO_Write(&(hlcd->RS), LCD_COMMAND_REG);  // Write to command register

  if(hlcd->Mode == LCD_4_BIT_MODE)
  {
    if(hlcd->IsInitialized) // Before initialization ignore most significant nibble
    {
      __lcd_dio_write(hlcd, (command >> 4), LCD_NIB);
    }
    __lcd_dio_write(hlcd, command & 0x0F, LCD_NIB);
  }
  else
  {
     __lcd_dio_write(hlcd, command, LCD_BYTE);
  }
}

/**
 * @brief Write a byte to the data register
 * @param[in] hlcd : LCD handler
 * @param[in] data : Display data byte
 * @return None
 */
void __lcd_dio_write_data(LCD_DIO_HandleTypeDef* hlcd, uint8_t data)
{
  DIO_Write(&(hlcd->RS), LCD_DATA_REG);     // Write to data register

  if(hlcd->Mode == LCD_4_BIT_MODE)
  {
    __lcd_dio_write(hlcd, data >> 4, LCD_NIB);
    __lcd_dio_write(hlcd, data & 0x0F, LCD_NIB);
  }
  else
  {
    __lcd_dio_write(hlcd, data, LCD_BYTE);
  }
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief LCD initialization procedure.
 * @note Cursor off, Cursor increment on, No blink @see HD44780 technical note.
 * @param[in] hlcd : LCD handler
 * @return None 
 */
void LCD_DIO_Init(LCD_DIO_HandleTypeDef* hlcd)
{
  hlcd->IsInitialized = 0;

  __lcd_dio_delay(hlcd, 15.2);         // >15 ms

  if(hlcd->Mode == LCD_4_BIT_MODE)
  {
    __lcd_dio_write_command(hlcd, 0x3);  // 0011
    __lcd_dio_delay(hlcd, 4.2);        // > 4.1 ms
    __lcd_dio_write_command(hlcd, 0x3);  // 0011
    __lcd_dio_delay(hlcd, 0.2);        // > 0.1 ms
    __lcd_dio_write_command(hlcd, 0x3);  // 0011
    __lcd_dio_write_command(hlcd, 0x2);  // 0010

    hlcd->IsInitialized = 1;

    __lcd_dio_write_command(hlcd, LCD_FUNCTION_SET | LCD_OPT_N);
  }
  else if(hlcd->Mode == LCD_8_BIT_MODE) /* TODO: test 8-bit interface */
  {
    __lcd_dio_write_command(hlcd, 0x30); // 0011 XXXX
    __lcd_dio_delay(hlcd, 4.2);        // > 4.1 ms
    __lcd_dio_write_command(hlcd, 0x30); // 0011 XXXX
    __lcd_dio_delay(hlcd, 0.2);        // > 0.1 ms
    __lcd_dio_write_command(hlcd, 0x30); // 0011 XXXX

    hlcd->IsInitialized = 1;

    __lcd_dio_write_command(hlcd, LCD_FUNCTION_SET | LCD_OPT_DL | LCD_OPT_N);
  }

  __lcd_dio_write_command(hlcd, LCD_CLEAR_DISPLAY);                      // Clear screen
  __lcd_dio_delay(hlcd, 1.6);                                            // > 1.52 ms
  __lcd_dio_write_command(hlcd, LCD_DISPLAY_ON_OFF_CONTROL | LCD_OPT_D); // LCD on, Cursor off, No blink
  __lcd_dio_write_command(hlcd, LCD_ENTRY_MODE_SET | LCD_OPT_INC);       // Cursor increment on
}

/**
 * @brief Write a decimal number on the current position.
 * @param[in] hlcd   : LCD handler
 * @param[in] number : Decimal number, max. 10 digits
 * @return None 
 */
void LCD_DIO_printDecInt(LCD_DIO_HandleTypeDef* hlcd, int number)
{
  char buffer[LCD_NUMBER_BUF_SIZE];
  sprintf(buffer, "%d", number);

  LCD_DIO_printStr(hlcd, buffer);
}

/**
 * @brief Write a hexadecimal number on the current position.
 * @param[in] hlcd   : LCD handler
 * @param[in] number : Hexadecimal number, max. 10 digits
 * @return None 
 */
void LCD_DIO_printHexInt(LCD_DIO_HandleTypeDef* hlcd, int number)
{
  char buffer[LCD_NUMBER_BUF_SIZE];
  sprintf(buffer, "%x", number);

  LCD_DIO_printStr(hlcd, buffer);
}

/**
 * @brief Write a string on the current position.
 * @param[in] hlcd : LCD handler
 * @param[in] str  : Null-terminated string
 * @return None 
 */
void LCD_DIO_printStr(LCD_DIO_HandleTypeDef* hlcd, char* str)
{
  for(uint8_t i = 0; i < strlen(str); i++)
    __lcd_dio_write_data(hlcd, str[i]);
}

/**
 * @brief Set the cursor position.
 * @param[in] hlcd : LCD handler
 * @param[in] row  : Display row (line): 0 to N
 * @param[in] col  : Display column: 0 to 15 (16 character display) or 19 (20 character display)
 * @return None 
 */
void LCD_DIO_SetCursor(LCD_DIO_HandleTypeDef* hlcd, uint8_t row, uint8_t col)
{
  #ifdef LCD20xN
  __lcd_dio_write_command(hlcd, LCD_SET_DDRAM_ADDR + LCD_ROW_20[row] + col);
  #endif

  #ifdef LCD16xN
  __lcd_dio_write_command(hlcd, LCD_SET_DDRAM_ADDR + LCD_ROW_16[row] + col);
  #endif
}

/**
 * @brief Clear the screen.
 * @param[in] hlcd : LCD handler
 * @return None 
 */
void LCD_DIO_Clear(LCD_DIO_HandleTypeDef* hlcd) {
  __lcd_dio_write_command(hlcd, LCD_CLEAR_DISPLAY);
}

/**
 * @brief Clear the screen.
 * @param[in] hlcd   : LCD handler
 * @param[in] code   : Defined character code in display memory @see HD44780 technical note.
 * @param[in] bitmap : Defined character array @see HD44780 technical note.
 * @return None 
 */
void LCD_DIO_DefineChar(LCD_DIO_HandleTypeDef* hlcd, uint8_t code, uint8_t bitmap[]){
  __lcd_dio_write_command(hlcd, LCD_SETCGRAM_ADDR + (code << 3));
  
  for(uint8_t i=0; i < 8; ++i)
    __lcd_dio_write_data(hlcd, bitmap[i]);
}

#ifdef LCD_PRINTF_ENABLE
/**
 * @brief Write text in standard format on the current position.
 * @param[in] hlcd   : LCD handler
 * @param[in] format : Text format @see http://www.cplusplus.com/reference/cstdio/printf/
 * @param[in] ...    : Variadic arguments
 * @return None
 */
void LCD_DIO_printf(LCD_DIO_HandleTypeDef* hlcd, const char* format, ...)
{
  char buffer[LCD_PRINTF_BUF_SIZE];
  va_list args;
  va_start(args, format);
  vsprintf(buffer,format, args);
  LCD_DIO_printStr(hlcd, buffer);
  va_end(args);
}
#endif
