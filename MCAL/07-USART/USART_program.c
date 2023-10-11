/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: USART             **************/
/***************  Version: 1.00           *************/
/******************************************************/

/***************** Include Libraries ******************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************/

/****************** Include MCAL **********************/
#include "USART_Register.h"
#include "USART_Private.h"
#include "USART_config.h"
/******************************************************/

static void (*Notify_SEND_Asynch)(void) = Null;
static void (*Notify_SENDStringAsynch)(void) = Null;
static char*StringAsynchData = Null;
static u8 StringAsynchIndex = 0;
static u8 sendState = IDLE;


static void(*Notify_RecieveAsynch)(void) = Null;
static void(*Notify_RecieveStringAsynch)(void) = Null;
static char *Recievedcharacter = Null;
static char *RecievedString = Null;
static u8 RecieveAsynchIndex = 0;
static u8 RecieveAsynchSize = Null;
static u8 RecieveState = IDLE;


void USART_INIT(void)
{
	u8 Local_u8UCSRC = 0;

    //Select to Access UCSRC Register
	 SET_BIT(Local_u8UCSRC,UCSRC_URSEL);


	//Check Stop Bit First

	  #if Stops_Bits  ==  OneStopBit
		CLR_BIT(Local_u8UCSRC,UCSRC_USBS);

	  #elif Stops_Bits ==  TwoStopBit
		SET_BIT(Local_u8UCSRC,UCSRC_USBS);

	  #else
		 #error"Wrong Configuration of Stop Bits"

  #endif

    //Check Parity Mode
      #if Parity_MODE == Disabled
	    CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
	    CLR_BIT(Local_u8UCSRC,UCSRC_UPM1);

     #elif Parity_MODE == Even
	    CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
	   	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);

     #elif Parity_MODE == Odd
	    SET_BIT(Local_u8UCSRC,UCSRC_UPM0);
	   	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);

  #endif


	//Set Character Size
   #if   Data_Size == Five
		CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
		CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
		CLR_BIT(UCSRB,UCSRB_UCSZ2);

   #elif Data_Size == Six
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
		CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
		CLR_BIT(UCSRB,UCSRB_UCSZ2);

   #elif Data_Size == Seven
		CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
		CLR_BIT(UCSRB,UCSRB_UCSZ2);

   #elif Data_Size == Eight
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
		CLR_BIT(UCSRB,UCSRB_UCSZ2);

   #elif Data_Size == Nine
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
		SET_BIT(UCSRB,UCSRB_UCSZ2);
   #else
     #error"Wrong Data Size"

#endif


	//Check USART Mode
   #if USART_MODE == Asynchronous
		CLR_BIT(Local_u8UCSRC,UCSRC_UMSEL);

   #elif USART_MODE == Synchronous
		SET_BIT(UCSRC,UCSRC_UMSEL);
   #else
     #error"Wrong USART Mode"

#endif

	//Set UCSRC Register Value
	  UCSRC = Local_u8UCSRC;

    //Set Baud Rate 9600
	 UBRRL = 51;

   //Set Send and Recieve Bit of USART
	 SET_BIT(UCSRB,UCSRB_RXEN);
	 SET_BIT(UCSRB,UCSRB_TXEN);


}

//Synchronous Fucntions(polling)
void USART_voidSEND_Synch(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	UDR = Copy_u8Data;

}
u8 USART_voidSendStringSynch(char* data)
{  

    u8 Local_Status status = OK
	u8 Local_u8Index = 0;
	
	if( data == Null )
	{
		status = NOK;
		return status;
	}
	
	while(data[Local_u8Index] !='\0')
	{
		USART_voidSEND_Synch(data[Local_u8Index]);
		Local_u8Index++;
	}
	
	return status;

}
u8 USART_u8RECIEVE_Synch(void)
{

	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}
u8 USART_RecieveBuffer(u8*BufferData , u8 Buffer_size)
{
	u8 Local_u8Status = OK;

	if(BufferData == Null || Buffer_size == 0)
	{
		Local_u8Status = NOK;
	}

	else
	{
		for(int i = 0 ;i<Buffer_size; i++)
			{
				BufferData[i] = USART_u8RECIEVE_Synch();
			}
	}

	return Local_u8Status;

}


//Asychronous Functions(Interrupt)
u8 USART_u8SEND_Asynch(u8 Copy_u8Data,void(*Notify)(void))
{
	u8 Local_u8State = OK;

    //Check Null pointer

	if(Notify == Null)
	{
		Local_u8State = NOK;

	}

	else if(sendState == IDLE)
	{
		//set State to send Character
		sendState = character;

		//set Notify Function
		Notify_SEND_Asynch = Notify;

		//Set Send Data to UDR
		  UDR = Copy_u8Data;

	   //Enable UDRE Interrupt
		 SET_BIT(UCSRB,UCSRB_UDRIE);
	 }


	return Local_u8State;


}
u8 USART_u8SendStringAsynch(char* Copy_u8Data ,void(*Notify)(void))
{
	u8 Local_u8State = OK;

    //Check Null pointer

	if(Notify == Null)
	{
		Local_u8State = NOK;

	}

	else if(sendState == IDLE)
	{
		//set State to send Character
		sendState = String;

		//set Notify Function
		Notify_SENDStringAsynch = Notify;

		//Copy of Data to handle in ISR
		  StringAsynchData = Copy_u8Data;

		//Set Send Data to UDR
		UDR = Copy_u8Data[StringAsynchIndex];

		//increment Index
		 StringAsynchIndex++;

	   //Enable UDRE Interrupt
	    SET_BIT(UCSRB,UCSRB_UDRIE);
	 }


	return Local_u8State;
}


// ISR Function of UDRE (send Data)
void __vector_14 (void)   __attribute__((signal));
void __vector_14 (void)
{

	if( sendState == character)
	{
		//Set SendState to IDLE
		 sendState = IDLE;

		//Enable Notify Function
		 Notify_SEND_Asynch();

		//disable UDRE Interrupt
		 CLR_BIT(UCSRB,UCSRB_UDRIE);
	}

	else if (sendState == String)
	{
       if(StringAsynchData[StringAsynchIndex] == '\0')
       {
    	   //Set SendState to IDLE
    	   	sendState = IDLE;

    	   //Enable Notify Function
    	   Notify_SENDStringAsynch();

    	   StringAsynchIndex = 0;

    	   //disable UDRE Interrupt
    	   	CLR_BIT(UCSRB,UCSRB_UDRIE);
       }

       else
       {
    	   //Set Send Data to UDR
    	   	UDR = StringAsynchData[StringAsynchIndex];

    	   	//increment Index
    	   	 StringAsynchIndex++;
       }


	}

}



//Asychronous Functions(Interrupt)
u8 USART_u8Recieve_Asynch(char* RecieveData ,void(*Notify)(void))
{
	u8 Local_u8State = OK;

      //check Null Pointer
	 if(RecieveData == Null)
	 {
		 Local_u8State = NOK;
	 }

	 else if(RecieveState == IDLE)
	 {

		 //Set State
		 RecieveState = character;

		 //Set Notify Function
		 Notify_RecieveAsynch = Notify;

		 Receivedcharacter = RecieveData;

		 //Enable RXC Interrupt
		 SET_BIT(UCSRB,UCSRB_RXIE);

	 }

	 return Local_u8State;
}

u8 USART_u8RecieveBuffer_Asynch(char* BufferData ,u8 BufferSize ,void(*Notify)(void))
{
	u8 Local_u8State = OK;

	//check Null Pointer and BufferSize
	if(BufferData == Null  || BufferSize == 0)
	{
		Local_u8State = NOK;
	}

	else if(RecieveState == IDLE)
	{
		//Set State
		RecieveState = String;

        //Set Notify Function
		Notify_RecieveStringAsynch = Notify;

		//Copy of Buffer
		RecievedString = BufferData;

		//Intialize Index
		RecieveAsynchIndex = 0;

		//copy Of BufferSize
		RecieveAsynchSize = BufferSize;

		//Enable RXC Interrupt
		SET_BIT(UCSRB,UCSRB_RXIE);
	}

	return Local_u8State;

}

// ISR Function of RXC (Recieve Data)
void __vector_13 (void)   __attribute__((signal));
void __vector_13 (void)
{
	if( ReceiveState == character )
	{
		//SetState to IDLE
		RecieveState = IDLE;

		//Get Date
		*Recievedcharacter = UDR;

		//Enable Notify Function
		Notify_RecieveAsynch();

		//Disable RXC
		CLR_BIT(UCSRB,UCSRB_RXIE);

	}

	else if( RecieveState == String )
	{
		//Get character and store in Buffer
		RecievedString[RecieveAsynchIndex] = UDR;

		//Increment Index
		RecieveAsynchIndex++;

		//check for end
		if(RecieveAsynchIndex == RecieveAsynchSize)
		{
			//SetState to IDLE
			RecieveState = IDLE;

			//Enable Notify Function
			Notify_RecieveStringAsynch();

			//Set RecieveAsynchIndex to zero
			RecieveAsynchIndex = 0;

			//Disable RXC Interrupt
			CLR_BIT(UCSRB,UCSRB_RXIE);
		}

	}



}





