#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"
#include "STK_private.h"
#include "STK_config.h"
#include "STK_interface.h"


static void (*STK_pvoidfunc)(void)= NULL;
static u8 	STK_u8_Async_func_state;


void STK_voidInit(void){
#if 	(STK_u8CLKSRC == STK_u8CLKSRC_AHB_8)
		STK->CTRL = 0;

#elif	(STK_u8CLKSRC == STK_u8CLKSRC_PCLK)
		STK->CTRL = 0x00000004;
#else
		"wrong"
#endif

}


u8 STK_u8SetBusyWait					(u32 Copy_u32NumofTicks){

	if(Copy_u32NumofTicks > 0xFFFFFF){
		return STD_TYPES_NOK;
	}
	STK->LOAD = Copy_u32NumofTicks;
	SET_BIT(STK->CTRL,STK_u8_COUNTER);
	while(!GET_BIT(STK->CTRL,STK_u8_COUNTFLAG));
	CLR_BIT(STK->CTRL,STK_u8_COUNTER);
	STK->LOAD = 0;
	STK->VAL = 0;

	return STD_TYPES_OK;
}




void SysTick_Handler(void){

	if(STK_u8_Async_func_state == STK_u8_SetIntervalSingle_FLAG){
		/* Disable Interrupt */
				CLR_BIT(STK->CTRL,1);

				/* Stop Timer */
				CLR_BIT(STK->CTRL,0);
				STK->LOAD = 0;
				STK->VAL  = 0;

	}


	if(STK_pvoidfunc!=NULL){
	STK_pvoidfunc();
	}
}

u8 		STK_u8SetIntervalSingle			(u32 Copy_u32NumofTicks, void (*Copy_pfunSingleInterval)(void)){

	if(Copy_u32NumofTicks > 0xFFFFFF || Copy_pfunSingleInterval == NULL){
			return STD_TYPES_NOK;
		}

	STK_u8_Async_func_state = STK_u8_SetIntervalSingle_FLAG;

	STK->LOAD = Copy_u32NumofTicks;

	SET_BIT(STK->CTRL,STK_u8_COUNTER);

	STK_pvoidfunc = Copy_pfunSingleInterval;

	SET_BIT(STK->CTRL,STK_u8_EXCEPTION_REQ);

	return STD_TYPES_OK;
}

u8 		STK_u8SetIntervalPeriodic		(u32 Copy_u32NumofTicks,void (*Copy_pfunPeriodicInterval)(void)){

	if(Copy_u32NumofTicks > 0xFFFFFF || Copy_pfunPeriodicInterval == NULL){
				return STD_TYPES_NOK;
			}

	STK_u8_Async_func_state = STK_u8_SetIntervalPeriodic_FLAG;

	STK->LOAD = Copy_u32NumofTicks-1;

	SET_BIT(STK->CTRL,STK_u8_COUNTER);

	STK_pvoidfunc = Copy_pfunPeriodicInterval;

	SET_BIT(STK->CTRL,STK_u8_EXCEPTION_REQ);

	return STD_TYPES_OK;

}


void 	STK_voidStopTimer				(void){

	CLR_BIT(STK->CTRL,0);
	STK->LOAD = 0;
	STK->VAL  = 0;
}


u8 STK_u8GetElapsedTime					(u32 * Copy_pu32ElapsedTime){

	*Copy_pu32ElapsedTime = STK->LOAD - STK->VAL;

	return STD_TYPES_OK;
}

u8 STK_u8GetRemaningTime				 (u32 * Copy_pu32RemaningTime){

	*Copy_pu32RemaningTime = STK->VAL;

	return STD_TYPES_OK;
}


