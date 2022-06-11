/*
 * RCC_private.h
 *
 *  Created on: Jul 8, 2021
 *      Author: ahmed hassan
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

//Enum for RCC_CR_REG_BITS
enum{
	RCC_CR_HSION,
	RCC_CR_HSIRDY,
	RCC_CR_HSITRIM = 3,
	RCC_CR_HSEON   = 16,
	RCC_CR_HSERDY,
	RCC_CR_HSEBYP,
	RCC_CR_CSSON,
	RCC_CR_PLLON   =24,
	RCC_CR_PLLRDY
};

//Macros for RCC_CFGR_REG_BITS
#define RCC_CFGR_SW0					0
#define RCC_CFGR_SW1					1
#define RCC_CFGR_SWS					2
#define RCC_CFGR_HPRE					4
#define RCC_CFGR_PPRE1					8
#define RCC_CFGR_PPRE2					11
#define RCC_CFGR_ADCPRE					14
#define RCC_CFGR_PLLSRC					16
#define RCC_CFGR_PLLXTPRE				17
#define RCC_CFGR_PLLMUL					18
#define RCC_CFGR_USBPRE					22
#define RCC_CFGR_MSO					24




void Private_voidEnableHSIClk 			(void);
void Private_voidEnableHSEBypassClk 	(void);
void Private_voidEnableHSECrystlClk 	(void);
void Private_voidEnablePLLClk 			(void);
u8   Private_u8PLLMul					(u8 Copy_u8PLLMultpValue, u8 Copy_u8InputClkValueMHZ);
u8	 Private_u8HSEDivider				(u8 Copy_u8PLLHSEDivider,u8 Copy_u8InputClkValueMHZ);



#endif /* RCC_PRIVATE_H_ */
