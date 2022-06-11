/**********************************************************/
/***************** Name    : Ahmed Hassan *****************/
/***************** Date    : 12/7/2021    *****************/
/***************** Version : 1.0          *****************/
/***************** SWC     : GPIO         *****************/
/**********************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

//Macros for Ports
#define GPIO_u8_GPIOA									0
#define GPIO_u8_GPIOB									1
#define GPIO_u8_GPIOC									2

//Macros for Pins
#define GPIO_u8_PIN0                    				0
#define GPIO_u8_PIN1                    				1
#define GPIO_u8_PIN2                    				2
#define GPIO_u8_PIN3                    				3
#define GPIO_u8_PIN4                    				4
#define GPIO_u8_PIN5                    				5
#define GPIO_u8_PIN6                    				6
#define GPIO_u8_PIN7                    				7
#define GPIO_u8_PIN8                    				8
#define GPIO_u8_PIN9                    				9
#define GPIO_u8_PIN10                   				10
#define GPIO_u8_PIN11                   				11
#define GPIO_u8_PIN12                   				12
#define GPIO_u8_PIN13                   				13
#define GPIO_u8_PIN14                   				14
#define GPIO_u8_PIN15                   				15


//Macros for PinModes
//Input
#define GPIO_u8_MODE_INPUT_ANALOG						0b0000
#define GPIO_u8_MODE_INPUT_FLOATING						0b0100
#define GPIO_u8_MODE_INPUT_PULLDOWN						0b1000
#define GPIO_u8_MODE_INPUT_PULLUP						0b11000

//Output
//10MHZ
#define GPIO_u8_MODE_OUTPUT_GP_PP_10MHZ					0b0001
#define GPIO_u8_MODE_OUTPUT_GP_OD_10MHZ					0b0101
#define GPIO_u8_MODE_OUTPUT_AF_PP_10MHZ					0b1001
#define GPIO_u8_MODE_OUTPUT_AF_OD_10MHZ					0b1101

//2MHZ
#define GPIO_u8_MODE_OUTPUT_GP_PP_2MHZ					0b0010
#define GPIO_u8_MODE_OUTPUT_GP_OD_2MHZ					0b0110
#define GPIO_u8_MODE_OUTPUT_AF_PP_2MHZ					0b1010
#define GPIO_u8_MODE_OUTPUT_AF_OD_2MHZ					0b1110

//50MHZ
#define GPIO_u8_MODE_OUTPUT_GP_PP_50MHZ					0b0011
#define GPIO_u8_MODE_OUTPUT_GP_OD_50MHZ					0b0111
#define GPIO_u8_MODE_OUTPUT_AF_PP_50MHZ					0b1011
#define GPIO_u8_MODE_OUTPUT_AF_OD_50MHZ					0b1111

//Macros for Pin Value
#define GPIO_u8_HIGH									1
#define GPIO_u8_LOW										0

typedef struct{
	u8 PortId;
	u8 PinId;
	u8 PinMode;
}GPIO_PinConfig_t;

typedef struct{
	u8 	PortId;
	u16 PinsId;
	u8 	PortMode;
}GPIO_PortConfig_t;



u8 GPIO_u8PinInit			(const GPIO_PinConfig_t * Copy_PstrPinConfig);

u8 GPIO_u8SetPinValue		(const GPIO_PinConfig_t * Copy_PstrPinConfig, u8 Copy_u8PinValue);

u8 GPIO_u8GetPinValue		(const GPIO_PinConfig_t * Copy_PstrPinConfig, u8 * Copy_Pu8ReturnedPinValue);

u8 GPIO_u8TogPinValue		(const GPIO_PinConfig_t * Copy_PstrPinConfig);

u8 GPIO_u8SetPinValueAtomic (const GPIO_PinConfig_t * Copy_PstrPinConfig, u8 Copy_u8PinValue);

u8 GPIO_u8PortInit			(const GPIO_PortConfig_t * Copy_PstrPortConfig);

u8 GPIO_u8SetPortValueAtomic	(const GPIO_PortConfig_t * Copy_PstrPortConfig);


#endif
