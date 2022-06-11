/*
 * SPI_interface.c
 *
 *  Created on: Aug 27, 2021
 *      Author: ahmed
 */
#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "SPI_config.h"

typedef void (*SPI_pvoidFunc)(void);
SPI_pvoidFunc Global_PfArr[2]={NULL,NULL};
u8 SPI_u8InterruptFlag=0;

static SPI_RegDef_t * SPI_Astr[2] = {SPI1,SPI2};

u8 SPI_u8Init(SPI_Config_t * Copy_PstrSpiConfig){
	u8 Local_u8ErrorState=STD_TYPES_OK;

	/*Clk Mode*/
	SPI_Astr[SPI_u8SPIID]->CR1 &= ~(3<<0);
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->ClkMode;

	/*Data Frame Format*/
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->DataFrameFormat << 11;

	/*Data Order*/
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->DataOrder << 7;

	/*SS Management*/
	SPI_Astr[SPI_u8SPIID]->CR1 &= ~(3<<8);
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->SSManagement << 8;

	/*SSOutputEnable*/
	SPI_Astr[SPI_u8SPIID]->CR2 |= Copy_PstrSpiConfig->SSOutputEnable << 2;

	/*Baud Rate*/
	SPI_Astr[SPI_u8SPIID]->CR1 &= ~(7<<3);
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->BaudRate << 3;

	/*Interrupt State*/
	SPI_Astr[SPI_u8SPIID]->CR2 |= Copy_PstrSpiConfig->InterruptState;

	/*Master Slave Selection*/
	SPI_Astr[SPI_u8SPIID]->CR1 |= Copy_PstrSpiConfig->MasterSlaveSelection << 2;

	/*Enable SPI*/
	SPI_Astr[SPI_u8SPIID]->CR1 |= 1 << 6;

	return Local_u8ErrorState;
}
u8 SPI_u8Transiever(u16 *Copy_u16Data){
	u8 Local_u8ErrorState=STD_TYPES_OK;

	/*Load Data to Data Reg*/
	SPI_Astr[SPI_u8SPIID]->DR = *Copy_u16Data;
	/*Waiting Data to transfer to shift register (waiting Transmit buffer empty)*/
	while(GET_BIT(SPI_Astr[SPI_u8SPIID]->SR,1) == 0);

	/*Waiting Data to transfer from shift register to Receive buffer (data in Receive buffer need to read)*/
	while(GET_BIT(SPI_Astr[SPI_u8SPIID]->SR,0) == 0);
	/*reading Data received and flag cleared while reading*/
	*Copy_u16Data = SPI_Astr[SPI_u8SPIID]->DR;

	while(GET_BIT(SPI_Astr[SPI_u8SPIID]->SR,1) == 0);

	/*Waiting transmit to end (waiting busy flag)*/
	//while(GET_BIT(SPI_Astr[SPI_u8SPIID]->SR,7) == 1);


	return Local_u8ErrorState;
}

u8 SPI_u8SetCallBack(u8 Copy_u8IntrIndex,void (*Copy_PvoidtoFunc) (void)){
	u8 Local_u8ErrorState=STD_TYPES_NOK;

	if(Copy_PvoidtoFunc != NULL){
		Local_u8ErrorState=STD_TYPES_OK;
		Global_PfArr[SPI_u8SPIID]=Copy_PvoidtoFunc;
		SPI_u8InterruptFlag = Copy_u8IntrIndex;
	}

	return Local_u8ErrorState;
}

void SPI1_IRQHandler(void){
	if(SPI_u8InterruptFlag == SPI_u8_TX_INTERRUPT){
		SPI_u8InterruptFlag=0;
		Global_PfArr[0]();
		/*disable TX interrupt*/
		CLR_BIT(SPI_Astr[0]->CR2,7);
	}

	if(SPI_u8InterruptFlag == SPI_u8_RX_INTERRUPT){
			SPI_u8InterruptFlag=0;
			Global_PfArr[0]();
			/*disable RX interrupt*/
			CLR_BIT(SPI_Astr[0]->CR2,6);
		}

}

void SPI2_IRQHandler(void){

	if(SPI_u8InterruptFlag == SPI_u8_TX_INTERRUPT){
			SPI_u8InterruptFlag=0;
			Global_PfArr[1]();
			/*disable TX interrupt*/
			CLR_BIT(SPI_Astr[0]->CR2,7);
		}

		if(SPI_u8InterruptFlag == SPI_u8_RX_INTERRUPT){
				SPI_u8InterruptFlag=0;
				Global_PfArr[1]();
				/*disable RX interrupt*/
				CLR_BIT(SPI_Astr[0]->CR2,6);
			}

}
