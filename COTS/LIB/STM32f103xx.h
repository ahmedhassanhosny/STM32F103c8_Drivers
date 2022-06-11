/************************************************************/
/**************** Name 	  : Ahmed Hassan ********************/
/**************** Date 	  : 8/7/2021     ********************/
/**************** Version : 1.0          ********************/
/**************** SWC	  : STM32F103xx  ********************/
/************************************************************/
#ifndef STM32F103xx_h
#define STM32F103xx_h
/**********************	RCC Registers ***********************/

#define RCC_u32_BASE_ADDRESS 				0x40021000

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_RegDef_t;

#define RCC									((RCC_RegDef_t*)RCC_u32_BASE_ADDRESS)

/************************************************************/



/**********************GPIO Registers ***********************/

#define GPIO_u32_GPIOA_BASE_ADDRESS 				0x40010800U
#define GPIO_u32_GPIOB_BASE_ADDRESS 				0x40010C00U
#define GPIO_u32_GPIOC_BASE_ADDRESS 				0x40011000U

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_RegDef_t;

#define GPIOA								((GPIO_RegDef_t*)GPIO_u32_GPIOA_BASE_ADDRESS)
#define GPIOB								((GPIO_RegDef_t*)GPIO_u32_GPIOB_BASE_ADDRESS)
#define GPIOC								((GPIO_RegDef_t*)GPIO_u32_GPIOC_BASE_ADDRESS)

/************************************************************/


/**********************SysTick Registers ********************/

#define STK_u32_BASE_ADDRESS						0xE000E010U

typedef struct{
	
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_RegDef_t;

#define STK 										((STK_RegDef_t*)STK_u32_BASE_ADDRESS)



/************************************************************/


/**********************NVIC Register *************************/

#define NVIC_u32_BASE_ADDRESS						0xE000E100U

typedef struct{
	volatile u32 ISER[32];
	volatile u32 ICER[32];
	volatile u32 ISPR[32];
	volatile u32 ICPR[32];
	volatile u32 IABR[64];
	volatile u32 IPR [60];

}NVIC_RegDef_t;

#define NVIC										((NVIC_RegDef_t*)NVIC_u32_BASE_ADDRESS)
#define SCB_AIRCR									(*(volatile u32 *)0xE000ED0CU)

/************************************************************/


/**********************EXTI Register *************************/

#define EXTI_u32_BASE_ADDRESS						0x40010400U

typedef struct{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR ;

}EXTI_RegDef_t;

#define EXTI										((EXTI_RegDef_t*)EXTI_u32_BASE_ADDRESS)


/************************************************************/


/**********************DMA Register *************************/

#define DMA_ISR									*(volatile u32*)0x40020000U
#define DMA_IFCR								*(volatile u32*)0x40020004U
#define DMA_u32_BASE_ADDRESS					0x40020008U

typedef struct{
	volatile u32 CCR;
	volatile u32 CNDTR;
	volatile u32 CPAR;
	volatile u32 CMAR;
	volatile u32 reserved;
}DMA_RegDef_t;

typedef struct
{
	DMA_RegDef_t Copy_StrToArrofReg[7];
}DMA_Struct_to_RegDef_t;


#define DMA										((DMA_Struct_to_RegDef_t*)DMA_u32_BASE_ADDRESS)


/************************************************************/


/**********************UART Register *************************/

#define UART1_u32_BASE_ADDRESS					0x40013800U

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;

}UART1_RegDef_t;


#define UART1									((UART1_RegDef_t*)UART1_u32_BASE_ADDRESS)

/************************************************************/

/**********************ADC Register *************************/

#define ADC1_u32_BASE_ADDRESS					0x40012400U
#define ADC2_u32_BASE_ADDRESS					0x40012800U

typedef struct{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR[4];
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR[3];
	volatile u32 JSQR;
	volatile u32 JDR[4];
	volatile u32 DR;

}ADC_RegDef_t;


#define ADC1									((ADC_RegDef_t*)ADC1_u32_BASE_ADDRESS)
#define ADC2									((ADC_RegDef_t*)ADC2_u32_BASE_ADDRESS)



/************************************************************/

/**********************SPI Register *************************/
#define SPI1_u32_BASE_ADDRESS					0x40013000U
#define SPI2_u32_BASE_ADDRESS					0x40013800U

typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;
}SPI_RegDef_t;

#define SPI1									((SPI_RegDef_t*)SPI1_u32_BASE_ADDRESS)
#define SPI2									((SPI_RegDef_t*)SPI2_u32_BASE_ADDRESS)

#endif
/************************************************************/
