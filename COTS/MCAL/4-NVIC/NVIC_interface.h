/*
 * NVIC_interface.h
 *
 *  Created on: Jul 25, 2021
 *      Author: ahmed
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_




/*This function used to enable interrupt*/
u8 NVIC_u8EnableInterrupt(u8 Copy_u8InterruptNumber);

/*This function used to disable interrupt*/
u8 NVIC_u8DisableInterrupt(u8 Copy_u8InterruptNumber);

/*This function used to set pending interrupts*/
u8 NVIC_u8SetInterruptPending(u8 Copy_u8InterruptNumber);

/*This function used to clear pending interrupts*/
u8 NVIC_u8ClearInterruptPending(u8 Copy_u8InterruptNumber);

/*This function used to get current active interrupt*/
u8 NVIC_u8GetCurrentActive(u8 Copy_u8InterruptNumber,u8 *Copy_pu32CurrentActive);

/*This function used to set priority*/
u8 NVIC_u8SetInterruptPriority(u8 Copy_u8InterruptNumber,u8 Copy_u8InterruptPriorityLVL,u8 Copy_u8SubPriority);

#endif /* NVIC_INTERFACE_H_ */
