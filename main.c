/*
 * main.c
 *
 *  Created on: Jun 23, 2023
 *      Author: Abdelrhman Hesham
 */

#include <avr/io.h>
#include <util/delay.h>

#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/DCMOTOR/dcmotor.h"
#include "../HAL/EEPROM/eeprom.h"
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/UART/uart.h"
#include "../OLIB/std_types.h"




#define NO_TO_PASS 5
#define address_pass 0x000E


uint8 g_teck = 0 ;
uint8 gflag=0;
uint8  counttocheck=0 ;



typedef enum{
	SUD,STP
}status;


void passSave(void);
void oDoor(void);
void passALTER(void);
void oMotor(void);
void wrong(void);
void buzzer(void);


int main(void)
{

	SREG   |= (1<<7);


	DcMotor_Init();

	Buzzer_init();


	TWI_ConfigType twiConfig={0b00000010,400000};

	TWI_init(&twiConfig);


	UART_ConfigType uartConfig={BD8,DISABLED,ONE_BIT,9600};

	UART_init(&uartConfig);
	passSave();



	while(1)
	{
		if(UART_recieveByte()=='+')
		{
			oDoor();
		}
		else if(UART_recieveByte()=='-')
		{
			passALTER();
		}
	}



}


void passSave(void)
{

	uint8 arr[5]={0};

	status st=SUD;


	for(int i=0;i<NO_TO_PASS;i++)
	{

		arr[i]=UART_recieveByte();

	}

	for(int i=0;i<NO_TO_PASS;i++)

	{

		if(arr[i]!=UART_recieveByte())

		{

			st=STP;
		}
	}

	UART_sendByte(st);

	if(st==STP)
	{

		passSave();
	}
	else
	{
		for(int i=0;i<NO_TO_PASS;i++)
		{

			_delay_ms(10);

			EEPROM_writeByte(address_pass+i,arr[i]);
		}
	}
}





void oDoor(void)
{

	uint8 read;

	status st=SUD;

	for(int i=0;i<NO_TO_PASS;i++)
	{
		_delay_ms(10);

		EEPROM_readByte(address_pass+i, &read);

		if(read!=UART_recieveByte())
		{
			st=STP;
		}
	}

	UART_sendByte(st);

	if(st==SUD)
	{
		counttocheck=0;
		Timer1_setCallBack(oMotor);
		Timer1_ConfigType t1Config={0,0,PS_64_T1,NORM_T1,NONE,TOGGLE_T1};
		Timer1_init(&t1Config);
	}
	else if(st==STP)
	{
		counttocheck++;

		if(counttocheck==3)

		{
			counttocheck=0;

			wrong();
		}

		else

		{
			oDoor();
		}
	}
}



void passALTER(void)
{
	uint8 read;

	status st=SUD;
	for(int i=0;i<NO_TO_PASS;i++)
	{
		_delay_ms(10);
		EEPROM_readByte(address_pass+i, &read);


		if(read!=UART_recieveByte())
		{
			st=STP;
		}
	}
	UART_sendByte(st);

	if(st==SUD)

	{
		counttocheck=0;
		passSave();
	}
	else
	{
		counttocheck++;

		if(counttocheck==3)
		{

			counttocheck=0;

			wrong();

		}
		else
		{
			passALTER();
		}

	}
}




void oMotor(void)
{
	g_teck++;


	if(g_teck==66)
	{
		DcMotor_Rotate(NO_ROTATION,100);

		Timer1_deInit();

		g_teck=0;
	}

	else if(g_teck<30)
	{

		DcMotor_Rotate(CW_ROTATION,100);

	}
	else if(g_teck<36)

	{
		DcMotor_Rotate(NO_ROTATION,100);
	}
	else
	{
		DcMotor_Rotate(CCW_ROTATION,100);
	}



}



void wrong(void)
{
	Timer1_setCallBack(buzzer);

	Timer1_ConfigType t1Config={0,0,PS_64_T1,NONE,TOGGLE_T1};


	Timer1_init(&t1Config);
}



void buzzer(void)
{
	g_teck++;

	Buzzer_on();

	if(g_teck==120)
	{
		Buzzer_off();

		g_teck=0;

		Timer1_deInit();
	}

}

