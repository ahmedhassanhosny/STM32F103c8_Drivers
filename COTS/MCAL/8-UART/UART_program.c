/*
 * UART_program.c
 *
 *  Created on: Jul 29, 2021
 *      Author: ahmed
 */

#ifndef UART_PROGRAM_C_
#define UART_PROGRAM_C_

#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART_inteface.h"


static void (*UART1_pvoidFunc)(void) = NULL;
static u8 	UART1_u8InterruptStatusFlag = 0;
static u8 	UART1_u8DataPassedToInterrupt = 0;
/*this function used to configure uart*/
u8 UART1_u8Init(UART_Config_t *Copy_pstrUARTConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_pstrUARTConfig !=NULL){
		Local_u8ErrorState = STD_TYPES_OK;

		UART1 -> CR1 =0;
		UART1 -> CR2 =0;

		/*enable UART1*/
		SET_BIT(UART1 -> CR1,13);
		/*word type*/
		UART1 -> CR1 |= (Copy_pstrUARTConfig -> Word_Length) << 12;
		/*Parity Selection*/
		UART1 -> CR1 |= (Copy_pstrUARTConfig -> Parity_Selection) << 9;
		/*Stop bits selection*/
		UART1 -> CR2 |= (Copy_pstrUARTConfig -> Stop_Bits)	<<	12;
		/*baud rate selction*/
		UART1 -> BRR |= (Copy_pstrUARTConfig -> Baud_Rate);

		/*enable TE*/
		SET_BIT(UART1->CR1,3);
		/*enable RE*/
		SET_BIT(UART1->CR1,2);


	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

/*this function used to send single byte (without interrupt)*/
u8 UART1_u8SendByte(u8 Copy_u8DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(GET_BIT(UART1->SR,7))
	{
		UART1->DR = Copy_u8DataByte;
		while(!GET_BIT(UART1 -> SR, 6));

		CLR_BIT(UART1 -> SR, 6);
	}

	return Local_u8ErrorState;
}

/*this function used to send single byte (with interrupt)*/
u8 UART1_u8SendByte_interrupt(u8 Copy_u8DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	UART1_u8DataPassedToInterrupt = Copy_u8DataByte;
	UART1_u8InterruptStatusFlag=1;
	/*TXE Interrupt Enable*/
	UART1 -> CR1 |= 0x80;


		return Local_u8ErrorState;
}

/*this function used to send stream of data*/
u8 UART1_u8SendStream(u8 *Copy_pu8DataByte, u16 Copy_u16DataSize)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu8DataByte != NULL){
		Local_u8ErrorState = STD_TYPES_OK;

		while(Copy_u16DataSize){

			UART1_u8SendByte(*Copy_pu8DataByte);
			Copy_pu8DataByte++;
			Copy_u16DataSize--;
		}
	}
	else{
		/*Do nothing*/
	}


	return Local_u8ErrorState;
}


u8 UART1_u8SendStream_interrupt(u8 *Copy_pu8DataByte, u16 Copy_u16DataSize)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
		if(Copy_pu8DataByte != NULL){
			Local_u8ErrorState = STD_TYPES_OK;

			while(Copy_u16DataSize){

				UART1_u8SendByte_interrupt(*Copy_pu8DataByte);
				Copy_pu8DataByte++;
				Copy_u16DataSize--;
			}
		}
		else{
			/*Do nothing*/
		}


		return Local_u8ErrorState;
}

/*this function used to recv single byte (without interrupt)*/
u8 UART1_u8RecvByte(u8* Copy_pu8DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(GET_BIT(UART1 -> SR, 5))
		{
			/*Getting the data byte*/
			*Copy_pu8DataByte = UART1 -> DR;

			/*Clearing RXNE flag*/
			CLR_BIT(UART1 -> SR, 5);
		}
		else
		{
			/*Do nothing*/
		}

	return Local_u8ErrorState;
}

/*this function used to recv single byte (without interrupt)*/
u8 UART1_u8RecvByte_interrupt(u8* Copy_pu8DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu8DataByte != NULL)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		/*Enable RXNE interrupt*/
		UART1->CR1 |= 1<<5;

		*Copy_pu8DataByte = UART1_u8DataPassedToInterrupt;
	}

	else
	{
		/*Do nothing*/
	}


	return Local_u8ErrorState;
}

u8 UART1_u8SetCallBack(void (*Copy_pvoidFunc)(void)){
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pvoidFunc != NULL)
		{
		Local_u8ErrorState = STD_TYPES_OK;

		UART1_pvoidFunc=*Copy_pvoidFunc;
		}
	return Local_u8ErrorState;
}

void USART1_IRQHandler(void){

	/*Checking on TXE Flag*/
	if(UART1_u8InterruptStatusFlag == 1)
	{
		UART1_u8InterruptStatusFlag = 2;
		/*Sending data byte to TDR */
		UART1->DR = UART1_u8DataPassedToInterrupt;
		/*TXE Flag cleared when write happened to DR Reg*/

	}
	/*Checking on TC Flag*/
	if(GET_BIT(UART1->SR,6) && UART1_u8InterruptStatusFlag == 2)
	{
		UART1_u8InterruptStatusFlag = 5;
		/*Clear TC Flag*/
		CLR_BIT(UART1->SR,6);
		/*Disable TXE Interrupt*/
		UART1 -> CR1 &= ~0x80;
	}

	if(GET_BIT(UART1->SR,5))
	{
		UART1_u8DataPassedToInterrupt = UART1->DR;
		UART1 -> CR1 &=~(1<<5);
		//UART1_u8DataPassedToInterrupt = 0;

	}

	if(UART1_pvoidFunc != NULL)
	{
		UART1_pvoidFunc();
	}

	else{
		/*Do nothing*/
	}
}


#endif /* UART_PROGRAM_C_ */
