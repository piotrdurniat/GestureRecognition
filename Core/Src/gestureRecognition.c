/*
 * CDC_MPU6050.c
 *
 * Created on: 03.04.2019
 * Authors: Pawel Rogalinski,
 *          Piotr Durniat,
 *			Grzegorz Gajewski
 */

#include "usbd_cdc_if.h"
#include "USB_tools.h"
#include "sd_hal_mpu6050.h"

extern I2C_HandleTypeDef hi2c2;

SD_MPU6050 mpu1;
SD_MPU6050_Result result;

void setup()
{
    HAL_Delay(600); // For whatever reason this delay is needed for printf to work furher in the code

    result = SD_MPU6050_Init(&hi2c2, &mpu1, SD_MPU6050_Device_0, SD_MPU6050_Accelerometer_2G, SD_MPU6050_Gyroscope_250s);
    HAL_Delay(10);

    if (result != SD_MPU6050_Result_Ok)
    {
        USB_printlnStr("MPU is not working");
        Error_Handler();
    }
}

void blinkLED(uint8_t num, uint32_t time)
{
    for (int i = 0; i < num * 2; i++)
    {
        GPIOC->ODR ^= 1 << 13;
        HAL_Delay(time);
    }
}

void USBCommunication()
{
    int16_t msg = readCharFromBuffer();
    if (msg == -1)
        return;
    uint8_t c = (uint8_t)msg;

    USB_printChar(c);

    switch (c)
    {
    case '1':
        USB_printlnStr("You pressed 1!");
        break;

    case '2':
        USB_printlnStr("Blinking LED 6 times.");
        blinkLED(6, 200);
        break;

    case 'e':
        USB_printlnStr("Throwing testing exception!");
        Error_Handler();
        break;

    case 'h':
        USB_printlnStr("Help not supported yet!");
        break;
    }
}

void sosLed()
{
    while (1)
    {
        blinkLED(3, 90);
        blinkLED(3, 150);
        blinkLED(3, 90);
        HAL_Delay(500);
    }
}

void printSensorData()
{
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

    USB_printlnStr("Acceleration");
    USB_printf("X: %4.2f\n\r", a_x / 1632.0);
    USB_printf("Y: %4.2f\n\r", a_y / 1632.0);
    USB_printf("Z: %4.2f\n\r", a_z / 1632.0);

    USB_printlnStr("Gyroscope");
    USB_printf("X: %d\n\r", g_x);
    USB_printf("Y: %d\n\r", g_y);
    USB_printf("Z: %d\n\r", g_z);

    USB_printlnStr("Temperature");
    USB_printf("%.2f\n\r", temper);
}

void loop()
{
    printSensorData();

    HAL_Delay(100);

    // USBCommunication();
}
