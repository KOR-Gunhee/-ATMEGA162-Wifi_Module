/*
 * ISR.h
 *
 * Created: 2020-07-08 오전 11:46:11
 *  Author: ghhan
 */ 


#ifndef ISR_H_
#define ISR_H_

char str_us0[50];
char str_us1[150];
char us0_rx_buf[50];
char us1_rx_buf[50];
char us0_rx_ch;
char us1_rx_ch;
char str_ip[50];
char str_chip[50];
uint8_t us0_rx_cnt;
uint8_t us1_rx_cnt;

uint8_t mode_flag;
uint8_t UDP_mode;

SIGNAL(USART0_RX_vect);
SIGNAL(USART1_RX_vect);



#endif /* ISR_H_ */