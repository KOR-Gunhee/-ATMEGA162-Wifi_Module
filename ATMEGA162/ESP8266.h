/*
 * ESP8266.h
 *
 * Created: 2020-07-08 오전 11:14:16
 *  Author: ghhan
 */ 


#ifndef ESP8266_H_
#define ESP8266_H_

char AT_RST[50];     
char AT_CWMODE[50];     
char AT_CWSAP[50]; 
char AT_CWJAP[50];
char AT_CIFSR[50];
char AT_CIPMUX[50];
char AT_CIPSTART[100];
char AT_CIPSERVER[50];
char AT_CIPSTATUS[50];
char AT_CIPMODE[50];
char AT_CIPSEND[50];

void ESP8266_Init();
void ESP8266_Init_Test();


#endif /* ESP8266_H_ */