/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: DIO               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_




/****************************************************************
   Description: Function Used to Set Pin Value of Specific Port *
   Paramaters:                                                  *
               1- Copy_u8Port:                                  *
			                Options:                            *
							    1-DIO_u8PORTA                   *
                                2-DIO_u8PORTB                   *
                                3-DIO_u8PORTC                   *
								4-DIO_u8PORTD                   *
																*
			  2- Copy_u8Pin:                                    *
			                Options:                            *
							    DIO_u8PIN0 <-> DIO_u8PIN7       *
																*
			  3- Copy_u8Value:                                  *
			                Options:                            *
							    1-DIO_u8PIN_HIGH                *
								2-DIO_u8PIN_LOW                 *
																*
    Return:                                                     *
              1-DIO_OK:  No Error                               *
			  2-DIO_NOK: Error Occur							*
																*
*****************************************************************/
u8 DIO_u8SetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value);




/****************************************************************
   Description: Function Used to Set Value for all Pins of PORT *
   Paramaters:                                                  *
               1- Copy_u8Port:                                  *
			                Options:                            *
							    1-DIO_u8PORTA                   *
                                2-DIO_u8PORTB                   *
                                3-DIO_u8PORTC                   *
								4-DIO_u8PORTD                   *
																*      
																*
			   2- Copy_u8Value:                                 *
			                Options:                            *
							    1-DIO_u8PORT_HIGH               *
								2-DIO_u8PORT_LOW                *
																*
    Return:                                                     *
              1-DIO_OK:  No Error                               *
			  2-DIO_NOK: Error Occur							*
																*
*****************************************************************/
u8 DIO_u8SetPortValue(u8 Copy_u8Port , u8 Copy_u8Value);



/****************************************************************
   Description: Function Used to Set Pin Value of Specific Port *
   Paramaters:                                                  *
               1- Copy_u8Port:                                  *
			                Options:                            *
							    1-DIO_u8PORTA                   *
                                2-DIO_u8PORTB                   *
                                3-DIO_u8PORTC                   *
								4-DIO_u8PORTD                   *
																*
			  2- Copy_u8Pin:                                    *
			                Options:                            *
							    DIO_u8PIN0 <-> DIO_u8PIN7       *
																*
			  3- Copy_u8PinValue: Pointer to Hold Value of Pin  *
			                                                    *
							                                    *
								                                *
																*
    Return:                                                     *
              1-DIO_OK:  No Error                               *
			  2-DIO_NOK: Error Occur							*
																*
*****************************************************************/
u8 DIO_GetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 *Copy_u8PinValue);


#endif //DIO_INTERFACE_H_
