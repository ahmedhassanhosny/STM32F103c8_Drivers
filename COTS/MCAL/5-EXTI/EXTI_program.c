/*
 * EXTI_program.c
 *
 *  Created on: Jul 26, 2021
 *      Author: ahmed
 */


#include "STD_TYPES.h"
#include "STM32f103xx.h"
#include "BIT_Math.h"
#include "EXTI_pirvate.h"
#include "EXTI_config.h"
#include "EXTI_interfac.h"



typedef void(*fptr)(void);

static fptr Global_pfArray[7]={NULL,NULL,NULL,NULL,NULL,NULL,NULL};

/*This function is used to set a specific EXTI status [Masked - Not masked]*/
u8 EXTI_u8SetInterruptStatus(u8 Copy_u8EXTINumber,u8 Copy_u8EXTIStatus){
	u8 Local_u8ErrorState=STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15 && Copy_u8EXTIStatus <=1){
		EXTI->IMR &= ~(1 << Copy_u8EXTINumber);
		EXTI->IMR |= (Copy_u8EXTIStatus << Copy_u8EXTINumber);
		Local_u8ErrorState = STD_TYPES_OK;
	}

	return Local_u8ErrorState;
}

/*This function is used to set a specific EXTI edge [Rising - Falling - Rising and Falling]*/
u8 EXTI_u8SetInterruptEdge(u8 Copy_u8EXTINumber,u8 Copy_u8EXTIEdge){
	u8 Local_u8ErrorState=STD_TYPES_NOK;

		if(Copy_u8EXTINumber <= 15 && Copy_u8EXTIEdge <=2){
			switch(Copy_u8EXTIEdge){
			case EXTI_RISING_EDGE:{
				SET_BIT(EXTI->RTSR,Copy_u8EXTINumber);
				CLR_BIT(EXTI->FTSR,Copy_u8EXTINumber);
				break;
			}
			case EXTI_FALLING_EDGE:{
				SET_BIT(EXTI->FTSR,Copy_u8EXTINumber);
				CLR_BIT(EXTI->RTSR,Copy_u8EXTINumber);
				break;
			}
			case EXTI_RISING_FALLING_EDGE:{
				SET_BIT(EXTI->RTSR,Copy_u8EXTINumber);
				SET_BIT(EXTI->FTSR,Copy_u8EXTINumber);
				break;
			}
			}
			Local_u8ErrorState = STD_TYPES_OK;
		}

		return Local_u8ErrorState;
}

/*This function is used to clear a specific EXTI pending status*/
u8 EXTI_u8ClearInterruptPending(u8 Copy_u8EXTINumber){
	u8 Local_u8ErrorState=STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15){
		SET_BIT(EXTI->PR,Copy_u8EXTINumber);
		Local_u8ErrorState = STD_TYPES_OK;
	}

	return Local_u8ErrorState;
}

/*This function is used to get a specific EXTI pending status*/
u8 EXTI_u8IsInterruptActive(u8 Copy_u8EXTINumber,u8*Copy_pu8EXTIStatus){
	u8 Local_u8ErrorState=STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15 && Copy_pu8EXTIStatus != NULL){
		*Copy_pu8EXTIStatus = GET_BIT(EXTI->PR,Copy_u8EXTINumber);
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}


u8 EXTI_u8SetInterruptCallback(u8 Copy_u8EXTINumber,void (*Copy_pfCallback)(void)){

	u8 Local_u8ErrorState=STD_TYPES_OK;
	if(Copy_u8EXTINumber>4 && Copy_u8EXTINumber<10){
		Copy_u8EXTINumber =5;
	}
	else if(Copy_u8EXTINumber>=10 && Copy_u8EXTINumber<16){
		Copy_u8EXTINumber =6;
	}

	Global_pfArray[Copy_u8EXTINumber]=Copy_pfCallback;
	return Local_u8ErrorState;
}



void EXTI0_IRQHandler (void){

	SET_BIT(EXTI->PR,0);

	if(Global_pfArray[EXTI_LINE_0] != NULL){
		Global_pfArray[EXTI_LINE_0]();
	}

}
void EXTI1_IRQHandler (void){

	SET_BIT(EXTI->PR,1);

	if(Global_pfArray[EXTI_LINE_1] != NULL){
		Global_pfArray[EXTI_LINE_1]();
	}

}
void EXTI2_IRQHandler (void){

	SET_BIT(EXTI->PR,2);

	if(Global_pfArray[EXTI_LINE_2] != NULL){
		Global_pfArray[EXTI_LINE_2]();
	}

}
void EXTI3_IRQHandler (void){

	SET_BIT(EXTI->PR,3);

	if(Global_pfArray[EXTI_LINE_3] != NULL){
		Global_pfArray[EXTI_LINE_3]();
	}

}

void EXTI4_IRQHandler (void){

	SET_BIT(EXTI->PR,4);

	if(Global_pfArray[EXTI_LINE_4] != NULL){
		Global_pfArray[EXTI_LINE_4]();
	}

}

void EXTI9_5_IRQHandler (void){

	EXTI->PR |= 0b11111<<5;
	if(Global_pfArray[EXTI_LINE_5_9] != NULL){
		Global_pfArray[EXTI_LINE_5_9]();
	}

}

void EXTI15_10_IRQHandler (void){
	EXTI->PR |= 0b111111<<10;
	if(Global_pfArray[EXTI_LINE_10_15] != NULL){
		Global_pfArray[EXTI_LINE_10_15]();
	}
}
