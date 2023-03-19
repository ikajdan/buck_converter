/**
 ******************************************************************************
 * @file		: serial_api.h
 * @author  	: AW		Adrian.Wojcik@put.poznan.pl
 * @version 	: 1.3.0
 * @date    	: Oct 19, 2022
 * @brief   	: Serial API: simple output control and input readout
 *
 ******************************************************************************
 */

#ifndef INC_SERIAL_API_H_
#define INC_SERIAL_API_H_

/* Public includes -----------------------------------------------------------*/
#include "buck.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
#define SERIAL_API_BUF_SIZE 128

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Reads serial API message into a handler
 * @param[in] hbuck	: Buck handler
 * @param[in] msg	: Input message
 * @retval Parsing status (0 if successful, <0 otherwise)
 */
int Serial_API_ReadMsg(Buck_Handle_TypeDef *hbuck, char *msg);

/**
 * @brief Writes serial API message from the handler
 * @param[in] hbuck	: Buck handler
 * @param[out] msg	: Output message buffer
 * @retval None
 */
void Serial_API_WriteMsg(Buck_Handle_TypeDef *hbuck, char *msg);

#endif /* INC_SERIAL_API_H_ */
