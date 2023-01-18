/**
  ******************************************************************************
  * @file		: btn.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button & switch components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "btn.h"

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
  * @brief Reads button state
  * @param[in] hbtn		: button DIO handler
  * @retval	Button state (BTN_PRESSED or BTN_RELEASED)
  */
BTN_DIO_State_TypeDef BTN_DIO_Read(const BTN_DIO_Handle_TypeDef* hbtn)
{
	_Bool state = DIO_Read(&(hbtn->Input));
	return (hbtn->Pull == BTN_PULL_DOWN) ? state : !state;
}

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button DIO handler
  * @retval	1 if button is pressed, if if is released
  */
_Bool BTN_DIO_IsPressed(const BTN_DIO_Handle_TypeDef* hbtn)
{
	return BTN_DIO_Read(hbtn) == BTN_PRESSED;
}

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button GPIO handler
  * @retval	1 if button is released, 0 if is pressed
  */
_Bool BTN_DIO_IsReleased(const BTN_DIO_Handle_TypeDef* hbtn)
{
	return BTN_DIO_Read(hbtn) == BTN_RELEASED;
}

/**
  * @brief Detects button state change
  * @param[in/out] hbtn		: button DIO handler
  * @retval	Detected edge (BTN_NO_EDGE, BTN_PRESSED_EDGE or BTN_RELEASED_EDGE)
  */
BTN_DIO_Edge_TypeDef BTN_DIO_EdgeDetected(BTN_DIO_Handle_TypeDef* hbtn)
{
	BTN_DIO_State_TypeDef state = BTN_DIO_Read(hbtn);
	BTN_DIO_Edge_TypeDef edge = BTN_NO_EDGE;
	if(state == BTN_PRESSED && hbtn->PrevState == BTN_RELEASED)
		edge = BTN_PRESSED_EDGE;
	else if(state == BTN_RELEASED && hbtn->PrevState == BTN_PRESSED)
		edge = BTN_RELEASED_EDGE;
	hbtn->PrevState = state;
	return edge;
}
