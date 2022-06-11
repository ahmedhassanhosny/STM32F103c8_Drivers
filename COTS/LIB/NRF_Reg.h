/*
 * NRF_Reg.h
 *
 *  Created on: Sep 15, 2021
 *      Author: ahmed
 */

#ifndef NRF_REG_H_
#define NRF_REG_H_

#define NRF_CONFIG						*((volatile u8*)0x00)
#define NRF_EN_AA						*((volatile u8*)0x01)
#define NRF_EN_RXADDR					*((volatile u8*)0x02)
#define NRF_SETUP_AW					*((volatile u8*)0x03)
#define NRF_SETUP_RETR					*((volatile u8*)0x04)
#define NRF_RF_CH						*((volatile u8*)0x05)
#define NRF_RF_SETUP					*((volatile u8*)0x06)
#define NRF_STATUS						*((volatile u8*)0x07)
#define NRF_OBSERVE_TX					*((volatile u8*)0x08)
#define NRF_RPD							*((volatile u8*)0x09)
#define NRF_RX_ADDR_P0					*((volatile u8*)0x0A)
#define NRF_RX_ADDR_P1					*((volatile u8*)0x0B)
#define NRF_RX_ADDR_P2					*((volatile u8*)0x0C)
#define NRF_RX_ADDR_P3					*((volatile u8*)0x0D)
#define NRF_RX_ADDR_P4					*((volatile u8*)0x0E)
#define NRF_RX_ADDR_P5					*((volatile u8*)0x0F)
#define NRF_TX_ADDR						*((volatile u8*)0x10)
#define NRF_RX_PW_P0					*((volatile u8*)0x11)
#define NRF_RX_PW_P1					*((volatile u8*)0x12)
#define NRF_RX_PW_P2					*((volatile u8*)0x13)
#define NRF_RX_PW_P3					*((volatile u8*)0x14)
#define NRF_RX_PW_P4					*((volatile u8*)0x15)
#define NRF_RX_PW_P5					*((volatile u8*)0x16)
#define NRF_FIFO_STATUS					*((volatile u8*)0x17)



#endif /* NRF_REG_H_ */
