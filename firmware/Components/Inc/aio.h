/**
  ******************************************************************************
  * @file     : dio.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Analog inputs/outputs components header.
  *
  ******************************************************************************
  */

#ifndef INC_AIO_H_
#define INC_AIO_H_

/* Public includes -----------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
#define ADC_BIT_RES      12      // [bits]
#define ADC_REG_MAX      (float)((1ul << ADC_BIT_RES) - 1)
#define ADC_VOLTAGE_MAX  3.3f    // [V]

#define ADC1_NUMBER_OF_CONV  2
#define ADC1_TIMEOUT         10 // [ms]

#define DAC_BIT_RES      12    // [bits]
#define DAC_REG_MAX      (float)((1ul << DAC_BIT_RES) - 1)
#define DAC_VOLTAGE_MAX  3.3f  // [V]

/* Public macro --------------------------------------------------------------*/
/**
 * @brief Linear transformation of 'x' from <amin, amax> to <bmin, bmax>.
 * @param[in] x Input variable
 * @param[in] amin Minimum of input range
 * @param[in] amax Maximum of input range
 * @param[in] bmin Minimum of output range
 * @param[in] bmax Maximum of output range
 * @return Scaled output variable in <bmin, bmax> range
 */
#define __LINEAR_TRANSFORM(x,amin,amax,bmin,bmax) (((x-amin)/(amax-amin))*(bmax-bmin)+bmin)

/**
 * @brief ADC data register to voltage in millivolts.
 * @param[in] reg : Data register
 * @return Input voltage in millivolts
 */
#define ADC_REG2VOLTAGE(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,           \
                                                         0.0f, ADC_REG_MAX,    \
                                                         0.0f, ADC_VOLTAGE_MAX))

/**
 * @brief ADC voltage in volts to data register.
 * @param[in] vol : Output voltage in millivolts
 * @return Data register
 */
#define ADC_VOLTAGE2REG(vol) (uint16_t)(__LINEAR_TRANSFORM(vol/1000.0f,        \
                                                          0.0, ADC_VOLTAGE_MAX,\
                                                          0.0, ADC_REG_MAX ))

/**
 * @brief DAC voltage in millivolts to data register.
 * @param[in] vol : Output voltage in millivolts
 * @return Data register
 */
#define DAC_VOLTAGE2REG(vol) (uint16_t)(__LINEAR_TRANSFORM(vol/1000.0f,\
                                                 0.0, DAC_VOLTAGE_MAX, \
                                                 0.0, DAC_REG_MAX))

/**
 * @brief DAC data register to voltage in millivolts.
 * @param[in] reg : Data register
 * @return Output voltage in millivolts
 */
#define DAC_REG2VOLTAGE(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,           \
                                                         0.0f, DAC_REG_MAX,    \
                                                         0.0f, DAC_VOLTAGE_MAX))
/**
 * @brief DAC voltage in percent to data register.
 * @param[in] vol : Output voltage in percent [0-100]
 * @return Data register
 */
#define DAC_PERCENT2REG(percent) (uint16_t)(__LINEAR_TRANSFORM(percent,\
                                                          0.0, 100.0f, \
                                                          0.0, DAC_REG_MAX))

/**
 * @brief DAC data register to percent
 * @param[in] reg : Data register
 * @return Output voltage percent [0-100]
 */
#define DAC_REG2PERCENT(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,           \
                                                         0.0f, DAC_REG_MAX,    \
                                                         0.0f, 100.0f))

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_AIO_H_ */
