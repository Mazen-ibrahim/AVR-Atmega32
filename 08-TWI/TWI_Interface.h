/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: TWI               **************/
/***************  Version: 1.00          **************/
/******************************************************/
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
   NO_Error,
   StartConditionError,
   RepeatedStartError,
   SlaveAddressWithWriteError,
   SlaveAddressWithReadError,
   MasterWriteByteError,
   MasterReadByteError,

}TWI_ERRORStatus;


/*
Description: Fucntion Used to initialize Master  
Parameters: Address used to Specifiy Master (pass 0 in the slave address argument if the master not be addressed)
Return: void
*/
void TWI_voidMaster_Init(u8 copy_u8SlaveAddress);


/*
Description: Fucntion Used to initialize Slave  
Parameters: Address used to Specifiy Slave
Return: void
*/
void TWI_voidSlave_Init(u8 Copy_u8SlaveAddress);


/*
Description: Fucntion Used to Send Start Condition  
Parameters: void
Return: 
  1- NO_Error: Sucessfully Start Condition Sent
  2- StartConditionError : Error Happend
*/
TWI_ERRORStatus TWI_SendStartCondition(void);



/*
Description: Fucntion Used to Send Repeated Start 
Parameters: void
Return: 
  1- NO_Error: Sucessfully Repeated Start Sent 
  2- RepeatedStartError : Error Happend
*/
TWI_ERRORStatus TWI_SendRepeatedStart(void);


/*
Description: Fucntion Used to Send Slave Address with Write opearation
Parameters:  Address used to Specifiy Slave
Return: 
  1- NO_Error: Sucessfully Repeated Start Sent 
  2- SlaveAddressWithWriteError: Error Happend
*/
TWI_ERRORStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);


/*
Description: Fucntion Used to Send Slave Address with Read opearation
Parameters:  Address used to Specifiy Slave
Return: 
  1- NO_Error: Sucessfully Repeated Start Sent 
  2- SlaveAddressWithReadError: Error Happend
*/
TWI_ERRORStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);


/*
Description: Fucntion Used to Send Data byte to Slave Based on Slave Address Sent 
Parameters: Data Byte to Send
Return: 
  1- NO_Error: Sucessfully Repeated Start Sent 
  2- MasterWriteByteError: Error Happend
*/
TWI_ERRORStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

/*
Description: Fucntion Used to Read Data byte from Slave Based on Slave Address Sent 
Parameters: Data Byte to Send
Return: 
  1- NO_Error: Sucessfully Repeated Start Sent 
  2- MasterReadByteError: Error Happend
*/
TWI_ERRORStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte);

/*
Description: Fucntion Used to Send Stop Condition
Parameters: void
Return: void 
*/
void TWI_SendStopCondition(void);

#endif
