/*
 * SPI_interface.h
 *
 *  Created on: Aug 27, 2021
 *      Author: ahmed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*ClkMode*/
#define SPI_u8_IDLELOW_FIRSTEDGE							0
#define SPI_u8_IDLELOW_SECONDEDGE							1
#define SPI_u8_IDLEHIGH_FIRSTEDGE							2
#define SPI_u8_IDLEHIGH_SECONDEDGE							3

/*DataFrameFormat*/
#define SPI_u8_8_BITDATA									0
#define SPI_u8_16_BITDATA									1

/*DataOrder*/
#define SPI_u8_MSB_FIRST									0
#define SPI_u8_LSB_FIRST									1

/*SSManagement*/
#define SPI_u8_HW_SLAVEMANAGEMENET							0
#define SPI_u8_SW_SLAVEMANAGEMENET_LOW						2
#define SPI_u8_SW_SLAVEMANAGEMENET_HIGH						3

/*SSOutputEnable*/
#define SPI_u8_SSOutputDisable								0
#define SPI_u8_SSOutputEnable								1

/*BaudRate*/
#define SPI_u8_PCLK_2										0
#define SPI_u8_PCLK_4										1
#define SPI_u8_PCLK_8										2
#define SPI_u8_PCLK_16										3
#define SPI_u8_PCLK_32										4
#define SPI_u8_PCLK_64										5
#define SPI_u8_PCLK_128										6
#define SPI_u8_PCLK_256										7

/*InterruptState*/
#define SPI_u8_NO_INTERRUPT									0
#define SPI_u8_TX_INTERRUPT									(1<<7)
#define SPI_u8_RX_INTERRUPT									(1<<6)

/*MasterSlaveSelection*/
#define SPI_u8_Slave										0
#define SPI_u8_Master										1

/*SPI_ID*/
#define SPI_u8_SPI1											0
#define SPI_u8_SPI2											1

typedef struct {
	u8 ClkMode;
	u8 DataFrameFormat;
	u8 DataOrder;
	u8 SSManagement;
	u8 SSOutputEnable;
	u8 BaudRate;
	u8 InterruptState;
	u8 MasterSlaveSelection;
}SPI_Config_t;

u8 SPI_u8Init(SPI_Config_t * Copy_PstrSpiConfig);
u8 SPI_u8Transiever(u16 *Copy_Pu16Data);
u8 SPI_u8SetCallBack(u8 Copy_u8IntrIndex,void (*Copy_PvoidtoFunc) (void));

#endif /* SPI_INTERFACE_H_ */
