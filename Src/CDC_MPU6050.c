/*
 * CDC_MPU6050.c
 *
 *  Created on: 03.04.2019
 *  Authors: Pawel Rogalinski,
 *	  		 Piotr Durniat,
 *			 Grzegorz Gajewski
 */

#include "usbd_cdc_if.h"
#include "sd_hal_mpu6050.h"
#include "USB_tools.h"

extern I2C_HandleTypeDef hi2c2;

SD_MPU6050 mpu1;
SD_MPU6050_Result result;


void setup() {
	// TODO co to jest??
	// Inicjalizacja mpu???
	// HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
}



void blinkLED(uint8_t num) {
	for (int i = 0; i < num; i++) {
		GPIOC->ODR ^= 1 << 13;
		HAL_Delay(200);
		GPIOC->ODR ^= 1 << 13;
		HAL_Delay(200);
	}
}

void loop() {

result = SD_MPU6050_Init(&hi2c2, &mpu1, SD_MPU6050_Device_0, SD_MPU6050_Accelerometer_2G, SD_MPU6050_Gyroscope_250s);
HAL_Delay(10);

//if (result == SD_MPU6050_Result_Ok) {
//	//USB_printlnStr("mpu is working");
//} else {
//	//USB_printlnStr("mpu is not working");
//}


//HAL_Delay(100);

SD_MPU6050_ReadTemperature(&hi2c2, &mpu1);
float temper = mpu1.Temperature;
SD_MPU6050_ReadGyroscope(&hi2c2, &mpu1);
int16_t g_x = mpu1.Gyroscope_X;
int16_t g_y = mpu1.Gyroscope_Y;
int16_t g_z = mpu1.Gyroscope_Z;

SD_MPU6050_ReadAccelerometer(&hi2c2, &mpu1);
int16_t a_x = mpu1.Accelerometer_X;
int16_t a_y = mpu1.Accelerometer_Y;
int16_t a_z = mpu1.Accelerometer_Z;

// To enable float  printf:
// check your linker flags (
// Project > Properties > C/C++ Build > Setings > Tool Settings > MCU GCC Linker > Miscellaneous > Linker flags
// if you are using nanolib “-specs=nano.specs” you need to add “-u _printf_float”

// -32000 - 32000

USB_printlnStr("Acceleration");
USB_printlnStr("");

USB_printStr("X:   ");
//USB_printf("%f", 13.2);
//USB_printf("%f \n\r", a_x / 1632.0);
USB_printStr("Y:   ");
USB_printf("%d \n\r", a_y / 1632);
USB_printStr("Z:   ");
USB_printf("%d \n\r", a_z / 1632);


USB_printStr("\n\rTemperature");
//USB_printf("%.2f \n\r", temper);

HAL_Delay(100);
USB_printStr("\33c");




//	 //while(1) {
//	 	int16_t test = readCharFromBuffer();                                                                                             //może na odrót i tu zrobić int8?
//	 	//if (test == -1) break;
//	 	if (test == -1) return;
//	//continue;
//	 	uint8_t c = (uint8_t) test;
//	 	uint8_t tab1[2];
//	 	tab1[0] = c;
//	 	tab1[1] = 0;
//
//	 	//transmit(tab1, 1);
//	 	USB_printStr(tab1);
//
//	 	switch (c) {
//
//	 		case '1':
//	 			USB_printlnStr("You pressed 1!");
//	 			break;
//
//	 		case '2':
//	 			USB_printlnStr("Blinking LED 6 times.");
//	 			HAL_Delay(100);
//	 			blinkLED(6);
//	 			break;
//
//	 		case 'e':
//	 			USB_printlnStr("Throwing testing exception!");
//	 			HAL_Delay(100);
//	 			_Error_Handler(*"", 2);
//	 			break;
//
//	 		case 'h':
//	 			USB_printlnStr("Help not supported yet!");
//	 			break;
//
//	 	}
//	 //}



}
