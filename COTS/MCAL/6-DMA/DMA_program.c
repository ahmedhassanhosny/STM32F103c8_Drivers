/*
 * DMA_program.c
 *
 *  Created on: Jul 27, 2021
 *      Author: ahmed
 */

#ifndef DMA_PROGRAM_C_
#define DMA_PROGRAM_C_

#include "STD_TYPES.h"
#include "STM32f103xx.h"
#include "BIT_Math.h"
#include "DMA_private.h"
#include "DMA_config.h"
#include "DMA_interface.h"


typedef void (*fptr_t) (void);

fptr_t Global_pfArr[7]={NULL,NULL,NULL,NULL,NULL,NULL,NULL};


u8 DMA_u8ChannelInit(DMA_ConfigStruct_t* Copy_PstrConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_PstrConfig != NULL){
		Local_u8ErrorState = STD_TYPES_OK;

		DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR=0;

		DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR |= Copy_PstrConfig->PriorityLvl<<12;

		DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR |= Copy_PstrConfig->DataSize << 8 | Copy_PstrConfig->DataSize << 10;

		DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR |=	Copy_PstrConfig->IncrementMode << 6 | Copy_PstrConfig->CircularMode << 5 | 1 << Copy_PstrConfig->Interrupt;

		if(Copy_PstrConfig->DataTransferType == DMA_MEM_to_MEM){

		SET_BIT(DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR,14);

		}
		else{
			DMA->Copy_StrToArrofReg[Copy_PstrConfig->ChannelNumber].CCR |= Copy_PstrConfig->DataTransferType <<4;
		}

	}
	else
	{
		/*Do Nothing*/
	}

	return Local_u8ErrorState;
}



u8 DMA_u8ChannelTransfer(u8 Copy_u8ChannelNum ,DMA_Config_Transfer_t * Copy_PstrConfigTrans)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_PstrConfigTrans != NULL){
			Local_u8ErrorState = STD_TYPES_OK;


			if(GET_BIT(DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CCR, 4) )
			{
				DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CPAR |= Copy_PstrConfigTrans->DesAddress;
				DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CMAR |= Copy_PstrConfigTrans->SrcAddress;
			}
			else
			{
				DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CPAR |= Copy_PstrConfigTrans->SrcAddress;
				DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CMAR |= Copy_PstrConfigTrans->DesAddress;
			}

			DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CNDTR |= Copy_PstrConfigTrans->NumberofTrans;

			/*Channel Enable*/
			DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CCR |=	1;
	}
	else{
		/*Do Nothing*/
	}
	return Local_u8ErrorState;

}
u8 DMA_u8ChannelTransfer_busyWait(u8 Copy_u8ChannelNum ,DMA_Config_Transfer_t * Copy_PstrConfigTrans)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

		if(Copy_PstrConfigTrans != NULL){
				Local_u8ErrorState = STD_TYPES_OK;

				if(GET_BIT(DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CCR, 4) )
				{
					DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CPAR |= Copy_PstrConfigTrans->DesAddress;
					DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CMAR |= Copy_PstrConfigTrans->SrcAddress;
				}
				else
				{
					DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CPAR |= Copy_PstrConfigTrans->SrcAddress;
					DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CMAR |= Copy_PstrConfigTrans->DesAddress;
				}

				DMA->Copy_StrToArrofReg[Copy_u8ChannelNum].CNDTR |= Copy_PstrConfigTrans->NumberofTrans;

				/*polling over TC flag*/
				while(GET_BIT(DMA_ISR,(Copy_u8ChannelNum*4+1)));

				/*clearing TC flag*/
				SET_BIT(DMA_IFCR,(Copy_u8ChannelNum*4+1));

		}
		else{
			/*Do Nothing*/
		}
		return Local_u8ErrorState;
}

u8 DMA_u8DMASetCallBack(u8 Copy_u8ChanneNumber,void(*pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	Global_pfArr[Copy_u8ChanneNumber]=pf;

	return Local_u8ErrorState;
}

void DMA1_Channel1_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,1);

	if(Global_pfArr[0]!=NULL)
	{
	Global_pfArr[0]();
	}
	else
	{
		/*Do nothing*/
	}
}
void DMA1_Channel2_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,5);

		if(Global_pfArr[1]!=NULL)
		{
		Global_pfArr[1]();
		}
		else
		{
			/*Do nothing*/
		}

}
void DMA1_Channel3_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,9);

		if(Global_pfArr[2]!=NULL)
		{
		Global_pfArr[2]();
		}
		else
		{
			/*Do nothing*/
		}
}
void DMA1_Channel4_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,13);

		if(Global_pfArr[3]!=NULL)
		{
		Global_pfArr[3]();
		}
		else
		{
			/*Do nothing*/
		}
}
void DMA1_Channel5_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,17);

		if(Global_pfArr[4]!=NULL)
		{
		Global_pfArr[4]();
		}
		else
		{
			/*Do nothing*/
		}
}
void DMA1_Channel6_IRQHandler (void)
{
	SET_BIT(DMA_IFCR,21);

		if(Global_pfArr[5]!=NULL)
		{
		Global_pfArr[5]();
		}
		else
		{
			/*Do nothing*/
		}
}
void DMA1_Channel7_IRQHandler (void){
	SET_BIT(DMA_IFCR,25);

		if(Global_pfArr[6]!=NULL)
		{
		Global_pfArr[6]();
		}
		else
		{
			/*Do nothing*/
		}
}


#endif /* DMA_PROGRAM_C_ */
