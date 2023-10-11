/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: EXTERNEL          **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef EXTERNEL_INTERFACE_H_
#define EXTERNEL_INTERFACE_H_




 
/* 
 Description: pre build configuration functions for Externel Interrupt 
 Parameters:void
 return :void
*/
void EXTI_voidInt0Init(void);
void EXTI_voidInt1Init(void);
void EXTI_voidInt2Init(void);

/*
  Description : function to Set Sense control  of Init0 or Init1 using postbuild configuration
  Input options:
    1-LOW_LEVEL:
    2-ON_CHANGE:
    3-FALLING_EDGE:
    4-RASING_EDGE:
  Return: 
    1-OK : No Error Happen
	2-NOK: Error Happen
 */
u8 EXTI_u8Int0Init(u8 copy_u8SenseControl);
u8 EXTI_u8Int1Init(u8 copy_u8SenseControl);

/*
  Description : function to Set Sense control  of Init2 using postbuild configuration
  Input options:
    1-FALLING_EDGE:
    2-RASING_EDGE:
  Return: 
    1-OK: No Error Happen
	2-NOK: Error Happen
 */
u8 EXTI_u8Int2Init(u8 copy_u8SenseControl);


/*
 Description: Fucntion to Enable specific Interrupt Enable
 Input options:
  1-EXTI_1
  2-EXTI_2
  3-EXTI_3
 Return:
  1-OK: No Error Happen
  2-NOK: Error Happen
*/
u8 EXTI_u8IntEnable(u8 Copy_u8IntName);

/*
 Description: Fucntion to Disable specific Interrupt Enable
 Input options:
  1-EXTI_1
  2-EXTI_2
  3-EXTI_3
 Return:
  1-OK: No Error Happen
  2-NOK: Error Happen
*/

u8 EXTI_u8IntDisable(u8 Copy_u8IntName);


/*
 Description: Function to take address of INT0 Function Callback
 Input options: 
  1-address of Callback Fucntion
 Return:
  1-OK: No Error Happen
  2-NOK: Error Happen
  3-Null_Pointer
*/

u8 EXTI_u8Int0SetCallBack(void(*Copy_pvInti0)(void));


/*
 Description: Function to take address of INT1 Function Callback
 Input options: 
  1-address of Callback Fucntion
 Return:
  1-OK: No Error Happen
  2-NOK: Error Happen
  3-Null_Pointer
*/

u8 EXTI_u8Int1SetCallBack(void(*Copy_pvInti1)(void));


/*
 Description: Function to take address of INT2 Function Callback
 Input options: 
  1-address of Callback Fucntion
 Return:
  1-OK: No Error Happen
  2-NOK: Error Happen
  3-Null_Pointer
*/

u8 EXTI_u8Int2SetCallBack(void(*Copy_pvInti2)(void));



#endif  //EXTERNEL_INTERFACE_H_
