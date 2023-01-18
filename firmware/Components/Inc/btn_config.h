/**
  ******************************************************************************
  * @file		: btn_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button components configuration file
  *
  ******************************************************************************
  */
#ifndef INC_BTN_CONFIG_H_
#define INC_BTN_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "btn.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern BTN_DIO_Handle_TypeDef husrbtn; //<! Blue on-board button ("USER")
extern BTN_DIO_Handle_TypeDef hbtn1; 	//<! THT pushbutton #1
extern BTN_DIO_Handle_TypeDef hbtn2; 	//<! THT pushbutton #2
extern BTN_DIO_Handle_TypeDef hbtn3;
extern BTN_DIO_Handle_TypeDef hbtn4;

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_BTN_CONFIG_H_ */
