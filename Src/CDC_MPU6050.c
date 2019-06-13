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


SD_MPU6050 mpu1;

SD_MPU6050_Result result;
uint8_t mpu_ok[15] = { "MPU WORK FINE\n" };
uint8_t mpu_not[17] = { "MPU NOT WORKING\n" };

void setup() {
	// TODO co to jest??
	// Inicjalizacja mpu???
	// HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
}

//void transmit(uint8_t* Buf, uint16_t Len) {
//	int limit = 200;
//	int iterations = 0;
//	while (1) {
//		if (CDC_Transmit_FS(Buf, Len) == USBD_OK) {
//			break;
//		}
//		iterations++;
//		if (iterations > limit) {
//			_Error_Handler(*"", 2);
//		}
//		HAL_Delay(1);
//	}
//
//}

void blinkLED(uint8_t num) {
	for (int i = 0; i < num; i++) {
		GPIOC->ODR ^= 1 << 13;
		HAL_Delay(200);
		GPIOC->ODR ^= 1 << 13;
		HAL_Delay(200);
	}
}

void loop() {
	while(1) {
		int16_t test = readCharFromBuffer();                                                                                             //może na odrót i tu zrobić int8?
		if (test == -1) break;                                                                                                           //continue;
		uint8_t c = (uint8_t) test;
		uint8_t tab1[2];
		tab1[0] = c;
		tab1[1] = 0;

		//transmit(tab1, 1);
		USB_printStr(tab1);

		switch (c) {

			case '1':
				USB_printlnStr("You pressed 1!");
				break;

			case '2':
				USB_printlnStr("Blinking LED 6 times.");
				HAL_Delay(100);
				blinkLED(6);
				break;

			case 'e':
				USB_printlnStr("Throwing testing exception!");
				HAL_Delay(100);
				_Error_Handler(*"", 2);
				break;

			case 'h':
				USB_printlnStr("Help not supported yet!");
				break;

		}

		// if (c == '1') {
		// 	char* temp = "You pressed 1!\r\n";
		// 	transmit(temp, strlen(temp));
		// }
		//
		// if (c == '2') {
		// 	char* temp = "Blinking led 10 times.\r\n";
		// 	transmit(temp, strlen(temp));
		//
		// 	HAL_Delay(100);
		// 	for (int i = 0; i < 10; i++) {
		// 		GPIOC->ODR ^= 1 << 13;
		// 		HAL_Delay(100);
		// 		GPIOC->ODR ^= 1 << 13;
		// 		HAL_Delay(800);
		// 	}
		// }
		//
		// if (c == 'e') {
		// 	char* temp = "Throwing testing exception!\r\n";
		// 	transmit(temp, strlen(temp));
		//
		// 	HAL_Delay(100);
		// 	_Error_Handler(*"", 2);
		// }
		//
		// if (c == 'h') {
		// 	char* temp = "Help not supported yet!\r\n";
		// 	transmit(temp, strlen(temp));
		// }



		// result = SD_MPU6050_Init(&hi2c1,&mpu1,SD_MPU6050_Device_0,SD_MPU6050_Accelerometer_2G,SD_MPU6050_Gyroscope_250s );
		// HAL_Delay(500);
		//
		// if (result == SD_MPU6050_Result_Ok) {
		// 		SD_UART_Send(&huart1,mpu_ok,(uint16_t)15);
		// } else {
		// 		SD_UART_Send(&huart1,mpu_not,(uint16_t)17);
		// }
		// HAL_Delay(500);
		// SD_MPU6050_ReadTemperature(&hi2c1,&mpu1);
		// float temper = mpu1.Temperature;
		// SD_MPU6050_ReadGyroscope(&hi2c1,&mpu1);
		// int16_t g_x = mpu1.Gyroscope_X;
		// int16_t g_y = mpu1.Gyroscope_Y;
		// int16_t g_z = mpu1.Gyroscope_Z;
		//
		// SD_MPU6050_ReadAccelerometer(&hi2c1,&mpu1);
		// int16_t a_x = mpu1.Accelerometer_X;
		// int16_t a_y = mpu1.Accelerometer_Y;
		// int16_t a_z = mpu1.Accelerometer_Z;
		// }

	}

}
