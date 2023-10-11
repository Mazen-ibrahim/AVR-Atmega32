/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: EXTERNEL          **************/
/***************  Version: 1.00           *************/
/******************************************************/

//include library first
#include "STD_TYPES.h"
#include "BIT_MATH.h"


//include MCAL Layer Files
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_register.h"
#include "EXTI_config.h"


//Global Pointer to Hold INT0 Func
void (*EXTI_INT0ptrFunc)(void) = Null;

//Global Pointer to Hold INT1 Func
void (*EXTI_INT1ptrFunc)(void) = Null;

//Global Pointer to Hold INT2 Func
void (*EXTI_INT2ptrFunc)(void) = Null;


void EXTI_voidInt0Init(void)
{

	// check Sense control
  #if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

  #elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

  #elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
    CLR_BIT(MCUCR,MCUCR_ISC01);

  #elif INT0_SENSE == RASING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
    SET_BIT(MCUCR,MCUCR_ISC01);

  #else
    #error"Wrong INT0 Sense Configuration options"

#endif

  //check for Periphral Interuppt for INT0
  #if INT0_INTILIAL_STATE == ENABLED
     SET_BIT(GICR,GICR_INT0);

  #elif INT0_INTILIAL_STATE == DISABLED
     CLR_BIT(GICR,GICR_INT0);

  #else
     #error"Wrong INT0 INTILIAL STATE Configuration options"
#endif

}

u8 EXTI_u8Int0Init(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorState = OK;

	switch(copy_u8SenseControl)
	{
	   case LOW_LEVEL:
		   CLR_BIT(MCUCR,MCUCR_ISC00);
		   CLR_BIT(MCUCR,MCUCR_ISC01);
		   SET_BIT(GICR,GICR_INT0);
	    break;

	   case ON_CHANGE:
		   SET_BIT(MCUCR,MCUCR_ISC00);
		   CLR_BIT(MCUCR,MCUCR_ISC01);
		   SET_BIT(GICR,GICR_INT0);
        break;

	   case RASING_EDGE:
		   SET_BIT(MCUCR,MCUCR_ISC00);
		   SET_BIT(MCUCR,MCUCR_ISC01);
		   SET_BIT(GICR,GICR_INT0);
		break;

	   case FALLING_EDGE:
		   CLR_BIT(MCUCR,MCUCR_ISC00);
		   SET_BIT(MCUCR,MCUCR_ISC01);
		   SET_BIT(GICR,GICR_INT0);
		break;
	   
	   default:
		       Local_u8ErrorState = NOK;
	}


	return Local_u8ErrorState;

}


void EXTI_voidInt1Init(void)
{

	// check Sense control
  #if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

  #elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

  #elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
    CLR_BIT(MCUCR,MCUCR_ISC11);

  #elif INT0_SENSE == RASING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
    SET_BIT(MCUCR,MCUCR_ISC11);

 #else
    #error"Wrong INT0 Sense Configuration options"

#endif

    //check for Periphral Interuppt for INT1
  #if INT1_INTILIAL_STATE == ENABLED
     SET_BIT(GICR,GICR_INT1);


  #elif INT1_INTILIAL_STATE == DISABLED
     CLR_BIT(GICR,GICR_INT1);

  #else
     #error"Wrong INT0 INTILIAL STATE Configuration options"
#endif

}
u8 EXTI_u8Int1Init(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorState = OK;

		switch(copy_u8SenseControl)
		{
		   case LOW_LEVEL:
			   CLR_BIT(MCUCR,MCUCR_ISC10);
			   CLR_BIT(MCUCR,MCUCR_ISC11);
			   SET_BIT(GICR,GICR_INT1);
		    break;

		   case ON_CHANGE:
			   SET_BIT(MCUCR,MCUCR_ISC10);
			   CLR_BIT(MCUCR,MCUCR_ISC11);
			   SET_BIT(GICR,GICR_INT1);
	        break;

		   case RASING_EDGE:
			   SET_BIT(MCUCR,MCUCR_ISC10);
			   SET_BIT(MCUCR,MCUCR_ISC11);
			   SET_BIT(GICR,GICR_INT1);
			break;

		   case FALLING_EDGE:
			   CLR_BIT(MCUCR,MCUCR_ISC10);
			   SET_BIT(MCUCR,MCUCR_ISC11);
			   SET_BIT(GICR,GICR_INT1);
			break;
		   
		   default:
			       Local_u8ErrorState = NOK;
		}


		return Local_u8ErrorState;

}


void EXTI_voidInt2Init(void)
{
	// check Sense control
      #if INT2_SENSE == FALLING_EDGE
	    CLR_BIT(MCUCSR,MCUCSR_ISC2);

      #elif INT2_SENSE == RASING_EDGE
		SET_BIT(MCUCSR,MCUCSR_ISC2);

       #else
          #error "Wrong INT2 INTILIAL STATE Configuration options"
   #endif

   //check for Periphral Interuppt for INT0
	  #if INT2_INTILIAL_STATE == ENABLED
		 SET_BIT(GICR,GICR_INT2);

	  #elif INT2_INTILIAL_STATE == DISABLED
		 CLR_BIT(GICR,GICR_INT2);

	  #else
		   #error"Wrong INT2 INTILIAL STATE Configuration options"
		#endif



}
u8 EXTI_u8Int2Init(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorState = OK;

	  switch(copy_u8SenseControl)
		{
	       case RASING_EDGE:
			  SET_BIT(MCUCSR,MCUCSR_ISC2);
		      SET_BIT(GICR,GICR_INT2);
			break;

		  case FALLING_EDGE:
				   CLR_BIT(MCUCSR,MCUCSR_ISC2);
				   SET_BIT(GICR,GICR_INT2);
			break;
		  
		  default:
				   Local_u8ErrorState = NOK;
		}

	  return Local_u8ErrorState;

}


u8 EXTI_u8IntEnable(u8 Copy_u8IntName)
{
	u8 Local_u8Errorstatus = OK;
	switch(Copy_u8IntName)
	{
		case EXTI_0:
		 SET_BIT(GICR,GICR_INT0);
		break;
		
		
		case EXTI_1:
		 SET_BIT(GICR,GICR_INT1);
		break;
		
		
		case EXTI_2:
		 SET_BIT(GICR,GICR_INT2);
		break;
		
		default: Local_u8Errorstatus = NOK;
	}
	
	return Local_u8Errorstatus;
	
}


u8 EXTI_u8IntDisable(u8 Copy_u8IntName)
{
	u8 Local_u8Errorstatus = OK;
	switch(Copy_u8IntName)
	{
		case EXTI_0:
		 CLR_BIT(GICR,GICR_INT0);
		break;
		
		
		case EXTI_1:
		 CLR_BIT(GICR,GICR_INT1);
		break;
		
		
		case EXTI_2:
		 CLR_BIT(GICR,GICR_INT2);
		break;
		
		default: Local_u8Errorstatus = NOK;
	}
	
	return Local_u8Errorstatus;
	
}



u8 EXTI_u8Int0SetCallBack(void(*Copy_pvInti0)(void))
{
	u8 Local_u8Errorstatus = OK;
	if( Copy_pvInti0 != Null)
	{
		EXTI_INT0ptrFunc = Copy_pvInti0;
	}

	else
	{
		Local_u8Errorstatus = Null_Pointer;
	}

	return Local_u8Errorstatus;

}


u8 EXTI_u8Int1SetCallBack(void(*Copy_pvInti1)(void))
{
	u8 Local_u8Errorstatus = OK;
	if( Copy_pvInti1 != Null)
	{
		EXTI_INT1ptrFunc = Copy_pvInti1;
	}

	else
	{
		Local_u8Errorstatus = Null_Pointer;
	}

	return Local_u8Errorstatus;

}



u8 EXTI_u8Int2SetCallBack(void(*Copy_pvInti2)(void))
{
	u8 Local_u8Errorstatus = OK;
	if( Copy_pvInti2 != Null)
	{
		EXTI_INT2ptrFunc = Copy_pvInti2;
	}

	else
	{
		Local_u8Errorstatus = Null_Pointer;
	}

	return Local_u8Errorstatus;

}




// ISR Of INTI0
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
   if(EXTI_INT0ptrFunc != Null)
     	EXTI_INT0ptrFunc();
   else
   {
	   //Do Nothing
   }
}


// ISR Of INTI1
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
   if(EXTI_INT1ptrFunc != Null)
     	EXTI_INT1ptrFunc();
   else
   {
	   //Do Nothing
   }
}


// ISR Of INTI2
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
   if(EXTI_INT2ptrFunc != Null)
     	EXTI_INT2ptrFunc();
   else
   {
	   //Do Nothing
   }
}
