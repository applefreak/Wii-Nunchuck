/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart.h"
#include "wiichuck.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Delay(uint32_t nCount);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
	
	
int main(void)
{
	USART1_Config();
	chuck_init();
	
	while(1){
		printf("Joystick Angle: %d\r\n",getJoyAngle());
		
		printf("Roll: %d\r\n",getRoll());
		printf("Pitch: %d\r\n",getPitch());
		
		printf("C: %d\r\n",getCstate());
		printf("Z: %d\r\n",getZstate());
		
		Delay(0xFFFFF);
	}
}

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
