/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: USART             **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/*
Description: Function Used to Intialize USART Depend on Config file.
Parameters: void.
Return: void.
*/
void USART_INIT(void);


//Synchronous Fucntions(polling)

/*
Description: Function Used to Send Data to USART.
Parameters: Data to Send to USART.
Return: void
*/
void USART_voidSEND_Synch(u8 Copy_u8Data);

/*
Description: Function Used to Send String Message to USART.
Parameters: Pointer to Array of Bytes
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument. 
*/
u8 USART_voidSendStringSynch(u8* data);

/*
Description: Function Used to Recieve Byte of Data from USART.
Parameters: void.
Return: Byte of Data Recieved.
*/
u8 USART_u8RECIEVE_Synch(void);

/*
Description: Function Used to Recieve Array of Bytes from USART.
Parameters: Pointer to Empty Array to Save Data in it , Number of bytes need to be Recieved from USART.
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument.  
*/
u8 USART_RecieveBuffer(u8*BufferData , u8 Buffer_size);



//Asychronous Functions(Interrupt)

/*
Description: Function Used to send Data to USART.
Parameters: Data Send to USART, Pointer to Callback Fucntion (Notification Fucntion)
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument. 
*/
u8 USART_u8SEND_Asynch(u8 Copy_u8Data,void(*Notify)(void));

/*
Description: Function Used to send String to USART.
Parameters: Pointer to Data Send, Pointer to Callback Fucntion (Notification Fucntion)
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument. 
*/
u8 USART_u8SendStringAsynch(u8* data ,void(*Notify)(void));

/*
Description: Function Used to Recieve Byte From USART.
Parameters: Pointer to variable to Save Data Recieved in it , Pointer to Callback Fucntion (Notification Fucntion)
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument. 
*/
u8 USART_u8Recieve_Asynch(u8* RecieveData ,void(*Notify)(void));


/*
Description: Function Used to Recieve Array of Bytes From USART.
Parameters: Pointer to Empty Array to Save Data Come from USART , Number of Bytes need to Be Recieved , Pointer to Callback Function (Notification Function)
Return: 
   1-OK : All Done Successfully
   2-NOK : Error Happen such as Null Pointer passed in argument. 
*/
u8 USART_u8RecieveBuffer_Asynch(u8* BufferData ,u8 BufferSize ,void(*Notify)(void));


#endif
