/*
 * DMA_interface.h
 *
 *  Created on: Jul 27, 2021
 *      Author: ahmed
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_


/***************************** macros *******************************************/
#define DMA_CHANNEL1					(u8)0
#define DMA_CHANNEL2					(u8)1
#define DMA_CHANNEL3					(u8)2
#define DMA_CHANNEL4					(u8)3
#define DMA_CHANNEL5					(u8)4
#define DMA_CHANNEL6					(u8)5
#define DMA_CHANNEL7					(u8)6

#define DMA_PRI_LOW						(u8)0
#define DMA_PRI_MED						(u8)1
#define DMA_PRI_HIGH					(u8)2
#define DMA_PRI_VHIGH					(u8)3

#define DMA_DS_1BYTE					(u8)0
#define DMA_DS_2BYTES					(u8)1
#define DMA_DS_3BYTES					(u8)2

#define DMA_PER_to_MEM					(u8)0
#define DMA_MEM_to_PER					(u8)1
#define DMA_MEM_to_MEM					(u8)2

#define DMA_DIS_AUTOINC					(u8)0
#define DMA_EN_AUTOINC					(u8)3

#define DMA_DIS_CIRCULAR				(u8)0
#define DMA_EN_CIRCULAR					(u8)1

#define DMA_EN_TCI						(u8)1
#define DMA_EN_HTI						(u8)2
#define DMA_EN_TEI						(u8)3


/***************************** Config Struct ************************************/

typedef struct
{
	u8 ChannelNumber;
	u8 PriorityLvl;
	u8 DataSize;
	u8 DataTransferType;
	u8 IncrementMode;
	u8 CircularMode;
	u8 Interrupt;
}DMA_ConfigStruct_t;


typedef struct
{
	u32 SrcAddress;
	u32 DesAddress;
	u16 NumberofTrans;
}DMA_Config_Transfer_t;

/***************************** Functions Prototypes *****************************/
u8 DMA_u8ChannelInit(DMA_ConfigStruct_t* Copy_PstrConfig);

u8 DMA_u8ChannelTransfer(u8 Copy_u8ChannelNum ,DMA_Config_Transfer_t * Copy_PstrConfigTrans);

u8 DMA_u8ChannelTransfer_busyWait(u8 Copy_u8ChannelNum ,DMA_Config_Transfer_t * Copy_PstrConfigTrans);

u8 DMA_u8DMASetCallBack(u8 Copy_u8ChanneNumber,void(*pf)(void));

#endif /* DMA_INTERFACE_H_ */
