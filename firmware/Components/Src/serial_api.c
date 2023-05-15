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
#include "jsmn.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
jsmn_parser JSMN_PARSER;
jsmntok_t JSMN_TOK[64];
/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
///**
// * @brief Comparison of a JSMN_STRING token to a C-string
// * @param[in] json : JSON C-string (token data source)
// * @param[in] tok  : JSMN token for comparison
// * @param[in] str  : C-string for comparison
// * @retval 1 if token content is the same as string, 0 otherwise
// */
//_Bool __jsmn_tok_str_cmp(const char *json, jsmntok_t *tok, const char *str)
//{
//	_Bool is_string = (tok->type == JSMN_STRING);
//	_Bool is_len_eq = ((int)strlen(str) == tok->end - tok->start);
//	_Bool is_str_eq = (strncmp(json + tok->start, str, tok->end - tok->start) == 0);
//	return is_string && is_len_eq && is_str_eq;
//}
//
///**
// * @brief Comparison of a C-string key and value JSMN type with JSMN tokens
// * @param[in] json : JSON C-string (token data source)
// * @param[in] tok  : JSMN token for comparison
// * @param[in] str  : C-string for key comparison
// * @param[in] type : JSMN token type for value type comparison
// * @retval 1 if token is contains given key and next tokens have given JSMN type, <0 otherwise
// */
//_Bool __jsmn_tok_keyvalue_cmp(const char *json, jsmntok_t *tok, const char *str, jsmntype_t type)
//{
//	_Bool is_key_eq = __jsmn_tok_str_cmp(json, tok, str);
//	_Bool is_value_type_eq = ((tok+1)->type == type);
//	return is_key_eq && is_value_type_eq;
//}
/* Public functions ----------------------------------------------------------*/
/**
 * @brief Reads serial API message into a handler
 * @param[in] hbuck	: Buck handler
 * @param[in] msg	: Input message
 * @retval Parsing status (0 if successful, <0 otherwise)
 */
int Serial_API_ReadMsg(Buck_Handle_TypeDef *hbuck, char *msg) {
    jsmn_init(&JSMN_PARSER);
    int r = jsmn_parse(&JSMN_PARSER, msg, strlen(msg), JSMN_TOK, sizeof(JSMN_TOK) / sizeof(JSMN_TOK[0]));

    if (r < 1 || JSMN_TOK[0].type != JSMN_OBJECT) {
        // The top-level element is not an object
        return -1;
    }

    if (r < 7) {
        // Too few JSON token. Bailing out.
        return -1;
    }

    char tv[16];
    memcpy(tv, msg + JSMN_TOK[2].start, JSMN_TOK[2].end - JSMN_TOK[2].start);
    int tv_i = atoi(tv);
    hbuck->TargetVoltage = tv_i;

    char cl[16];
    memcpy(cl, msg + JSMN_TOK[4].start, JSMN_TOK[4].end - JSMN_TOK[4].start);
    int cl_i = atoi(cl);
    hbuck->CurrentLimit = cl_i;

    char o[16];
    memcpy(o, msg + JSMN_TOK[6].start, JSMN_TOK[6].end - JSMN_TOK[6].start);
    int o_i = atoi(o);
    hbuck->Output = o_i;

    return 0;
}

/**
 * @brief Writes serial API message from the handler
 * @param[in] hbuck	: Buck handler
 * @param[out] msg	: Output message buffer
 * @retval None
 */
void Serial_API_WriteMsg(Buck_Handle_TypeDef *hbuck, char *msg) {
    snprintf(msg, SERIAL_API_BUF_SIZE, "{\"Voltage\": %d,\"Current\": %d,\"TargetVoltage\": %d,\"CurrentLimit\": %d,\"OutputMode\": %d,\"Output\": %d}\n",
            hbuck->Voltage, hbuck->Current, hbuck->TargetVoltage, hbuck->CurrentLimit, hbuck->OutputMode, hbuck->Output);
}
