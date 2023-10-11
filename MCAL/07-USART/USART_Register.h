/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: USART             **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR         *((volatile u8*)0x2C)    //USART I/O Data Register

//----------------------------------------------------------------------------------
#define UCSRA       *((volatile u8*)0x2B)    //USART Control and Status Register A
#define UCSRA_RXC   7                        //USART Receive Complete
#define UCSRA_TXC   6                        //USART Transmit Complete
#define UCSRA_UDRE  5                        //UDRE: USART Data Register Empty
#define UCSRA_FE    4                        //FE: Frame Error
#define UCSRA_DOR   3                        //DOR: Data over run
#define UCSRA_PE    2                        //PE: Parity Error
#define UCSRA_U2X   1                        //Double the USART Transmission Speed
#define UCSRA_MPCM  0                        //MPCM: Multi-processor Communication Mode
//-------------------------------------------------------------------------------------

#define UCSRB       *((volatile u8*)0x2A)     //USART Control and Status Register B
#define UCSRB_RXIE  7                         //RXCIE: RX Complete Interrupt Enable
#define UCSRB_TXIE  6                         //TXCIE: TX Complete Interrupt Enable
#define UCSRB_UDRIE 5                         //UDRIE: USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN  4                         //RXEN: Receiver Enable
#define UCSRB_TXEN  3                         //TXEN: Transmitter Enable
#define UCSRB_UCSZ2 2                         //UCSZ2: Character Size Bit 2
#define UCSRB_RXB8  1                         //RXB8: Receive Data Bit 8
#define UCSRB_TXB8  0                         //TXB8: Transmit Data Bit 8
//---------------------------------------------------------------------------------------

#define UCSRC       *((volatile u8*)0x40)     //USART Control and Status Register C
#define UCSRC_URSEL 7                         //URSEL: Register Select ( 0:UBRRH Register, 1:UCSRC)
#define UCSRC_UMSEL 6                         //USART Mode Select (0:Asynchronous ,1:Synchronous)
#define UCSRC_UPM1  5                         //USART Parity Mode Bit 1
#define UCSRC_UPM0  4                         //USART Parity Mode Bit 0
#define UCSRC_USBS  3                         //USART Stop Bit Select
#define UCSRC_UCSZ1 2                         //Character Size Bit 1
#define UCSRC_UCSZ0 1                         //Character Size Bit 0
#define UCSRC_UCPOL 0                         //Clock Polarity
//------------------------------------------------------------------------------------------

#define UBRRL      *((volatile u8*)0x29)      //USART Baud Rate Registers – UBRRL and UBRRH
#define URBBH      *((volatile u8*)0x40)

#endif
