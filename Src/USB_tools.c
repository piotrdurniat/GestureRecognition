/*
 * USB_tools.c
 *
 *  Created on: 13.04.2019
 *      Author: Pawel Rogalinski
 */


#include "stm32f1xx.h"
#include "USB_tools.h"


#include "string.h"
#include "stdlib.h"
#include "stdarg.h"


// Tryb reakcji funkcji USB_print... na b��dy transmisji danych:
//   IGNORE_TRANSMIT_FAILURE - nie jest wywo�ywana funkcja error()
//   CATCH_TRANSMIT_FAILURE  - jest wywo�ywana funkcja error()


uint8_t USBTransmitFailureMode = IGNORE_TRANSMIT_FAILURE;

void USB_setTransmitFailureMode(uint8_t mode) {
	USBTransmitFailureMode = mode;
}

// Maksymalny dopuszczalny czas zaj�to�ci interfejsu USB
uint32_t MaxBusyTime = 10;

void USB_setMaxBusyTime(uint32_t ms) {
	MaxBusyTime = ms;
}

uint8_t USB_printStr(char *str) {
	return USB_write(str, strlen(str) + 1);
}


uint8_t USB_printlnStr(char *str) {
	uint8_t result = USB_write(str, strlen(str));
	if (result == USBD_OK) {
		result = USB_printStr("\r\n");
	}
	return result;
}

uint8_t USB_printf( const char * format, ... ) {
	char buffer[120];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);
	return USB_printStr(buffer);
}

uint8_t USB_printChar(char c) {
	return USB_write(&c, 1);
}

uint8_t USB_write(uint8_t *data, uint16_t length) {
	uint8_t result = CDC_Transmit_FS(data, length);
	if (result == USBD_OK) return result;
	if (result == USBD_BUSY) {
		uint32_t tickstart = HAL_GetTick();
		uint32_t wait = MaxBusyTime;

		// Add a freq to guarantee minimum wait
		if (wait < HAL_MAX_DELAY) wait++;

		while ((HAL_GetTick() - tickstart) < wait) {
			result = CDC_Transmit_FS(data, length);
			if (result == USBD_OK) return result;
			if (result == USBD_FAIL) break;
		}
	}
	if (USBTransmitFailureMode == CATCH_TRANSMIT_FAILURE) {
		//error(__FILE__, __LINE__);                         // Brakuje deklaracji funkcji error()
	}
	return result;
}







/*
   UART_HandleTypeDef * UART_handlerPtr = NULL;

   void UART_init(UART_HandleTypeDef * handler){
   UART_handlerPtr = handler;
   }

   void UART_printStr(char *str){
   HAL_UART_Transmit(UART_handlerPtr, (uint8_t*)str, (uint16_t)strlen(str), 1000);
   }

   void UART_printlnStr(char *str){
   HAL_UART_Transmit(UART_handlerPtr, (uint8_t *)str, (uint16_t)strlen(str), 1000);
   HAL_UART_Transmit(UART_handlerPtr, (uint8_t *)"\r\n", 2, 1000);
   }

   void UART_printf(const char * format, ... ) {
   char buffer[120];
   va_list args;
   va_start (args, format);
   vsprintf (buffer,format, args);
   UART_printStr(buffer);
   va_end (args);
   }

   void UART_printChar(char c){
   HAL_UART_Transmit(UART_handlerPtr, (uint8_t*)&c, 1, 1);
   }

   void UART_writeData(uint8_t *data, uint16_t length){
   HAL_UART_Transmit(UART_handlerPtr, (uint8_t *)data, length, 1000);
   }

   char UART_readChar(void){
   HAL_StatusTypeDef status;
   uint8_t current_char;

   status = HAL_UART_Receive(UART_handlerPtr, &current_char, 1, 1);
   if (status == HAL_OK) return current_char;
   return 0;
   }

   void UART_readLine(char * buffer, uint16_t buffer_size){
   HAL_StatusTypeDef status;
   uint8_t current_char;
   uint16_t char_counter = 0;

   while (char_counter < buffer_size - 1) {
    status = HAL_UART_Receive(UART_handlerPtr, &current_char, 1, 1);
    if (status == HAL_OK) {
      if (current_char == '\r' || current_char == '\n'){
        if (char_counter == 0)
          continue;
        else
          break;
      }
 *(buffer + char_counter++) = current_char;
    }
   }
 *(buffer + char_counter) = '\0';
   }

   void UART_readData(uint8_t *buffer, uint16_t buffer_size){
   HAL_UART_Receive(UART_handlerPtr, buffer, buffer_size, 1000);
   }
 */


/*
   void uart_write(UART_HandleTypeDef * handler, char * text) {
   HAL_UART_Transmit(handler, text, (uint16_t)strlen(text), 1000);
   }

   void uart_write_char(UART_HandleTypeDef * handler, char c) {
   HAL_UART_Transmit(handler, (uint8_t*)&c, 1, 1);
   }


   void uart_write_line(UART_HandleTypeDef * handler, char * text) {
   HAL_UART_Transmit(handler, (uint8_t *)text, (uint16_t)strlen(text), 1000);
   HAL_UART_Transmit(handler, (uint8_t *)"\r\n", 2, 1000);
   }


   void uart_read_line(UART_HandleTypeDef * handler, char * buffer,
    uint16_t buffer_size) {
   HAL_StatusTypeDef status;
   uint8_t current_char;
   uint16_t char_counter = 0;

   while (char_counter < buffer_size - 1) {
    status = HAL_UART_Receive(handler, &current_char, 1, 1);
    if (status == HAL_OK) {
      if (current_char == '\r' || current_char == '\n'){
        if (char_counter == 0)
          continue;
        else
          break;
      }
 *(buffer + char_counter++) = current_char;
    }
   }

 *(buffer + char_counter) = '\0';
   }

   char uart_read_char(UART_HandleTypeDef * handler) {
   HAL_StatusTypeDef status;
   uint8_t current_char;

   status = HAL_UART_Receive(handler, &current_char, 1, 1);
   if (status == HAL_OK) return current_char;
   return 0;
   }
 */
