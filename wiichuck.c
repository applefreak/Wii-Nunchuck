/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "wiichuck.h"
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
//void getUseful(const uint8_t *d);

void chuck_init(void) {
	I2C_LowLevel_Init(I2C1, 100000, chuck_addr);
  I2C_Write(I2C1, buf, 2, chuck_addr);
	I2C_Write(I2C1, buf2, 2, chuck_addr);
}

void chuck_read(void) {
	I2C_Write(I2C1, databuf, 1, chuck_addr);
	I2C_Read(I2C1, data, 6, chuck_addr);
}

int32_t getAX(void) {
	chuck_read();
	return ((data[2] << 2) | ((data[5] & 0x0C) >> 2))-512;
}

int32_t getAY(void) {
	chuck_read();
	return ((data[3] << 2) | ((data[5] & 0x30) >> 4))-512;
}

int32_t getAZ(void) {
	chuck_read();
	return ((data[4] << 2) | ((data[5] & 0xC0) >> 6))-512;
}

int32_t getJX(void) {
	chuck_read();
	return data[0]-131;
}

int32_t getJY(void) {
	chuck_read();
	return data[1]-131;
}

uint8_t getCstate(void) {
	chuck_read();
	return !((data[5] & 0x02) >> 1);
}

uint8_t getZstate(void) {
	chuck_read();
	return !((data[5] & 0x01));
}

int32_t getRoll(void) {
	//return (atan(getAY()/sqrt(pow(getAX(),2)+pow(getAZ(),2))));
	return (atan2(getAX(), getAZ() ) * 180 / M_PI  );
}

int32_t getPitch(void) {
	//return (atan(getAX()/sqrt(pow(getAY(),2)+pow(getAZ(),2))));
	return (atan2(getAY(), getAZ()) * 180 / M_PI  );
}

int32_t getJoyAngle(void) {
	return (atan2(getJY() , getJX()) * 180 / M_PI);
}
