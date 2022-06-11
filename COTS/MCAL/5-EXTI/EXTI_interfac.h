/*
 * EXTI_interfac.h
 *
 *  Created on: Jul 26, 2021
 *      Author: ahmed
 */

#ifndef EXTI_INTERFAC_H_
#define EXTI_INTERFAC_H_

/*****************************Interfacing macros  *****************************/

#define EXTI_INTERRUPT_MASKED 					(u8)0
#define EXTI_INTERRUPT_NOT_MASKED				(u8)1
#define EXTI_RISING_EDGE						(u8)0
#define EXTI_FALLING_EDGE						(u8)1
#define EXTI_RISING_FALLING_EDGE				(u8)2

#define EXTI_LINE_0								(u8)0
#define EXTI_LINE_1								(u8)1
#define EXTI_LINE_2								(u8)2
#define EXTI_LINE_3								(u8)3
#define EXTI_LINE_4								(u8)4
#define EXTI_LINE_5_9							(u8)5
#define EXTI_LINE_10_15							(u8)6


/*****************************Functions Prototypes*****************************/

/*This function is used to set a specific EXTI status [Masked - Not masked]*/
u8 EXTI_u8SetInterruptStatus(u8 Copy_u8EXTINumber,u8 Copy_u8EXTIStatus);

/*This function is used to set a specific EXTI edge [Rising - Falling - Rising and Falling]*/
u8 EXTI_u8SetInterruptEdge(u8 Copy_u8EXTINumber,u8 Copy_u8EXTIEdge);

/*This function is used to clear a specific EXTI pending status*/
u8 EXTI_u8ClearInterruptPending(u8 Copy_u8EXTINumber);

/*This function is used to get a specific EXTI pending status*/
u8 EXTI_u8IsInterruptActive(u8 Copy_u8EXTINumber,u8*Copy_pu8EXTIStatus);

u8 EXTI_u8SetInterruptCallback(u8 Copy_u8EXTINumber,void(*Copy_pfCallback)(void));

#endif /* EXTI_INTERFAC_H_ */
