/*
 * ADC_program.c
 *
 *  Created on: Aug 18, 2021
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "STM32f103xx.h"
#include "BIT_Math.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"


static ADC_RegDef_t * ADC_Astr[2]={ADC1,ADC2};
static u8 ADC_u8InterruptFlag=0;
//static u16 ADC_u16DataConverted[4];
typedef void (*ADCPointertoFunc_t)(void);
ADCPointertoFunc_t ADC_ArrID[2];


u8 ADC_u8Init			(ADC_InitConfig_t * Copy_PstrInitConfig){
	u8 Local_u8ErrorState=STD_TYPES_OK;

	/*Enalbe ADC*/
	SET_BIT(ADC_Astr[ADC_u8ADCID]->CR2,0);

	/*conntinous mode*/
	ADC_Astr[ADC_u8ADCID]->CR2 |= Copy_PstrInitConfig->Continous <<1;

	/*interrupts*/
	ADC_Astr[ADC_u8ADCID]->CR1 &= ~(1<<5 | 1<<7);
	ADC_Astr[ADC_u8ADCID]->CR1 |= Copy_PstrInitConfig->Interrupt;

	/*Data Alignment*/
	ADC_Astr[ADC_u8ADCID]->CR2 |= Copy_PstrInitConfig->DataAlignment <<11;

	switch(Copy_PstrInitConfig->ConvMode){
	case ADC_u8_SINGLE_CONV_MODE:{
		CLR_BIT(ADC_Astr[ADC_u8ADCID]->CR1,8);
		break;
	}

	case ADC_u8_SCAN_CONV_MODE:{
		/*enable scan mode*/
		SET_BIT(ADC_Astr[ADC_u8ADCID]->CR1,8);
		break;
	}
	}

	/*triggering type*/
	ADC_Astr[ADC_u8ADCID]->CR2 |= Copy_PstrInitConfig->TriggeringType;

	switch(Copy_PstrInitConfig->ChannelType){
	case ADC_u8_REGULAR_CHANNEL:{


		ADC_Astr[ADC_u8ADCID]->SQR[0] = 0;
		ADC_Astr[ADC_u8ADCID]->SQR[0] |= (Copy_PstrInitConfig->NumbersofConversions<<20);

		for(u8 i=0,j=2;i<Copy_PstrInitConfig->NumbersofConversions;i--){
			if(j!=0){
				ADC_Astr[ADC_u8ADCID]->SQR[j]=0;
			}
			if(i%6 == 0){
				j--;
			}
			ADC_Astr[ADC_u8ADCID]->SQR[j] |= *((Copy_PstrInitConfig->ChannelsSeq) + i) << 5*(i%6);
		}


		if(GET_BIT(ADC_Astr[ADC_u8ADCID]->CR2,20)){
			/*external trigger*/
			ADC_Astr[ADC_u8ADCID]->CR2 &= ~(0x7<<20);
			ADC_Astr[ADC_u8ADCID]->CR2 |= (Copy_PstrInitConfig->ExtTrigEvent <<20);
		}
		else{
			/*start conversion*/
			SET_BIT(ADC_Astr[ADC_u8ADCID]->CR2,0);
		}

		break;
	}
	case ADC_u8_INJECTED_CHANNEL:{


		ADC_Astr[ADC_u8ADCID]->JSQR = 0;
		ADC_Astr[ADC_u8ADCID]->JSQR |= (Copy_PstrInitConfig->NumbersofConversions<<20);
		u8 injected_seq_size =4-Copy_PstrInitConfig->NumbersofConversions;

		for(u8 i=0;i<Copy_PstrInitConfig->NumbersofConversions;i++){
		ADC_Astr[ADC_u8ADCID]->JSQR |= *((Copy_PstrInitConfig->ChannelsSeq) + i) << 5*(i+injected_seq_size);
		}

		if(GET_BIT(ADC_Astr[ADC_u8ADCID]->CR2,15)){
			/*external trigger*/
			ADC_Astr[ADC_u8ADCID]->CR2 &= ~(0x7<<15);
			ADC_Astr[ADC_u8ADCID]->CR2 |= (Copy_PstrInitConfig->ExtTrigEvent <<15);
		}

		else{
			/*start conversion*/
			SET_BIT(ADC_Astr[ADC_u8ADCID]->CR2,0);
		}
		break;

		}

	}


	return Local_u8ErrorState;
}


u8 ADC_u8ReadingRegularChannelPolling(u16* Copy_Pu8DataConverted){
	u8 Local_u8ErrorState=STD_TYPES_OK;

		while((ADC_Astr[ADC_u8ADCID]->SR & 1<<1) == 0);
		*Copy_Pu8DataConverted = ADC_Astr[ADC_u8ADCID]->DR;

	return Local_u8ErrorState;
}

u8 ADC_u8ReadingInjectedChannelPolling(u16* Copy_Pu8DataConverted){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8NumberofConv=(ADC_Astr[ADC_u8ADCID]->JSQR>>20);
	while((ADC_Astr[ADC_u8ADCID]->SR & 1<<2) == 0);
	for(int i=4-Local_u8NumberofConv;i<Local_u8NumberofConv;i++){
		*Copy_Pu8DataConverted = ADC_Astr[ADC_u8ADCID]->JDR[4-i-1];
	}

	return Local_u8ErrorState;

}

void ADC1_2_IRQHandler(void){
	/*EOC FLAG*/
	if(ADC_u8InterruptFlag == 1){
		ADC_u8InterruptFlag = 0;
		ADC_ArrID[0]();
	}
	else{
		//do nothing
	}
	/*JEOC FLAG*/
	if(ADC_u8InterruptFlag == 2){
		ADC_u8InterruptFlag = 0;
		ADC_ArrID[1]();
	}
	else{
		//do nothing
	}
}

//u8 ADC_u8ReadingRegularChannelInterrupt(void){
//	u8 Local_u8ErrorState=STD_TYPES_OK;
//	ADC_u8InterruptFlag = 1;
//
//	return Local_u8ErrorState;
//}
//
//u8 ADC_u8ReadingInjectedChannelInterrupt(void){
//	u8 Local_u8ErrorState=STD_TYPES_OK;
//	ADC_u8InterruptFlag =2 ;
//
//	return Local_u8ErrorState;
//}

u8 ADC_u8ExternalTriggerRegularSwConv(void){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	ADC_Astr[ADC_u8ADCID]->CR2 |=1<<22;
	return Local_u8ErrorState;
}

u8 ADC_u8ExternalTriggerInjectedSwConv(void){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	ADC_Astr[ADC_u8ADCID]->CR2 |=1<<21;
	return Local_u8ErrorState;
}


u8 ADC_u8ADCSetCallBack(u8 Copy_u8IntrIndex,void(*Copy_Pvoidtofunc)(void)){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	ADC_u8InterruptFlag = Copy_u8IntrIndex+1; 						/*    1->EOC   ,,   2->JEOC     */
	ADC_ArrID[Copy_u8IntrIndex]=Copy_Pvoidtofunc;

	return Local_u8ErrorState;
}
