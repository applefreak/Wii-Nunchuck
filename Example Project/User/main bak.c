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
#include "i2c.h"
#include <math.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define chuck_addr 0xA4
#define M_PI 3.14
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t buf[] = {0xf0, 0x55};
const uint8_t buf2[] = {0xfb,0x00};
uint8_t data[6];
const uint8_t databuf[] = {0};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void chuck_init(void);
void Delay(uint32_t nCount);
void printData(const uint8_t *d);
void getUseful(const uint8_t *d);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
	
	
int main(void)
{
	USART1_Config();
	
	I2C_LowLevel_Init(I2C1, 100000, chuck_addr);
	printf("I2C1 Configured...\r\n");
	
	chuck_init();
	printf("Wii Nunchuck Configured...\r\n");
	
// 	I2C_Write(I2C1, databuf, 1, chuck_addr);
// 	printf("Send Read Signal...\r\n");
// 	I2C_Read(I2C1, data, 6, chuck_addr);
// 	printf("Reading...\r\n");
// 	
// 	printf("Data: %s \r\n",&data[0]);
	
	while(1){
		I2C_Write(I2C1, databuf, 1, chuck_addr);
		printf("Send Read Signal...\r\n");
		I2C_Read(I2C1, data, 6, chuck_addr);
		printf("Reading...\r\n");
	
		printf("Data: \r\n");
		//printData(&data[0]);
		getUseful(&data[0]);
		
		Delay(0xFFFF);
	}
}

void chuck_init(void) {
	I2C_Write(I2C1, buf, 2, chuck_addr);
	I2C_Write(I2C1, buf2, 2, chuck_addr);

}

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void printData(const uint8_t *d) {
	uint8_t i;
	for(i=0;i<=5;i++)
		printf("%d \r\n",d[i]);
}

void getUseful(const uint8_t *d) {
	int32_t jx=0,jy=0,az=0,ay=0,ax=0,c=0,z=0;
	
	jx = d[0];
	jy = d[1];
	
	az = d[4] << 2;
	az = az | ((d[5] & 0xC0) >> 6);
	
	ay = d[3] << 2;
	ay = ay | ((d[5] & 0x30) >> 4);
	
	ax = d[2] << 2;
	ax = az | ((d[5] & 0x0C) >> 2);
	
	 c = !((d[5] & 0x02) >> 1);
	 z = !((d[5] & 0x01));
	
	printf("jx = %d\r\n",jx);
	printf("jy = %d\r\n",jy);
	printf("ax = %d\r\n",ax);
	printf("ay = %d\r\n",ay);
	printf("az = %d\r\n",az);
	printf("c = %d\r\n",c);
	printf("z = %d\r\n",z);

	//printf("Roll: %d\r\n",(int)(atan(ay/sqrt(pow(ax,2)+pow(az,2)))));
	//printf("Pitch: %d\r\n",(int)(atan(ax/sqrt(pow(ay,2)+pow(az,2)))));
	
  //printf("Roll: %d\r\n",(int) (atan2((double)ax, (double)az ) * 180 / M_PI  ));
	//printf("Pitch: %d\r\n",(int) (atan2((double)ay, (double)az) * 180 / M_PI  ));
	
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
