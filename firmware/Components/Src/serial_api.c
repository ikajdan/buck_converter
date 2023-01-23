/**
 ******************************************************************************
 * @file		: serial_api.c
 * @author  	: AW		Adrian.Wojcik@put.poznan.pl
 * @version 	: 1.3.0
 * @date    	: Oct 19, 2022
 * @brief   	: Serial API: simple output control and input readout
 *
 ******************************************************************************
 */

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial_api.h"

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
 * @brief Reads serial API message into a handler
 * @param[in] hbuck	: Buck handler
 * @param[in] msg	: Input message
 * @retval Parsing status (0 if successful, <0 otherwise)
 */
int Serial_API_ReadMsg(Buck_Handle_TypeDef *hbuck, const char *msg)
{
	// TODO: Rewrite this ugly thing using jsmn parser
	char tmp[128];
	memcpy(tmp, msg, sizeof(tmp));
	char *ptr = strtok(tmp, ",");
	int read[3];
	for (int i = 0; i < 3; i++)
	{
		if (ptr != NULL)
		{
			char *ptr2 = strchr(ptr, ':');
			if (ptr2 + 1 != NULL)
			{
				read[i] = atoi(ptr2 + 1);
			}

			ptr = strtok(NULL, ",");
		}
		else
		{
			break;
		}
	}

	hbuck->TargetVoltage = read[0];
	hbuck->CurrentLimit = read[1];
	hbuck->Output = read[2];

	return 0;
}

/**
 * @brief Writes serial API message from the handler
 * @param[in] hbuck	: Buck handler
 * @param[out] msg	: Output message buffer
 * @retval None
 */
void Serial_API_WriteMsg(Buck_Handle_TypeDef *hbuck, char *msg)
{
	snprintf(msg, SERIAL_API_BUF_SIZE,
			"{\"Voltage\": %d,\"Current\": %d,\"TargetVoltage\": %d,\"CurrentLimit\": %d,\"OutputMode\": %d,\"Output\": %d}\n",
			hbuck->Voltage, hbuck->Current, hbuck->TargetVoltage,
			hbuck->CurrentLimit, hbuck->OutputMode, hbuck->Output);
}
