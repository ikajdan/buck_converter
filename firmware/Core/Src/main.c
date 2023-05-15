/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "aio.h"
#include "buck_config.h"
#include "encoder_config.h"
#include "lcd_config.h"
#include "serial_api_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// Controller parameters
const float KI = 0.01;

// Scaling factor based on the voltage divider
const unsigned int VOLTAGE_MULTIPLIER = 9.2;
// Scaling factor based on the shunt resistor
const unsigned int CURRENT_MULTIPLIER = 10;

static volatile uint16_t ADC1_DATA[2];
static uint16_t DUTY_CYCLE = 0;
static uint8_t UART_BUFFER_RX; // Single character read from the UART
static char UART_MSG[SERIAL_API_BUF_SIZE]; // UART message
static uint8_t UART_MSG_LENGTH = 0; // UART message length
static double ENERGY = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USB_OTG_FS_PCD_Init();
    MX_TIM4_Init();
    MX_USART3_UART_Init();
    MX_ADC1_Init();
    MX_TIM10_Init();
    MX_TIM7_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim10); // 1 kHz
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // 10 kHz
    ENC_Init(&henc1);
    LCD_DIO_Init(&hlcd1);
    HAL_UART_Receive_IT(&huart3, &UART_BUFFER_RX, 1);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1) {
        ENC_GetCounter(&henc1);
        if(henc1.CounterInc) {
            Buck_SetTargetVoltage(&hbuck1, Buck_GetTargetVoltage(&hbuck1) + 100);
        } else if(henc1.CounterDec) {
            Buck_SetTargetVoltage(&hbuck1, Buck_GetTargetVoltage(&hbuck1) - 100);
        }

        char lcd_buffer[LCD_LINE_BUF_LEN];

        float U = Buck_GetVoltage(&hbuck1) / 1000.0;
        float I = Buck_GetCurrent(&hbuck1) / 1000.0;
        float P = U * I;
        ENERGY = ENERGY + P * 0.001;

        snprintf(lcd_buffer, LCD_LINE_LEN, "%5.2f V", U);
        LCD_DIO_SetCursor(&hlcd1, 0, 0);
        LCD_DIO_printStr(&hlcd1, lcd_buffer);

        snprintf(lcd_buffer, LCD_LINE_LEN, "%5.2f A", I);
        LCD_DIO_SetCursor(&hlcd1, 1, 0);
        LCD_DIO_printStr(&hlcd1, lcd_buffer);

        snprintf(lcd_buffer, LCD_LINE_LEN, "%5.2f W", P);
        LCD_DIO_SetCursor(&hlcd1, 0, 8);
        LCD_DIO_printStr(&hlcd1, lcd_buffer);

        snprintf(lcd_buffer, LCD_LINE_LEN, "%5.2f Wh", ENERGY);
        LCD_DIO_SetCursor(&hlcd1, 1, 8);
        LCD_DIO_printStr(&hlcd1, lcd_buffer);

        static char uart_buffer_tx[SERIAL_API_BUF_SIZE];
        Serial_API_WriteMsg(&hbuck1, uart_buffer_tx);
        HAL_UART_Transmit_IT(&huart3, (uint8_t*)uart_buffer_tx, strlen(uart_buffer_tx));

        HAL_Delay(250);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure LSE Drive Capability
     */
    HAL_PWR_EnableBkUpAccess();

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Activate the Over-Drive mode
     */
    if(HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/**
 * @brief  Period elapsed callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if(htim == &htim10) {
        // ADC DMA request
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_DATA, hadc1.Init.NbrOfConversion);
    }
}

/**
 * @brief  Regular conversion complete callback in non blocking mode
 * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
 *         the configuration information for the specified ADC.
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if(hadc == &hadc1) {
        // Store values in the struct
        Buck_SetVoltage(&hbuck1, ADC_REG2VOLTAGE(ADC1_DATA[0] * VOLTAGE_MULTIPLIER));
        Buck_SetCurrent(&hbuck1, ADC_REG2VOLTAGE(ADC1_DATA[1] * CURRENT_MULTIPLIER));

        // Control loop
        int16_t error = (int16_t)Buck_GetTargetVoltage(&hbuck1) - (int16_t)Buck_GetVoltage(&hbuck1);
        float du = KI * error;

        DUTY_CYCLE += du;

        // Simple regulation
        //		if (Buck_GetVoltage(&hbuck1) < Buck_GetTargetVoltage(&hbuck1))
        //		{
        //			DUTY_CYCLE = DUTY_CYCLE + 1;
        //			if (DUTY_CYCLE > 100)
        //			{
        //				DUTY_CYCLE = 100;
        //			}
        //		}
        //		else
        //		{
        //			DUTY_CYCLE = DUTY_CYCLE - 1;
        //			if (DUTY_CYCLE < 0)
        //			{
        //				DUTY_CYCLE = 0;
        //			}
        //		}

        if(Buck_GetOutput(&hbuck1) == 1) {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 100 - DUTY_CYCLE);
        } else {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 100); // Output disabled
        }
    }
}

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == BTN_OUT_Pin) {
        Buck_ToggleOutput(&hbuck1);
    } else if(GPIO_Pin == BTN_RESET_Pin) {
        ENERGY = 0;
    } else if(GPIO_Pin == BTN_PRESET1_Pin) {
        Buck_SetTargetVoltage(&hbuck1, 1500);
    } else if(GPIO_Pin == BTN_PRESET2_Pin) {
        Buck_SetTargetVoltage(&hbuck1, 3300);
    } else if(GPIO_Pin == BTN_PRESET3_Pin) {
        Buck_SetTargetVoltage(&hbuck1, 5000);
    } else if(GPIO_Pin == BTN_PRESET4_Pin) {
        Buck_SetTargetVoltage(&hbuck1, 12000);
    }
}

/**
 * @brief  Rx Transfer completed callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart == &huart3) {
        if(UART_BUFFER_RX == '\n' || UART_BUFFER_RX == '\r') {
            if(UART_MSG_LENGTH > 0) {
                UART_MSG[UART_MSG_LENGTH] = '\0';
                UART_MSG_LENGTH = 0;
                Serial_API_ReadMsg(&hbuck1, UART_MSG);
            }
        } else {
            if(UART_MSG_LENGTH >= SERIAL_API_BUF_SIZE - 1) {
                UART_MSG_LENGTH = 0;
            }
            UART_MSG[UART_MSG_LENGTH++] = UART_BUFFER_RX;
        }

        HAL_UART_Receive_IT(&huart3, &UART_BUFFER_RX, 1);
    }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while(1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
