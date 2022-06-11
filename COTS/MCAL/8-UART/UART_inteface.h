/*
 * UART_inteface.h
 *
 *  Created on: Jul 29, 2021
 *      Author: ahmed
 */

#ifndef UART_INTEFACE_H_
#define UART_INTEFACE_H_

/**************************** Interfacing Macros *****************************/

/*Interrupt status macros*/
#define UART_DISABLE_INTERRUPTS                (0x00)
#define UART_ENABLE_TC_INTERRUPT     	       (0x40)
#define UART_ENABLE_RXNE_INTERRUPT	           (0x20)
#define UART_ENABLE_TXE_TC_RXNE_INTERRUPT      (0xE0)


/*baud rate macros for 8 MHZ CLK*/
#define UART_2400_BAUD_RATE                    (0xD05) /*((208 << 4) | 5)*/
#define UART_4800_BAUD_RATE                    (0x683)
#define UART_9600_BAUD_RATE                    (0x341)
#define UART_115200_BAUD_RATE                  (0x45)

/*parity macros*/
#define NO_PARITY						  	   (0)
#define EVEN_PARITY						  	   (2)
#define ODD_PARITY						  	   (3)

/*stop bits macros*/
#define ONE_STOP_BIT					  	   (0)
#define HALF_STOP_BIT					  	   (1)
#define TWO_STOP_BIT					  	   (2)
#define TWO_HALF_STOP_BIT				  	   (3)

/*********************** Structure of init parameters  ***********************/
typedef struct
{
	u8 Word_Length;
	u8 Parity_Selection;
	u8 Stop_Bits;
	u16 Baud_Rate;
}UART_Config_t;

/****************************functions Prototypes*****************************/

/*this function used to configure uart*/
u8 UART1_u8Init(UART_Config_t *Copy_pstrUARTConfig);

/*this function used to send single byte (without interrupt)*/
u8 UART1_u8SendByte(u8 Copy_u8DataByte);

/*this function used to send single byte (with interrupt)*/
u8 UART1_u8SendByte_interrupt(u8 Copy_u8DataByte);

/*this function used to send stream of data(without interrupt)*/
u8 UART1_u8SendStream(u8 *Copy_pu8DataByte, u16 Copy_u16DataSize);

/*this function used to send stream of data(with interrupt)*/
u8 UART1_u8SendStream_interrupt(u8 *Copy_pu8DataByte, u16 Copy_u16DataSize);

/*this function used to recv single byte (without interrupt)*/
u8 UART1_u8RecvByte(u8* Copy_pu8DataByte);

/*this function used to recv single byte (with interrupt)*/
u8 UART1_u8RecvByte_interrupt(u8* Copy_pu8DataByte);

u8 UART1_u8SetCallBack(void (*Copy_pfvoid)(void));

#endif /* UART_INTEFACE_H_ */
