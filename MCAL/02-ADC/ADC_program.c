/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: ADC               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

//include Library First
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//include ADC headers
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

//Pointers
static u8 *ADC_u8Reading = Null;
static void(*Copy_ADC_Notification)(void) = Null;

//Pointers of ADC_Chain
static u8  *ADC_pu8ChainChannelArr  = Null;
static u16 *ADC_pu16ChainChannelRes = Null;
static u8   ADC_u8ChainSize;
static u8   ADC_u8ChainConversionIndex = 0;

//ADC State
u8 ADC_state = IDLE;

//ADC ISR Source
static u8 ADC_u8ISRSource;


void  ADC_VoidINIT(void)
{

  // Voltage Refrence Selection
    #if ADC_RefVoltage == AVCC
	   SET_BIT(ADMUX,ADMUX_REFS0);
	   CLR_BIT(ADMUX,ADMUX_REFS1);

    #elif ADC_RefVoltage == AREF
	   CLR_BIT(ADMUX,ADMUX_REFS0);
	   CLR_BIT(ADMUX,ADMUX_REFS1);
    #elif ADC_RefVoltage == INTERNAL_VCC
	   SET_BIT(ADMUX,ADMUX_REFS0);
	   SET_BIT(ADMUX,ADMUX_REFS1);
    #else
     #error "Incorrrect Selection of Voltage reference"

#endif


    //Activate Left Adjust Result
    #if ADC_LRA == Enable_LRA
      SET_BIT(ADMUX,ADMUX_ADLRA);
    #endif

    //Set Prescaler to divide by 128
     ADCSRA &= Pre_BitsClear;
     ADCSRA |= ADC_PreScaler;

   //Enable ADC
    #if ADC_Enable == Enable
      SET_BIT(ADCSRA,ADCSRA_ADEN);
    #endif



}
u8 ADC_u8StartconversionSynch(u8 Copy_u8Channel , u8*Copy_u8Reading)
{
	u32 Local_u32Counter   = 0;
	u8  Local_u8ErrorState = OK;

	 if(ADC_state == IDLE)
	 {
		   //Make ADC Busy
		    ADC_state = Busy;

		   //Clear The Mux Bits in ADMUX Register
		 	ADMUX &= MUX_BITS_Clear;

		 	//SET MUX Bits in ADMUX Register
		 	ADMUX |= Copy_u8Channel;

		     //Start Conversion
		 	 SET_BIT(ADCSRA,ADCSRA_ADSC);

		     //Polling (busy Waiting) until The conversion complete flag is Set or Counter reaching Time Out
		 	 while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) && (Local_u32Counter != ADC_u32TimeOut))
		 	 {
		 		 Local_u32Counter++;
		 	 }

		 	 if(Local_u32Counter == ADC_u32TimeOut)
		 	 {
		 		 //Loop is Broken Bec The Time Out is Reached
		 		 Local_u8ErrorState = NOk;
		 		 ADC_state = IDLE;
		 	 }
		 	 else
		 	 {
		 		 //Loop is Broken Bec The Conversion Complete Flag is Raised
		 		 //clear the conversion complete Flag
		 			 SET_BIT(ADCSRA,ADCSRA_ADIF);

		 	    //check for Null Safety
		 	    if(Copy_u8Reading != Null)
		 		  *Copy_u8Reading = ADCH;
		 	    else
		 	    	Local_u8ErrorState = NOk;

		 	    //Make ADC IDLE
		 	    ADC_state = IDLE;

		 	 }

	 }

	 else
	 {
		 Local_u8ErrorState = Busy_Func;
	 }


   return Local_u8ErrorState;

}
u8 ADC_u8StartconversionAsynch(u8 Copy_u8Channel , u8*Copy_u8Reading, void(*Copy_pvNotiFunc)(void))
{
	u8 Local_u8ErrorState = OK;

	if(ADC_state == IDLE)
	{
		//Check For Null Pointer
			if(Copy_u8Reading == Null || Copy_pvNotiFunc == Null)
			{
				Local_u8ErrorState = NOk;
			}

			else
			{
				//Make ADC Busy
				  ADC_state = Busy;

				//Make ADC ISR Source : Singal Channel
				  ADC_u8ISRSource = SINGLE_CHANNEL ;

				//Intialize The reading Variable globally
				  ADC_u8Reading = Copy_u8Reading;

				//Intialize The callBack Function globally
				  Copy_ADC_Notification = Copy_pvNotiFunc;

				//Clear The Mux Bits in ADMUX Register
				  ADMUX &= MUX_BITS_Clear;

			    //SET MUX Bits in ADMUX Register
				  ADMUX |= Copy_u8Channel;

			   //Start Conversion
				 SET_BIT(ADCSRA,ADCSRA_ADSC);

			   //ADC Interrupt Enable
				 SET_BIT(ADCSRA,ADCSRA_ADIE);

			}
	}

	else
	{
		Local_u8ErrorState = Busy_Func;
	}


	return Local_u8ErrorState;
}
u8 StartChainConversionAsynch(Chain_t *chain)
{
	u8 Local_u8ErrorState = OK;

	//Check For Null Safety
	if(chain == Null)
	{
		Local_u8ErrorState = NOk;
	}

	else
	{
		if(ADC_state == IDLE)
		{
			//Make ADC State Busy
			ADC_state = Busy;

			//Make ADC Source : CHAIN_CHANNEL
			ADC_u8ISRSource = CHAIN_CHANNEL;

			//Initialize Chain channel Array
			ADC_pu8ChainChannelArr = chain->Channel;

			//Initialize Chain channel Result
			ADC_pu16ChainChannelRes = chain->Result;

			//Initialize Chain Size
			ADC_u8ChainSize = chain->Size;

			//Initialize Notification Callback
		    Copy_ADC_Notification = chain->NotificationFunc;

            //Initialize ADC Chain Index
		    ADC_u8ChainConversionIndex = 0 ;

		    //Set Required Channel
		    ADMUX &= MUX_BITS_Clear;
		    ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

		    //Start ADC Conversion
		    SET_BIT(ADCSRA,ADCSRA_ADSC);

		    //Enable ADC Interrupt
		    SET_BIT(ADCSRA,ADCSRA_ADIE);
		}

		else
		{
			Local_u8ErrorState = Busy_Func;
		}
	}


	return Local_u8ErrorState;
}
// ISR OF ADC
void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SINGLE_CHANNEL)
	{
		//Read ADC Result
		  *ADC_u8Reading = ADCH;

		//Make ADC IDLE
		  ADC_state = IDLE;

		//Invoke CallBack ADC Notfication Function
		  Copy_ADC_Notification();

	    //Disable ADC Interrupt Enable
		  CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}

	else if(ADC_u8ISRSource == CHAIN_CHANNEL)
	{
        //Read ADC Current Conversion
		ADC_pu16ChainChannelRes[ADC_u8ChainConversionIndex] = ADCH;

		// Increment ADC Chain Index
		ADC_u8ChainConversionIndex++;

		//Check Chain Finished or Not
		if( ADC_u8ChainConversionIndex == ADC_u8ChainSize )
		{
			// Chain is Finished

			//Make ADC IDLE
			 ADC_state = IDLE;

			//Invoke the CallBack Notification Function
			 Copy_ADC_Notification();

			//Disable ADC Conversion Complete interrupt
			 CLR_BIT(ADCSRA,ADCSRA_ADIE);

		}

		else
		{
			// Chain is Not Finished
		    // Set new Channel
			ADMUX &= MUX_BITS_Clear;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			//Start new conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
