/************************************************************/
/**************** Name 	  : Ahmed Hassan ********************/
/**************** Date 	  : 14/7/2021    ********************/
/**************** Version : 1.0          ********************/
/**************** SWC	  : STK		 	 ********************/
/************************************************************/

#ifndef STK_INTERFACE_H
#define STK_INTEFACE_H

/*STK CLK Modes*/
#define STK_u8CLKSRC_PCLK					1
#define STK_u8CLKSRC_AHB_8					0

/*STK CTRL Reg Pins*/
#define STK_u8_COUNTFLAG					16
#define STK_u8_CLKSOURCE					2
#define STK_u8_EXCEPTION_REQ				1
#define STK_u8_COUNTER						0


#define STK_u8_SetIntervalSingle_FLAG		1
#define STK_u8_SetIntervalPeriodic_FLAG		2

#endif
