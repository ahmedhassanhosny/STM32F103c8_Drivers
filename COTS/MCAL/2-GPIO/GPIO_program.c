/*
 * GPIO_program.c
 *
 *  Created on: Jul 12, 2021
 *      Author: ahmed
 */

//Lib Layer
#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"

//MCAL
#include "GPIO_config.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"

static GPIO_RegDef_t * GPIO_Astr[3] = {GPIOA,GPIOB,GPIOC};

u8 GPIO_u8PinInit	(const GPIO_PinConfig_t * Copy_PstrPinConfig){
	/*Check Input Range*/
	if(Copy_PstrPinConfig == NULL || Copy_PstrPinConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPinConfig->PinId >	GPIO_u8_PIN15){
		return STD_TYPES_NOK;
	}

	if(Copy_PstrPinConfig->PinMode == GPIO_u8_MODE_INPUT_PULLUP ){

		/*SET ODR Register to set PULLUP In Input Mode*/
		SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
	}

	else if(Copy_PstrPinConfig->PinMode == GPIO_u8_MODE_INPUT_PULLDOWN){
		/*CLR ODR Register to set PULLDOWN In Input Mode*/
		CLR_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
	}
	else if(Copy_PstrPinConfig->PinMode > GPIO_u8_MODE_OUTPUT_AF_OD_50MHZ){
		return STD_TYPES_NOK;
	}

	if(Copy_PstrPinConfig -> PinId < GPIO_u8_PIN8){

		GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRL &= ~(0xF << (4*Copy_PstrPinConfig->PinId));
		if(Copy_PstrPinConfig->PinMode == GPIO_u8_MODE_INPUT_PULLUP){
			GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRL |= (GPIO_u8_MODE_INPUT_PULLDOWN << (4*Copy_PstrPinConfig->PinId));
		}
		else{
			/*Set Mode*/
			GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRL |= (Copy_PstrPinConfig->PinMode << (4*Copy_PstrPinConfig->PinId));
		}
	}
	else if(Copy_PstrPinConfig -> PinId >= GPIO_u8_PIN8){
		/*CLR Mode Bits*/
		GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRH &= ~(0xF << (4*Copy_PstrPinConfig->PinId - 32));

		if(Copy_PstrPinConfig->PinMode == GPIO_u8_MODE_INPUT_PULLUP){
			GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRH |= (GPIO_u8_MODE_INPUT_PULLDOWN << (4*Copy_PstrPinConfig->PinId - 32));
		}
		else{
			/*Set Mode*/
			GPIO_Astr[Copy_PstrPinConfig -> PortId]->CRH |= (Copy_PstrPinConfig->PinMode << (4*Copy_PstrPinConfig->PinId - 32));
		}
	}

	return STD_TYPES_OK;
}

u8 GPIO_u8SetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig, u8 Copy_u8PinValue){

	if(Copy_PstrPinConfig == NULL || Copy_PstrPinConfig->PortId > GPIO_u8_GPIOC){
			return STD_TYPES_NOK;
	}

	switch (Copy_u8PinValue){
	case GPIO_u8_LOW:{
		CLR_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
		break;
	}
	case GPIO_u8_HIGH:{
		SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
		break;
		}
	default : return STD_TYPES_NOK;
	}

	return STD_TYPES_OK;
}

u8 GPIO_u8GetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig, u8 * Copy_Pu8ReturnedPinValue ){
	if(Copy_PstrPinConfig == NULL || Copy_Pu8ReturnedPinValue == NULL || Copy_PstrPinConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPinConfig->PinId >	GPIO_u8_PIN15){
				return STD_TYPES_NOK;
		}

	*Copy_Pu8ReturnedPinValue = GET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->IDR,Copy_PstrPinConfig->PinId);

	return STD_TYPES_OK;
}

u8 GPIO_u8TogPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig){
	if(Copy_PstrPinConfig == NULL || Copy_PstrPinConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPinConfig->PinId >	GPIO_u8_PIN15){
					return STD_TYPES_NOK;
			}
	TOG_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);

	return STD_TYPES_OK;
}


u8 GPIO_u8SetPinValueAtomic (const GPIO_PinConfig_t * Copy_PstrPinConfig,u8 Copy_u8PinValue){
	if(Copy_PstrPinConfig == NULL || Copy_PstrPinConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPinConfig->PinId >	GPIO_u8_PIN15){
						return STD_TYPES_NOK;
				}
	switch (Copy_u8PinValue){
	case GPIO_u8_LOW:{
		SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->BRR, (Copy_PstrPinConfig->PinId));
		break;
	}
	case GPIO_u8_HIGH:{
		SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->BSRR, Copy_PstrPinConfig->PinId);
		break;
	}
	default :{
		return STD_TYPES_NOK;
	}
}
	return STD_TYPES_OK;
}


u32 GPIO_u8PinsMapping(u8 Copy_u8PinsId){
	u32 Local_u32PinsMapped=0;
	for(u8 i=0;i<8;i++){
		Local_u32PinsMapped |= ((Copy_u8PinsId >>i)%2)<<(i*4);
	}
	return Local_u32PinsMapped;
}

u8 GPIO_u8PortInit			(const GPIO_PortConfig_t * Copy_PstrPortConfig){

	if(Copy_PstrPortConfig == NULL || Copy_PstrPortConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPortConfig->PinsId >	0xFFFF){
			return STD_TYPES_NOK;
		}

		if(Copy_PstrPortConfig->PortMode == GPIO_u8_MODE_INPUT_PULLUP ){

			/*SET ODR Register to set PULLUP In Input Mode*/
			GPIO_Astr[Copy_PstrPortConfig->PortId]->ODR &= 0x00000000;
			GPIO_Astr[Copy_PstrPortConfig->PortId]->ODR |= Copy_PstrPortConfig->PinsId;
		}

		else if(Copy_PstrPortConfig->PortMode == GPIO_u8_MODE_INPUT_PULLDOWN){
			/*CLR ODR Register to set PULLDOWN In Input Mode*/
			GPIO_Astr[Copy_PstrPortConfig->PortId]->ODR |= 0xFFFFFFFF;
			GPIO_Astr[Copy_PstrPortConfig->PortId]->ODR &= ~(Copy_PstrPortConfig->PinsId);
		}
		else if(Copy_PstrPortConfig->PortMode > GPIO_u8_MODE_OUTPUT_AF_OD_50MHZ){
			return STD_TYPES_NOK;
		}
		/*Don't Forget Pull Up and Pull Down*/

		GPIO_Astr[Copy_PstrPortConfig->PortId]->CRL &=0x00000000;
		GPIO_Astr[Copy_PstrPortConfig->PortId]->CRH &=0x00000000;

		u32	Local_u32PinsMappedtoCRL = GPIO_u8PinsMapping(Copy_PstrPortConfig->PinsId);
		u32	Local_u32PinsMappedtoCRH = GPIO_u8PinsMapping(Copy_PstrPortConfig->PinsId>>8);

		GPIO_Astr[Copy_PstrPortConfig->PortId]->CRL |= (Local_u32PinsMappedtoCRL*Copy_PstrPortConfig->PortMode);
		GPIO_Astr[Copy_PstrPortConfig->PortId]->CRH |= (Local_u32PinsMappedtoCRH*Copy_PstrPortConfig->PortMode);



	return STD_TYPES_OK;
}

u8 GPIO_u8SetPortValueAtomic	(const GPIO_PortConfig_t * Copy_PstrPortConfig){

	if(Copy_PstrPortConfig == NULL || Copy_PstrPortConfig->PortId > GPIO_u8_GPIOC || Copy_PstrPortConfig->PinsId >	0xFFFF){
				return STD_TYPES_NOK;
			}

	GPIO_Astr[Copy_PstrPortConfig->PortId]->BRR &=0x00000000;
	GPIO_Astr[Copy_PstrPortConfig->PortId]->BRR |= ~Copy_PstrPortConfig->PinsId;

	GPIO_Astr[Copy_PstrPortConfig->PortId]->BSRR &=0x00000000;
	GPIO_Astr[Copy_PstrPortConfig->PortId]->BSRR |= Copy_PstrPortConfig->PinsId;

	return STD_TYPES_OK;
}

