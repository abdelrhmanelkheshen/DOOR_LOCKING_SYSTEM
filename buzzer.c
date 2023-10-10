/*
 * buzzer.c
 *
 *  Created on: Jun 23, 2023
 *      Author: Abdelrhman Hesham
 */


#include "../../HAL/BUZZER/buzzer.h"

#include "../../MCAL/GPIO/gpio.h"


/*
 * Description :
 * Initialize the Buzzer:
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT); //set direction as output

	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW); //set to LOW initially
}


/*
 * Description :
 * Turn ON Buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH); //Set to HIGH
}

/*
 * Description :
 * Turn OFF Buzzer
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW); //set to LOW
}

