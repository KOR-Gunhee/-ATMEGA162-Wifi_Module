/*
 * ISR.c
 *
 * Created: 2020-07-08 오전 11:46:18
 *  Author: ghhan
 */ 
#include "Board.h"

char str_us0[50]="";
char str_us1[150]="";
char us0_rx_buf[50]="";
char us1_rx_buf[50]="";
char us0_rx_ch;
char us1_rx_ch;
char str_ip[50]="";
char str_chip[50]="";
uint8_t us0_rx_cnt=0;
uint8_t us1_rx_cnt=0;

int test_cnt=0;


SIGNAL(USART1_RXC_vect)
{
	if (UDP_mode==1)
	{
		transmitByte_usart0(UDR1);
	}
	else
	{
		us1_rx_ch=UDR1;
		us1_rx_buf[us1_rx_cnt++] = us1_rx_ch;
		
		if (us1_rx_ch=='\n')
		{
			memset(str_us1,'\0',150);
			memcpy(str_us1,us1_rx_buf,us1_rx_cnt);
			memset(us1_rx_buf,'\0',50);
			
			if (strstr(str_us1, "+IPD") != 0)
			{
				if (strstr(str_us1, "IP:") != 0)
				{
					memset(str_chip,'\0',50);
					memcpy(str_chip,str_us1,us1_rx_cnt);
					mode_flag=IPCHANGE_mode;
				}
			}
			
			//if (strstr(str_us1, "STAIP"))
			if (strstr(str_us1, "APIP"))
			{
				memset(str_ip,'\0',50);
				memcpy(str_ip,str_us1,us1_rx_cnt);
				mode_flag=IPSAVE_mode;
			}

			if (strstr(str_us1, "+++") != 0)
			{
				mode_flag=INIT_mode;
			}

			if (strstr(str_us1, "CMD:") != 0)
			{
				mode_flag=CMD_mode;
			}

			us1_rx_cnt = 0;
		}
	}
}