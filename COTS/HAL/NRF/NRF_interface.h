/*
 * NRF_interface.h
 *
 *  Created on: Sep 16, 2021
 *      Author: ahmed
 */

#ifndef NRF_INTERFACE_H_
#define NRF_INTERFACE_H_

void NRF_SPI_INT(void);

void NRF_Bits_Config(void);

void NRF_CE_Enable (void);

void NRF_CE_Disable (void);

void NRF_CSN_Select (void);

void NRF_CSN_UnSelect (void);

void NRF_WriteReg (u8 Reg ,u8 Data);

void NRF_WriteRegMulti (u8 Reg ,u8 *data , u8 Size);

u8 NRF_ReadReg (u8 Reg);

void NRF_ReadRegMulti (u8 Reg ,u8 *data , u8 Size);

void NRF_SendCmd (u8 Cmd);

void NRF_Init (void);

void NRF_TXMode (u8 * Address , u8 Channel);

u8 NRF_Transmit(u8 * data);

void NRF_RXMode (u8 * Address , u8 Channel);

u8 NRF_Check_Data(u8 pipenum);

void NRF_Recieve(u8 *data);

#endif /* NRF_INTERFACE_H_ */
