/*
 * buzzer.h
 *
 *  Created on: Jun 23, 2023
 *      Author: Abdelrhman Hesham
 */

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_


#include "../../OLIB/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* DC Motor Driver HW Ports and Pins Ids */

#define BUZZER_PORT_ID   PORTC_ID
#define BUZZER_PIN_ID    PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Buzzer:
 */
void Buzzer_init(void);

/*
 * Description :
 * Turn ON Buzzer
 */
void Buzzer_on(void);

/*
 * Description :
 * Turn OFF Buzzer
 */
void Buzzer_off(void);

#endif /* HAL_BUZZER_BUZZER_H_ */


