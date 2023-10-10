/*
 * Module: TWI(I2C)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 *  Created on: Jun 23, 2023
 *      Author: Abdelrhman Hesham
 */

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_


#include "../../OLIB/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/


typedef struct{
 uint8 address;
 uint32 bit_rate;
}TWI_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(TWI_ConfigType* Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* MCAL_I2C_I2C_H_ */
