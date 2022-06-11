/*
 * NVIC_program.c
 *
 *  Created on: Jul 25, 2021
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
#include "NVIC_interface.h"



/*This function used to enable interrupt*/
u8 NVIC_u8EnableInterrupt(u8 Copy_u8InterruptNumber){
	if(Copy_u8InterruptNumber >= 67){
		return STD_TYPES_NOK;
	}
	else if(Copy_u8InterruptNumber < 32){
		SET_BIT(NVIC->ISER[0],Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber < 64){
		SET_BIT(NVIC->ISER[1],(Copy_u8InterruptNumber-32));
	}
	else if(Copy_u8InterruptNumber < 67){
		SET_BIT(NVIC->ISER[2],(Copy_u8InterruptNumber-64));
		}
	return STD_TYPES_OK;
}


/*This function used to disable interrupt*/
u8 NVIC_u8DisableInterrupt(u8 Copy_u8InterruptNumber){
	if(Copy_u8InterruptNumber >= 67){
			return STD_TYPES_NOK;
		}
		else if(Copy_u8InterruptNumber < 32){
			SET_BIT(NVIC->ICER[0],Copy_u8InterruptNumber);
		}
		else if(Copy_u8InterruptNumber < 64){
			SET_BIT(NVIC->ICER[1],(Copy_u8InterruptNumber-32));
		}
		else if(Copy_u8InterruptNumber < 67){
			SET_BIT(NVIC->ICER[2],(Copy_u8InterruptNumber-64));
			}
		return STD_TYPES_OK;
}

/*This function used to set pending interrupts*/
u8 NVIC_u8SetInterruptPending(u8 Copy_u8InterruptNumber){
	if(Copy_u8InterruptNumber >= 67){
			return STD_TYPES_NOK;
		}
		else if(Copy_u8InterruptNumber < 32){
			SET_BIT(NVIC->ISPR[0],Copy_u8InterruptNumber);
		}
		else if(Copy_u8InterruptNumber < 64){
			SET_BIT(NVIC->ISPR[1],(Copy_u8InterruptNumber-32));
		}
		else if(Copy_u8InterruptNumber < 67){
			SET_BIT(NVIC->ISPR[2],(Copy_u8InterruptNumber-64));
			}
		return STD_TYPES_OK;
}

/*This function used to clear pending interrupts*/
u8 NVIC_u8ClearInterruptPending(u8 Copy_u8InterruptNumber){
	if(Copy_u8InterruptNumber >= 67){
			return STD_TYPES_NOK;
		}
		else if(Copy_u8InterruptNumber < 32){
			SET_BIT(NVIC->ICPR[0],Copy_u8InterruptNumber);
		}
		else if(Copy_u8InterruptNumber < 64){
			SET_BIT(NVIC->ICPR[1],(Copy_u8InterruptNumber-32));
		}
		else if(Copy_u8InterruptNumber < 67){
			SET_BIT(NVIC->ICPR[2],(Copy_u8InterruptNumber-64));
			}
		return STD_TYPES_OK;
}

/*This function used to get current active interrupt*/
u8 NVIC_u8GetCurrentActive(u8 Copy_u8InterruptNumber,u8 *Copy_pu32CurrentActive){
	if(Copy_pu32CurrentActive == NULL && Copy_u8InterruptNumber >= 67){
			return STD_TYPES_NOK;
		}
		else if(Copy_u8InterruptNumber < 32){
			*Copy_pu32CurrentActive = GET_BIT(NVIC->IABR[0],Copy_u8InterruptNumber);
		}
		else if(Copy_u8InterruptNumber < 64){
			*Copy_pu32CurrentActive = GET_BIT(NVIC->IABR[1],Copy_u8InterruptNumber);

		}
		else if(Copy_u8InterruptNumber < 67){
			*Copy_pu32CurrentActive = GET_BIT(NVIC->IABR[2],Copy_u8InterruptNumber);

			}
		return STD_TYPES_OK;
}


u8 NVIC_u8SetInterruptPriority(u8 Copy_u8InterruptNumber,u8 Copy_u8InterruptPriorityLVL,u8 Copy_u8SubPriority){
	if(Copy_u8InterruptNumber >=67 && Copy_u8InterruptPriorityLVL >=16){
		return STD_TYPES_NOK;
	}
	else{
		SCB_AIRCR = (0x5FA <<16) | (Copy_u8SubPriority<<8);
		NVIC->IPR[Copy_u8InterruptNumber/4] &= ~ (0b1111 << ((Copy_u8InterruptNumber%4)*8+4));
		NVIC->IPR[Copy_u8InterruptNumber/4] |=   (Copy_u8InterruptPriorityLVL << ((Copy_u8InterruptNumber%4)*8+4));
		}

	return STD_TYPES_OK;
}

