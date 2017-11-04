/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Virtual Com Port Demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x.h"

// X_1 - four LEDs, X_2 - another four LEDs
#define X_1_On()  GPIOE -> ODR |= 0x0000AA00;
#define X_1_Off() GPIOE -> ODR &= ~(0x0000AA00);
#define X_2_On()  GPIOE -> ODR |= 0x00005500;
#define X_2_Off() GPIOE -> ODR &= ~(0x00005500);

GPIO_InitTypeDef gpio;
extern int ticks;

inline int millis(void) {
	return ticks;
}

void delay() {
	int time = 1000;
	int start, end;
	start = millis();
	end = start + time;
	while ((millis() >= start) && (millis() < end)) {}
}

void SysTickInit(int frequency) {
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	(void)SysTick_Config(RCC_Clocks.HCLK_Frequency / frequency);
}

int main(void) {	
	// it's important part
	Set_System();
  	Set_USBClock();
  	USB_Interrupts_Config();
  	USB_Init();
	
	// it's for LEDs
	SysTickInit(600);
	RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	
	GPIOE -> MODER |= GPIO_MODER_MODER15_0 | GPIO_MODER_MODER14_0 | 
	GPIO_MODER_MODER13_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER11_0| 
	GPIO_MODER_MODER10_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER8_0;
	
	while(1) {
		X_1_On();
		delay();
		X_1_Off();
		delay();
		X_2_On();
		delay();
		X_2_Off();
		delay();
	}
}
#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
