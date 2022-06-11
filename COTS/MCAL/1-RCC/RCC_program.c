/*
 * RCC_program.c
 *
 *  Created on: Jul 8, 2021
 *      Author: ahmed hassan
 */

#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "STM32f103xx.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "RCC_interface.h"


void Private_voidEnableHSIClk (void){
	SET_BIT(RCC->CR,RCC_CR_HSION);
	while(GET_BIT(RCC->CR,RCC_CR_HSIRDY)==0);
}

void Private_voidEnableHSEBypassClk (void){
	SET_BIT(RCC->CR,RCC_CR_HSEBYP);
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	while(GET_BIT(RCC->CR,RCC_CR_HSERDY)==0);
}

void Private_voidEnableHSECrystlClk (void){
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	while(GET_BIT(RCC->CR,RCC_CR_HSERDY)==0);
}

void Private_voidEnablePLLClk (void){
	SET_BIT(RCC->CR,RCC_CR_PLLON);
	while(GET_BIT(RCC->CR,RCC_CR_PLLRDY)==0);
}

u8 Private_u8HSEDivider(u8 Copy_u8PLLHSEDivider,u8 Copy_u8InputClkValueMHZ){
	switch (Copy_u8PLLHSEDivider){
	case HSEDivider_ON:{
		SET_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE);
		Copy_u8InputClkValueMHZ/=2;
		break;
	}
	case HSEDivider_OFF: CLR_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE);break;
	}
	return Copy_u8InputClkValueMHZ;
}

u8   Private_u8PLLMul	(u8 Copy_u8PLLMultpValue, u8 Copy_u8InputClkValueMHZ){
	if(Copy_u8PLLMultpValue > RCC_PLL_INPUT_CLK_X16 || Copy_u8InputClkValueMHZ > 25){
		return STD_TYPES_NOK;
	}
	if((Copy_u8InputClkValueMHZ * (Copy_u8PLLMultpValue+2))>72){
		return STD_TYPES_NOK;
	}
	RCC->CFGR &= ~(RCC_PLL_INPUT_CLK_X16<<RCC_CFGR_PLLMUL);
	RCC->CFGR |= Copy_u8PLLMultpValue << RCC_CFGR_PLLMUL;
	return STD_TYPES_OK;
}

u8	 RCC_u8PLLConfig	(u8 Copy_u8PLLCLKType, u8 Copy_u8PLLHSEDivider, u8 Copy_u8PLLMultpValue, u8 Copy_u8InputClkValueMHZ){
	u8 Local_u8ErrorState;

	if(Copy_u8PLLMultpValue > 16){
			return STD_TYPES_NOK;
		}
	switch (Copy_u8PLLCLKType){

	case RCC_u8_PLL_HSI_CLK	: {
		Private_voidEnableHSIClk();
		Copy_u8InputClkValueMHZ/=2;
		CLR_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
		break;
	}
	case RCC_u8_PLL_HSECRYSTL_CLK	: {
		Private_voidEnableHSECrystlClk();
		SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
		Private_u8HSEDivider(Copy_u8PLLHSEDivider, Copy_u8InputClkValueMHZ);
		break;
	}
	case RCC_u8_PLL_HSEBYPASS_CLK	: {
		Private_voidEnableHSEBypassClk();
		SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
		Private_u8HSEDivider(Copy_u8PLLHSEDivider, Copy_u8InputClkValueMHZ);
		break;
	}
	default : return STD_TYPES_NOK;
	}

	Local_u8ErrorState = Private_u8PLLMul	(Copy_u8PLLMultpValue, Copy_u8InputClkValueMHZ);
	if(Local_u8ErrorState == STD_TYPES_NOK){
		return Local_u8ErrorState;
	}
	Private_voidEnablePLLClk();

	return STD_TYPES_OK;
}




u8 RCC_u8ChooseSysClk (u8 Copy_u8HSCLKType){
	if(Copy_u8HSCLKType > RCC_u8_PLL_HSECRYSTL_CLK){
		return STD_TYPES_NOK;
	}
	switch (Copy_u8HSCLKType){
	case RCC_u8_HSI_CLK			: {
		Private_voidEnableHSIClk();
		CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
		CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);
		break;
	}
	case RCC_u8_HSEBYPASS_CLK	: {
		Private_voidEnableHSEBypassClk();
		SET_BIT(RCC->CFGR,RCC_CFGR_SW0);
		CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);
		break;
	}
	case RCC_u8_HSECRYSTL_CLK	: {
		Private_voidEnableHSECrystlClk();
		SET_BIT(RCC->CFGR,RCC_CFGR_SW0);
		CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);
		break;
	}
	default :{
		CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
		SET_BIT(RCC->CFGR,RCC_CFGR_SW1);

	}

	}
	return STD_TYPES_OK;
}

u8 RCC_u8EnablePeripheralClk   (u8 Copy_u8BusId,u8 Copy_u8PeripheralId)
{
	if(Copy_u8PeripheralId<32)
	{
		switch (Copy_u8BusId)
		{
			case RCC_u8_AHB_BUS  : SET_BIT(RCC->AHBENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB1_BUS : SET_BIT(RCC->APB1ENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB2_BUS : SET_BIT(RCC->APB2ENR,Copy_u8PeripheralId);break;
			default				 : return STD_TYPES_NOK;
		}
	}
	else
	{
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}


u8 RCC_u8DisablePeripheralClk  (u8 Copy_u8BusId,u8 Copy_u8PeripheralId)
{

	if(Copy_u8PeripheralId<32)
	{
		switch (Copy_u8BusId)
		{
			case RCC_u8_AHB_BUS  : CLR_BIT(RCC->AHBENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB1_BUS : CLR_BIT(RCC->APB1ENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB2_BUS : CLR_BIT(RCC->APB2ENR,Copy_u8PeripheralId);break;
			default				 : return STD_TYPES_NOK;
		}
	}
	else
	{
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

u8 RCC_u8BusesClkPrescaler		(u8 Copy_u8BusId,u8 Copy_u8BusesClkPrescalerId){
	switch (Copy_u8BusId){
	case RCC_u8_AHB_BUS :{
		if(Copy_u8BusesClkPrescalerId > RCC_ABHBUS_CLK_DIVIDED_BY_512){
			return STD_TYPES_NOK;
		}
		RCC->CFGR &= ~(RCC_ABHBUS_CLK_DIVIDED_BY_512 << RCC_CFGR_HPRE);
		RCC->CFGR |= Copy_u8BusesClkPrescalerId<<RCC_CFGR_HPRE;
		break;
	}
	case RCC_u8_APB2_BUS :{
		if(Copy_u8BusesClkPrescalerId > RCC_ABPBUS_CLK_DIVIDED_BY_16){
			return STD_TYPES_NOK;
		}
		RCC->CFGR &= ~(RCC_ABPBUS_CLK_DIVIDED_BY_16 << RCC_CFGR_PPRE2);
		RCC->CFGR |= Copy_u8BusesClkPrescalerId<<RCC_CFGR_PPRE2;
		break;
	}
	case RCC_u8_APB1_BUS :{
			if(Copy_u8BusesClkPrescalerId > RCC_ABPBUS_CLK_DIVIDED_BY_16){
				return STD_TYPES_NOK;
			}
			RCC->CFGR &= ~(RCC_ABPBUS_CLK_DIVIDED_BY_16 << RCC_CFGR_PPRE1);
			RCC->CFGR |= Copy_u8BusesClkPrescalerId<<RCC_CFGR_PPRE1;
			break;
		}
	default 			: return STD_TYPES_NOK;

	}
	return STD_TYPES_OK;
}

u8 RCC_u8MCOClk						(u8 Copy_u8MCOClkType){
	if(Copy_u8MCOClkType > RCC_MCO_PLLCLK_DIVIDED_BY_2){
		return STD_TYPES_NOK;
	}
	RCC->CFGR &= ~(RCC_MCO_PLLCLK_DIVIDED_BY_2 << RCC_CFGR_MSO);
	RCC->CFGR |= Copy_u8MCOClkType<<RCC_CFGR_MSO;

	return STD_TYPES_OK;
}

u8 RCC_USBPrescaler					(u8 Copy_u8USBPrescalerId){
	if(Copy_u8USBPrescalerId > RCC_USB_PLLCLK_NOT_DIVIDED){
			return STD_TYPES_NOK;
		}
	RCC->CFGR &= ~(RCC_USB_PLLCLK_NOT_DIVIDED << RCC_CFGR_USBPRE);
	RCC->CFGR |= Copy_u8USBPrescalerId<<RCC_CFGR_USBPRE;

	return STD_TYPES_OK;
}

u8 RCC_ADCPrescaler					(u8 Copy_u8ADCPrescalerId){
	if(Copy_u8ADCPrescalerId > RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_8){
				return STD_TYPES_NOK;
			}
		RCC->CFGR &= ~(RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_8 << RCC_CFGR_ADCPRE);
		RCC->CFGR |= Copy_u8ADCPrescalerId<<RCC_CFGR_ADCPRE;

		return STD_TYPES_OK;
}

u8 RCC_ClockSecuritySystem			(u8 Copy_u8CssStatus){
	if(GET_BIT(RCC->CR,RCC_CR_HSERDY)==0){
		return STD_TYPES_OK;
	}
	switch (Copy_u8CssStatus){
	case RCC_CSS_ENABLE  : SET_BIT(RCC->CR,RCC_CR_CSSON);break;
	case RCC_CSS_DISABLE : CLR_BIT(RCC->CR,RCC_CR_CSSON);break;
	default 			 : return STD_TYPES_NOK;

	}
	return STD_TYPES_OK;

}

u8 RCC_u8HSITrimingCalibration		(s16 Copy_u8CalibrationValueKHZ){
	if(Copy_u8CalibrationValueKHZ < -640 && Copy_u8CalibrationValueKHZ >600){
		return STD_TYPES_NOK;
	}

	if(Copy_u8CalibrationValueKHZ < 0){
		Copy_u8CalibrationValueKHZ = (-1 * Copy_u8CalibrationValueKHZ / 40);
	}
	else {
		Copy_u8CalibrationValueKHZ /= 40;
	}
	RCC->CR &= ~(0x1F << RCC_CR_HSITRIM);
	RCC->CR |= Copy_u8CalibrationValueKHZ << RCC_CR_HSITRIM;

	return STD_TYPES_OK;
}

u8 RCC_u8InitSysClk                 (void)
{

	/* Enable The Clk to be selected */
	/* Select Clk Source : 1-HSI 2-HSE 3-PLL  */
#if (RCC_u8_CLK_SYS == RCC_u8_HSI_CLK)
	Private_voidEnableHSIClk();
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);

#elif (RCC_u8_CLK_SYS == RCC_u8_HSECRYSTL_CLK)
	Private_voidEnableHSECrystlClk();
	SET_BIT(RCC->CFGR,RCC_CFGR_SW0);
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);

#elif (RCC_u8_CLK_SYS == RCC_u8_HSEBYPASS_CLK)
	Private_voidEnableHSEBypassClk();
	SET_BIT(RCC->CFGR,RCC_CFGR_SW0);
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);

#elif (RCC_u8_CLK_SYS == RCC_u8_PLL_HSI_CLK)
	Private_voidEnableHSIClk();
	CLR_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
	Private_voidEnablePLLClk();
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
	SET_BIT(RCC->CFGR,RCC_CFGR_SW1);
	Private_u8PLLMul(RCC_u8_PLL_MUL_FACTOR, 8);

#elif (RCC_u8_CLK_SYS == RCC_u8_PLL_HSECRYSTL_CLK)
	Private_voidEnableHSECrystlClk();
	SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
	Private_u8PLLMul(RCC_u8_PLL_MUL_FACTOR, RCC_u8_PLL_INPUT_CLK);
	Private_voidEnablePLLClk();
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
	SET_BIT(RCC->CFGR,RCC_CFGR_SW1);


#elif (RCC_u8_CLK_SYS == RCC_u8_PLL_HSEBYPASS_CLK)
	Private_voidEnableHSEBypassClk();
	SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
	Private_voidEnablePLLClk();
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
	SET_BIT(RCC->CFGR,RCC_CFGR_SW1);
	Private_u8PLLMul(RCC_u8_PLL_MUL_FACTOR, RCC_u8_PLL_INPUT_CLK);

#else
	#error"Wrong Choice"
#endif
	return STD_TYPES_OK;
}
