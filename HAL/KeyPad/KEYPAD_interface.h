/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: KEYPAD            **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/

#ifndef  KEYPAD_INTERFACE_H
#define  KEYPAD_INTERFACE_H

/*
* @brief : used to get the pressed key depend of type of KeyPad 4X3 or 4X4 based on KEYPAD_config.h
* @param : void
* @return: pressed key
*/

u8 KPD_u8GETPressedKey(void);


/*
* @brief : used to wait for user to press key
* @param : void
* @return: pressed key
*/
u8 KPD_u8WaitForKey(void);

#endif
