/************************************************************/
/**************** Name 	  : Ahmed Hassan ********************/
/**************** Date 	  : 14/7/2021    ********************/
/**************** Version : 1.0          ********************/
/**************** SWC	  : STK			 ********************/
/************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTEFACE_H

/*STK Initialization*/
void STK_voidInit(void);

/*Synch function*/
u8 STK_u8SetBusyWait					(u32 Copy_u32NumofTicks);


/*Async functions*/
u8 		STK_u8SetIntervalSingle			(u32 Copy_u32NumofTicks, void (*Copy_pfunSingleInterval)(void));

u8 		STK_u8SetIntervalPeriodic		(u32 Copy_u32NumofTicks,void (*Copy_pfunPeriodicInterval)(void));

void 	STK_voidStopTimer				(void);

u8 STK_u8GetElapsedTime					(u32 * Copy_pu32ElapsedTime);

u8 STK_u8GetRemaningTime				(u32 * Copy_pu32RemaningTime);

#endif
