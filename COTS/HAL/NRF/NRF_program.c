/*
 * NRF_program.c
 *
 *  Created on: Sep 3, 2021
 *      Author: ahmed
 */
#include "STD_TYPES.h"
#include "STM32f103xx.h"
#include "BIT_Math.h"
#include "RCC_Interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "NRF_Reg.h"
#include "NRF_interface.h"

#define NRF_CE_PORT GPIO_u8_GPIOB
#define NRF_CE_PIN  GPIO_u8_PIN5

#define NRF_CSN_PORT GPIO_u8_GPIOB
#define NRF_CSN_PIN  GPIO_u8_PIN6



void NRF_SPI_INT(void){
	RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS,RCC_APB2ENR_IOPAEN);
	RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS,RCC_APB2ENR_IOPBEN);
	RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS,RCC_APB2ENR_SPI1EN);

	/*setting MOSI CLK SS OUTPUT ALTERNATE FUNCTION PUSH PULL*/
	GPIO_PortConfig_t SPI_PINSCONFIG = {GPIO_u8_GPIOA, 11<<4, GPIO_u8_MODE_OUTPUT_AF_PP_10MHZ};
	GPIO_PinConfig_t  SPI_MISOCONFIG = {GPIO_u8_GPIOA, GPIO_u8_PIN6,GPIO_u8_MODE_INPUT_FLOATING};
	SPI_Config_t SPI_CONFIG = {  SPI_u8_IDLELOW_FIRSTEDGE
							    ,SPI_u8_8_BITDATA
							    ,SPI_u8_MSB_FIRST
							    ,SPI_u8_HW_SLAVEMANAGEMENET
							    ,SPI_u8_SSOutputEnable
							    ,SPI_u8_PCLK_4
							    ,SPI_u8_NO_INTERRUPT
							    ,SPI_u8_Master};

	GPIO_u8PortInit(&SPI_PINSCONFIG);
	GPIO_u8PinInit(&SPI_MISOCONFIG);



	SPI_u8Init(&SPI_CONFIG);
}


void NRF_Bits_Config(void){
	GPIO_PinConfig_t pin ={NRF_CE_PORT,NRF_CE_PIN,GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ};
	GPIO_u8PinInit(&pin);

	pin.PinId = NRF_CSN_PIN;
	GPIO_u8PinInit(&pin);

}

void NRF_CE_Enable (void){
	GPIO_PinConfig_t pin ={NRF_CE_PORT,NRF_CE_PIN,GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ};
	GPIO_u8SetPinValue(&pin ,GPIO_u8_HIGH);
}

void NRF_CE_Disable (void){
	GPIO_PinConfig_t pin ={NRF_CE_PORT,NRF_CE_PIN,GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ};
	GPIO_u8SetPinValue(&pin ,GPIO_u8_LOW);
}

void NRF_CSN_Select (void){
	GPIO_PinConfig_t pin ={NRF_CE_PORT,NRF_CSN_PIN,GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ};
	GPIO_u8SetPinValue(&pin ,GPIO_u8_LOW);
}

void NRF_CSN_UnSelect (void){
	GPIO_PinConfig_t pin ={NRF_CE_PORT,NRF_CSN_PIN,GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ};
	GPIO_u8SetPinValue(&pin ,GPIO_u8_HIGH);
}



void NRF_WriteReg (u8 Reg ,u8 Data){

	u8 buf[2];
	buf[0] = Reg | 1<<5;
	buf[1] = Data;

	//Pull CSN Low to Select Device
	NRF_CSN_Select();

	SPI_u8Transmit_Multi(buf,2);

	//Pull CSN High to Release Device
	NRF_CSN_UnSelect();
}


void NRF_WriteRegMulti (u8 Reg ,u8 *data , u8 Size){

	u8 buf[2];
	buf[0] = Reg | 1<<5;
	NRF_CSN_Select();

	SPI_u8Transmit(buf[0]);
	SPI_u8Transmit_Multi(data,Size);

	NRF_CSN_UnSelect();


}


u8 NRF_ReadReg (u8 Reg){

	u8 data=0;

	//Pull CSN Low to Select Device
	NRF_CSN_Select();

	SPI_u8Transmit(Reg);
	SPI_u8Transiever(&data);

	//Pull CSN High to Release Device
	NRF_CSN_UnSelect();

	return data;
}


void NRF_ReadRegMulti (u8 Reg ,u8 *data , u8 Size){


	NRF_CSN_Select();

	SPI_u8Transmit(Reg);
	SPI_u8Transiever_Multi(data,Size);

	NRF_CSN_UnSelect();


}


void NRF_SendCmd (u8 Cmd){

	//Pull CSN Low to Select Device
	NRF_CSN_Select();

	SPI_u8Transmit(Cmd);

	//Pull CSN High to Release Device
	NRF_CSN_UnSelect();
}

void NRF_Init (void){
	NRF_CE_Disable();

	NRF_WriteReg(NRF_CONFIG,0);
	NRF_WriteReg(NRF_EN_AA,0);
	NRF_WriteReg(NRF_EN_RXADDR,0);
	NRF_WriteReg(NRF_SETUP_AW,0x03);		// 5 bytes for TX/RX Address
	NRF_WriteReg(NRF_SETUP_RETR,0);
	NRF_WriteReg(NRF_RF_CH,0);
	NRF_WriteReg(NRF_RF_SETUP,0x0E);

	NRF_CE_Enable();
}


void NRF_TXMode (u8 * Address , u8 Channel){
	NRF_CE_Disable();

	NRF_WriteReg(NRF_RF_CH,Channel);

	NRF_WriteRegMulti(NRF_TX_ADDR,Address,5);

	u8 Config = NRF_ReadReg(NRF_CONFIG);
	Config |= 1<<1;
	NRF_WriteReg(NRF_CONFIG, Config);

	NRF_CE_Enable();
}

u8 NRF_Transmit(u8 * data){
	NRF_CSN_Select();

	u8 cmd = 0xA0;
	SPI_u8Transmit(cmd);

	SPI_u8Transmit_Multi(data, 32);

	NRF_CSN_UnSelect();

	STK_u8SetBusyWait(1000000);

	u8 fifo_status = NRF_ReadReg(NRF_FIFO_STATUS);

	if(fifo_status & (1<<4) && (!(fifo_status & (1<<3)))){
		cmd = 0xE1;
		NRF_SendCmd(cmd);
		return 1;
	}


	return 0;
}


void NRF_RXMode (u8 * Address , u8 Channel){
	NRF_CE_Disable();

	NRF_WriteReg(NRF_RF_CH,Channel);

	u8 en_rxaddr = NRF_ReadReg(NRF_EN_RXADDR);
	en_rxaddr |= 0x02;
	NRF_WriteReg(NRF_EN_RXADDR,en_rxaddr);

	NRF_WriteRegMulti(NRF_RX_ADDR_P1,Address,5);

	NRF_WriteReg(NRF_RX_PW_P1, 32);

	u8 Config = NRF_ReadReg(NRF_CONFIG);
	Config |= 3<<0;
	NRF_WriteReg(NRF_CONFIG, Config);

	NRF_CE_Enable();
}

u8 NRF_Check_Data(u8 pipenum){

	u8 status = NRF_ReadReg(NRF_STATUS);

	if((status& (1<<6)) && (status&(pipenum<<1))){

		NRF_WriteReg(NRF_STATUS, 1<<6);  // CLEAR FLAG

		return 1;
	}

	return 0;
}

void NRF_Recieve(u8 *data){
	NRF_CSN_Select();

		u8 cmd = 0x61;
		SPI_u8Transmit(cmd);

		SPI_u8Transmit_Multi(data, 32);

		NRF_CSN_UnSelect();

		STK_u8SetBusyWait(1000000);

		cmd = 0xE2;

		NRF_SendCmd(cmd);



}

