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

extern I2C_HandleTypeDef hi2c2;


void setup()
{
}

void blinkLED(uint8_t num)
{
    for (int i = 0; i < num * 2; i++)
    {
        GPIOC->ODR ^= 1 << 13;
        HAL_Delay(200);
    }
}

void loop()
{

    int16_t test = readCharFromBuffer();
    if (test == -1)
        return;
    uint8_t c = (uint8_t)test;
    uint8_t tab1[2];
    tab1[0] = c;
    tab1[1] = 0;

    USB_printlnStr(tab1);

    switch (c)
    {

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
        break;

    case 'h':
        USB_printlnStr("Help not supported yet!");
        break;

    case 'f':
        USB_printlnStr("Testing float printf");
        USB_printf("%.4f\n\r", 20.8922);
        break;

    }
}
