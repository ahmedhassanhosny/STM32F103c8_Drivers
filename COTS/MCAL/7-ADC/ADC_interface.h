/*
 * ADC_interface.h
 *
 *  Created on: Aug 18, 2021
 *      Author: ahmed
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*Conv Modes*/
#define ADC_u8_SINGLE_CONV_MODE						0
#define ADC_u8_SCAN_CONV_MODE						1


/*ADC Interrupt*/
#define ADC_u8_None									0
#define ADC_u8_EOC									(1<<5)
#define ADC_u8_JEOC									(1<<7)

/*Data Alignment*/
#define ADC_u8_RightAlignment						0
#define ADC_u8_LeftAlignment						1

/*Triggering type*/
#define ADC_u8_NORMAL_TRIGGER						0
#define ADC_u8_REG_EXTERNAL_TRIGGER					(1<<20)
#define ADC_u8_INJ_EXTERNAL_TRIGGER					(1<<15)

/*ExtTriggeringEvent*/
/*REGULAR*/
#define ADC_u8_Timer1_CC1							0
#define ADC_u8_Timer1_CC2							1
#define ADC_u8_Timer1_CC3							2
#define ADC_u8_Timer2_CC2							3
#define ADC_u8_Timer3_TRGO							4
#define ADC_u8_Timer4_CC4							5
#define ADC_u8_EXTI11								6
#define ADC_u8_SWSTART								7

/*INJECTED*/
#define ADC_u8_Timer1_TRGO							0
#define ADC_u8_Timer1_CC4							1
#define ADC_u8_Timer2_TRGO							2
#define ADC_u8_Timer2_CC1							3
#define ADC_u8_Timer3_CC4							4
#define ADC_u8_Timer4_TRGO							5
#define ADC_u8_EXTI15								6
#define ADC_u8_SWSTART								7


/*Channel Type*/
#define ADC_u8_REGULAR_CHANNEL						1
#define ADC_u8_INJECTED_CHANNEL						2

/*ADC ID*/
#define ADC_u8ADC1									0
#define ADC_u8ADC2									1


typedef struct{
	u8 ConvMode;
	u8 Continous;
	u8 Interrupt;
	u8 DataAlignment;
	u8 TriggeringType;
	u8 ExtTrigEvent;		/*DON'T CARE in case of TriggeringType = ADC_u8_NORMAL_TRIGGER*/
	u8 ChannelType;
	u8 NumbersofConversions;
	u8 *ChannelsSeq;		/*DON'T CARE in case of NumberofConversions = 0 (1 Conversion)*/
}ADC_InitConfig_t;




u8 ADC_u8Init			(ADC_InitConfig_t * Copy_PstrInitConfig);


/*this function can't work in scan mode*/
u8 ADC_u8ReadingRegularChannelPolling(u16* Copy_Pu8DataConverted);

u8 ADC_u8ReadingInjectedChannelPolling(u16* Copy_Pu8DataConverted);

/*this function can't work in scan mode*/
//u8 ADC_u8ReadingRegularChannelInterrupt(void);
//
//u8 ADC_u8ReadingInjectedChannelInterrupt(void);

u8 ADC_u8ExternalTriggerRegularSwConv(void);

u8 ADC_u8ExternalTriggerInjectedSwConv(void);

u8 ADC_u8ADCSetCallBack(u8 Copy_u8IntrIndex,void(*Copy_Pvoidtofunc)(void));



#endif /* ADC_INTERFACE_H_ */
