/**
  ******************************************************************************
  * @file		: btn.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button components driver
  *
  ******************************************************************************
  */
#ifndef INC_BTN_H_
#define INC_BTN_H_

/* Public includes -----------------------------------------------------------*/
#include "dio.h"

/* Public typedef ------------------------------------------------------------*/
/**
  * @brief GPIO (On/Off) button handle structure definition
  */
typedef enum { BTN_PULL_DOWN, BTN_PULL_UP } BTN_PULL_TYPE_TypeDef;
typedef enum { BTN_RELEASED = 0, BTN_PRESSED = 1 } BTN_DIO_State_TypeDef;
typedef enum { BTN_NO_EDGE, BTN_PRESSED_EDGE, BTN_RELEASED_EDGE } BTN_DIO_Edge_TypeDef;

typedef struct {
  DIO_Handle_TypeDef Input;
	BTN_PULL_TYPE_TypeDef Pull;
	BTN_DIO_State_TypeDef PrevState;
} BTN_DIO_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#define BTN_DIO_INIT_HANDLE(USER_NAME, PULL)	\
  { 										                      \
      .Input = DIO_INIT_HANDLE(USER_NAME),    \
			.Pull = PULL,					                	\
			.PrevState = BTN_RELEASED			          \
  }

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
  * @brief Reads button state
  * @param[in] hbtn		: button DIO handler
  * @retval	Button state (BTN_PRESSED or BTN_RELEASED)
  */
BTN_DIO_State_TypeDef BTN_DIO_Read(const BTN_DIO_Handle_TypeDef* hbtn);

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button DIO handler
  * @retval	1 if button is pressed, if if is released
  */
_Bool BTN_DIO_IsPressed(const BTN_DIO_Handle_TypeDef* hbtn);

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button DIO handler
  * @retval	1 if button is released, 0 if is pressed
  */
_Bool BTN_DIO_IsReleased(const BTN_DIO_Handle_TypeDef* hbtn);

/**
  * @brief Detects button state change
  * @param[in/out] hbtn		: button DIO handler
  * @retval	Detected edge (BTN_NO_EDGE, BTN_PRESSED_EDGE or BTN_RELEASED_EDGE)
  */
BTN_DIO_Edge_TypeDef BTN_DIO_EdgeDetected(BTN_DIO_Handle_TypeDef* hbtn);

#endif /* INC_BTN_H_ */
