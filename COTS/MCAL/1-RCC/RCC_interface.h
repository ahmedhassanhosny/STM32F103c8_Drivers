/*
 * RCC_interface.h
 *
 *  Created on: Jul 8, 2021
 *      Author: ahmed hassan
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

//Macros for High Speed Clock Source and for PLL Type
#define RCC_u8_HSI_CLK					0
#define RCC_u8_HSEBYPASS_CLK			1
#define RCC_u8_HSECRYSTL_CLK			2
#define RCC_u8_PLL_HSI_CLK				3
#define RCC_u8_PLL_HSEBYPASS_CLK		4
#define RCC_u8_PLL_HSECRYSTL_CLK		5

//Macros for PLLMultiplication factor

#define RCC_PLL_INPUT_CLK_X2            0
#define RCC_PLL_INPUT_CLK_X3            1
#define RCC_PLL_INPUT_CLK_X4            2
#define RCC_PLL_INPUT_CLK_X5            3
#define RCC_PLL_INPUT_CLK_X6            4
#define RCC_PLL_INPUT_CLK_X7            5
#define RCC_PLL_INPUT_CLK_X8            6
#define RCC_PLL_INPUT_CLK_X9            7
#define RCC_PLL_INPUT_CLK_X10           8
#define RCC_PLL_INPUT_CLK_X11           9
#define RCC_PLL_INPUT_CLK_X12           10
#define RCC_PLL_INPUT_CLK_X13           11
#define RCC_PLL_INPUT_CLK_X14           12
#define RCC_PLL_INPUT_CLK_X15           13
#define RCC_PLL_INPUT_CLK_X16           15


//Macros for Copy_u8_BusId
#define RCC_u8_AHB_BUS                  1
#define RCC_u8_APB1_BUS                 2
#define RCC_u8_APB2_BUS                 3

//Macros for Copy_u8_PeripheralId
//AHB Bus Peripherals
#define RCC_AHBENR_SDIOEN				10
#define RCC_AHBENR_FSMCEN		 		8
#define RCC_AHBENR_CRCEN				6
#define RCC_AHBENR_FLITFEN				4
#define RCC_AHBENR_SRAMEN				2
#define RCC_AHBENR_DMA2EN				1
#define RCC_AHBENR_DMA1EN				0

//APB2 Bus Peripherals
#define RCC_APB2ENR_TIM11EN					 		21
#define RCC_APB2ENR_TIM10EN					 		20
#define RCC_APB2ENR_TIM9EN					 		19
#define RCC_APB2ENR_ADC3EN							15
#define RCC_APB2ENR_USART1EN				 		14
#define RCC_APB2ENR_TIM8EN					 		13
#define RCC_APB2ENR_SPI1EN					 		12
#define RCC_APB2ENR_TIM1EN					 		11
#define RCC_APB2ENR_ADC2EN					 		10
#define RCC_APB2ENR_ADC1EN							9
#define RCC_APB2ENR_IOPGEN					 		8
#define RCC_APB2ENR_IOPFEN					 		7
#define RCC_APB2ENR_IOPEEN					 		6
#define RCC_APB2ENR_IOPDEN					 		5
#define RCC_APB2ENR_IOPCEN					 		4
#define RCC_APB2ENR_IOPBEN					 		3
#define RCC_APB2ENR_IOPAEN					 		2
#define RCC_APB2ENR_AFIOEN					 		0

//APB1 Bus Peripherals
#define RCC_APB1ENR_DACEN						 	29
#define RCC_APB1ENR_PWREN					 		28
#define RCC_APB1ENR_BKPEN					 		27
#define RCC_APB1ENR_CANEN					 		25
#define RCC_APB1ENR_USBEN					 		23
#define RCC_APB1ENR_I2C2EN					 		22
#define RCC_APB1ENR_I2C1EN					 		21
#define RCC_APB1ENR_UART5EN					 		20
#define RCC_APB1ENR_UART4EN					 		19
#define RCC_APB1ENR_USART3EN				 		18
#define RCC_APB1ENR_USART2EN				 		17
#define RCC_APB1ENR_SPI3EN					 		15
#define RCC_APB1ENR_SPI2EN					 		14
#define RCC_APB1ENR_WWDGEN					 		11
#define RCC_APB1ENR_TIM14EN					 		8
#define RCC_APB1ENR_TIM13EN					 		7
#define RCC_APB1ENR_TIM12EN					 		6
#define RCC_APB1ENR_TIM7EN					 		5
#define RCC_APB1ENR_TIM6EN					 		4
#define RCC_APB1ENR_TIM5EN					 		3
#define RCC_APB1ENR_TIM4EN					 		2
#define RCC_APB1ENR_TIM3EN					 		1
#define RCC_APB1ENR_TIM2EN					 		0

//Enum for ABH Bus Clk Prescaler
enum{
	RCC_ABHBUS_CLK_NODIVISOIN,
	RCC_ABHBUS_CLK_DIVIDED_BY_2=8,
	RCC_ABHBUS_CLK_DIVIDED_BY_4,
	RCC_ABHBUS_CLK_DIVIDED_BY_8,
	RCC_ABHBUS_CLK_DIVIDED_BY_16,
	RCC_ABHBUS_CLK_DIVIDED_BY_64,
	RCC_ABHBUS_CLK_DIVIDED_BY_128,
	RCC_ABHBUS_CLK_DIVIDED_BY_256,
	RCC_ABHBUS_CLK_DIVIDED_BY_512
};

//Enum for ABP1 or ABP2 Bus Clk Prescaler
enum{
	RCC_ABPBUS_CLK_NODIVISOIN,
	RCC_ABPBUS_CLK_DIVIDED_BY_2=4,
	RCC_ABPBUS_CLK_DIVIDED_BY_4,
	RCC_ABPBUS_CLK_DIVIDED_BY_8,
	RCC_ABPBUS_CLK_DIVIDED_BY_16
};

//Values of Copy_u8PLLHSEDivider
#define HSEDivider_ON							1
#define HSEDivider_OFF							0

//Enum for MCO CLK Type
enum{
	RCC_MCO_NO_CLK,
	RCC_MCO_SYSCLK = 4,
	RCC_MCO_HSICLK,
	RCC_MCO_HSECLK,
	RCC_MCO_PLLCLK_DIVIDED_BY_2
};

//Enum for USB Prescaler
enum{
	RCC_USB_PLLCLK_DIVIDED_BY_1_AND_HALF,
	RCC_USB_PLLCLK_NOT_DIVIDED
};

//Enum for ADC Prescaler
enum{
	RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_2,
	RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_4,
	RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_6,
	RCC_ADC_ABP2BUS_CLK_DIVIDED_BY_8
};

//Macros for Clock Security System Status
#define RCC_CSS_ENABLE							1
#define RCC_CSS_DISABLE							0

//Enum for Trimming Calibration Value
enum{
	RCC_HSI_TRIM_640KHZ,
	RCC_HSI_TRIM_600KHZ,
	RCC_HSI_TRIM_560KHZ,
	RCC_HSI_TRIM_520KHZ,
	RCC_HSI_TRIM_480KHZ,
	RCC_HSI_TRIM_440KHZ,
	RCC_HSI_TRIM_400KHZ,
	RCC_HSI_TRIM_360KHZ,
	RCC_HSI_TRIM_320KHZ,
	RCC_HSI_TRIM_280KHZ,
	RCC_HSI_TRIM_240KHZ,
	RCC_HSI_TRIM_200KHZ,
	RCC_HSI_TRIM_160KHZ,
	RCC_HSI_TRIM_120KHZ,
	RCC_HSI_TRIM_80KHZ,
	RCC_HSI_TRIM_40KHZ,
};

u8 RCC_u8ChooseSysClk				(u8 Copy_u8HSCLKType);
u8 RCC_u8PLLConfig					(u8 Copy_u8PLLCLKType, u8 Copy_u8PLLHSEDivider, u8 Copy_u8PLLMultpValue, u8 Copy_u8InputClkValueMHZ);
u8 RCC_u8EnablePeripheralClk   		(u8 Copy_u8BusId,u8 Copy_u8PeripheralId);
u8 RCC_u8DisablePeripheralClk  		(u8 Copy_u8BusId,u8 Copy_u8PeripheralId);
u8 RCC_u8BusesClkPrescaler			(u8 Copy_u8BusId,u8 Copy_u8BusesClkPrescalerId);
u8 RCC_u8MCOClk						(u8 Copy_u8MCOClkType);
u8 RCC_USBPrescaler					(u8 Copy_u8USBPrescalerId);
u8 RCC_ADCPrescaler					(u8 Copy_u8ADCPrescalerId);
u8 RCC_ClockSecuritySystem			(u8 Copy_u8CssStatus);
u8 RCC_u8HSITrimingCalibration		(s16 Copy_u8CalibrationValueKHZ);
u8 RCC_u8InitSysClk                 (void);
#endif /* RCC_INTERFACE_H_ */
