/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: TWI               **************/
/***************  Version: 1.00          **************/
/******************************************************/

/****************** Include Library ******************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************************************/

/****************** Include MCAL *********************/
#include "TWI_Register.h"
#include "TWI_private.h"
#include "TWI_Interface.h"
#include "TWI_config.h"
/****************************************************/

//pass 0 in the slave address argument if the master not be addressed
void TWI_voidMaster_Init(u8 copy_u8SlaveAddress)
{
	//SCL is 400000 bit / sec
	//Cpu Frequency is 8 MHZ
	//TWBR Register is 2
	//TWPS Bits is 0
	TWBR = 2;
	CLR_BIT(TWSR,TWSR_TWPS1);
	CLR_BIT(TWSR,TWSR_TWPS0);

	//Set The Master Address if the Address is not zero
	if(copy_u8SlaveAddress != 0)
	{
		TWAR = copy_u8SlaveAddress<<1;
	}


	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlave_Init(u8 Copy_u8SlaveAddress)
{

	//Intialize The Slave Address
	TWAR = Copy_u8SlaveAddress<<1;

	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);

}

TWI_ERRORStatus TWI_SendStartCondition(void)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;

	//Send Start conditon
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//Check For The Status
	if((TWSR & 0xF8) != START_ACK)
	{
		Local_ErrorStatus = StartConditionError;
	}

	return Local_ErrorStatus;
}

TWI_ERRORStatus TWI_SendRepeatedStart(void)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;

	//Send Start conditon
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while( GET_BIT(TWCR,TWCR_TWINT) == 0 );

	//Check For The Status
	if((TWSR & 0xF8) != REPEAT_START_ACK)
	{
		Local_ErrorStatus = RepeatedStartError;
	}

	return Local_ErrorStatus;

}

TWI_ERRORStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;

	//Clear the Start condition Bit
	CLR_BIT(TWCR,TWCR_TWSTA);

	//Set Slave Address in the MSB in the data Register With Write Request
	TWDR = Copy_u8SlaveAddress<<1;
	CLR_BIT(TWDR,0);      // For Write Request
	
	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while( GET_BIT(TWCR,TWCR_TWINT) == 0 );

	//Check For The Status
	if((TWSR & 0xF8) != SLAVE_ADD_WR_ACK)
	{
		Local_ErrorStatus = SlaveAddressWithWriteError;
	}

	return Local_ErrorStatus;
}

TWI_ERRORStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;


	//Clear the Start condition Bit
	CLR_BIT(TWCR,TWCR_TWSTA);

	//Set Slave Address in the MSB in the data Register With Write Request
	TWDR = Copy_u8SlaveAddress<<1;
	SET_BIT(TWDR,0);      // For Read Request

	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while( GET_BIT(TWCR,TWCR_TWINT) == 0 );

	//Check For The Status
	if((TWSR & 0xF8) != SLAVE_ADD_RD_ACK )
	{
		Local_ErrorStatus = SlaveAddressWithReadError;
	}


	return Local_ErrorStatus;
}

TWI_ERRORStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;

	//Set the data to Register TWDR
	TWDR = Copy_u8DataByte;

	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while( GET_BIT(TWCR,TWCR_TWINT) == 0 );

	//Check For The Status
	if((TWSR & 0xF8) != MSTR_WR_BYTE_ACK )
	{
		Local_ErrorStatus = MasterWriteByteError;
	}



	return Local_ErrorStatus;
}

TWI_ERRORStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte)
{
	TWI_ERRORStatus Local_ErrorStatus = NO_Error;

	//Enable Acknowledge Bit of master after receiving data from slave
    SET_BIT(TWCR,TWCR_TWEA);

	//Clear the interrupt flag to allow slave to send Data
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is rasied again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);


	//Check For The Status
	if((TWSR & 0xF8) !=  MSTR_RD_BYTE_ACK )
	{
		Local_ErrorStatus = MasterReadByteError;
	}

	else
	{
		//Read The Recieved Data
		*Copy_pu8DataByte = TWDR;
	}


	return Local_ErrorStatus;
}

void TWI_SendStopCondition(void)
{
	//Generate Stop Condition on the Bus
	SET_BIT(TWCR,TWCR_TWSTO);

	//Clear the interrupt flag to start send the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

}
