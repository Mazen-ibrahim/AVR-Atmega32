/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: USART             **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/*
  options:
    1-Asynchronous
    2-Synchronous
*/

#define  USART_MODE  Asynchronous


/*
  options :
    1-Disabled
    2-Even
    3-Odd
*/

#define Parity_MODE  Disabled

/*
  options :
    1-OneStopBit
    2-TwostopBit
*/

#define Stop_Bits  OneStopBit

/*
  options :
    1-Five
    2-Six
    3-Seven
    4-Eight
    5-Nine
*/

#define Data_Size  Eight



#endif
