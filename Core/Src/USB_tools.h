/*
 * USB_tools.h
 *
 * Created on: 13.04.2019
 * Author: Pawe� Rogalinski
 */

#ifndef USB_TOOLS_H_
#define USB_TOOLS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_cdc.h"

/********************************************************
 * Funkcje USB_print... zwracaj�:
 *    USBD_OK   - dane zosta�y wys�ane poprawnie
 *    USBD_BUSY - dane nie wys�ane (USB zaj�ty i up�yn�� czas oczekiwania)
 *    USBD_FAIL - dane nie wys�ane - niepowodzenie transmisji.
 *******************************************************/

uint8_t USB_printStr(char *str);
uint8_t USB_printlnStr(char *str);
uint8_t USB_printf(const char * format, ... );
uint8_t USB_printChar(char c);
uint8_t USB_write(uint8_t *data, uint16_t length);

// Ustawienie maksymlnego czasu oczekiwania gdy
// USB jest zaj�ty (w milisekundach).
void USB_setMaxBusyTime(uint32_t ms);

   // Gdy wyst�pi b��d transmisji funkcje
   // USB_print... nie wywo�uj� funkcji error()
   // Warto�� domy�lna.
 #define IGNORE_TRANSMIT_FAILURE  0

   // Gdy wyst�pi b��d transmisji funkcje
   // USB_print... wywo�uj� globaln� funkcj� error()
 #define CATCH_TRANSMIT_FAILURE   1

void USB_setTransmitFailureMode(uint8_t mode);

/*****************************************************
* UWAGA: Funkcje USB_read... dzia�aj� w trybie blokuj�cym
* (tzn. oczekuj� na odebranie danych z interfejsu USB)
* Przed wywo�aniem tych funkcji mo�na sprawdzi� czy w buforze
* s� dost�pne dane za pomoc� funkcji USB_availableBytes().
*
*****************************************************/

char USB_readChar(void);
void USB_readLine(char * buffer, uint16_t buffer_size);
void USB_readData(uint8_t *buffer, uint16_t buffer_size);

uint16_t USB_availableBytes();

#ifdef __cplusplus
}
#endif

#endif /* USB_TOOLS_H_ */
