/*
 * Board.h
 *
 * Created: 2020-07-07 오전 10:52:25
 *  Author: ghhan
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "Uart.h"
#include "LCD1602.h"
#include "ESP8266.h"
#include "ISR.h"

#define IPSAVE_mode 0x01
#define IPCHANGE_mode 0x02
#define INIT_mode 0x03
#define CMD_mode 0x04

#endif /* BOARD_H_ */