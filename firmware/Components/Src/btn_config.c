/**
 ******************************************************************************
 * @file		: btn_config.c
 * @author  	: AW		Adrian.Wojcik@put.poznan.pl
 * @version 	: 1.3.0
 * @date    	: Oct 19, 2022
 * @brief   	: Button & switch components configuration file
 *
 ******************************************************************************
 */

/* Private includes ----------------------------------------------------------*/
#include "btn.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
BTN_DIO_Handle_TypeDef hbtn1 = BTN_DIO_INIT_HANDLE(BTN_PRESET1, BTN_PULL_UP);
BTN_DIO_Handle_TypeDef hbtn2 = BTN_DIO_INIT_HANDLE(BTN_PRESET2, BTN_PULL_UP);
BTN_DIO_Handle_TypeDef hbtn3 = BTN_DIO_INIT_HANDLE(BTN_PRESET3, BTN_PULL_UP);
BTN_DIO_Handle_TypeDef hbtn4 = BTN_DIO_INIT_HANDLE(BTN_PRESET4, BTN_PULL_UP);
BTN_DIO_Handle_TypeDef hbtn5 = BTN_DIO_INIT_HANDLE(BTN_OUT, BTN_PULL_UP);
BTN_DIO_Handle_TypeDef hbtn6 = BTN_DIO_INIT_HANDLE(BTN_RESET, BTN_PULL_UP);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
