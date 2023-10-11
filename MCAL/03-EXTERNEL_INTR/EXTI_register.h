/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: EXTERNEL          **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef EXTERNEL_INT_H_
#define EXTERNEL_INT_H_

// To set perphireal interrupt
#define   GICR          *((volatile u8*)0x5B)
#define   GICR_INT1  7
#define   GICR_INT0  6
#define   GICR_INT2  5

#define   GIFR           *((volatile u8*)0x5A)

// To Set the the mode (sense) of INTRUPPT PIN   :
#define   MCUCR        *((volatile u8*)0x55)
#define   MCUCR_ISC11  3
#define   MCUCR_ISC10  2
#define   MCUCR_ISC01  1
#define   MCUCR_ISC00  0


#define   MCUCSR       *((volatile u8*)0x54)
#define   MCUCSR_ISC2  6


#endif //EXTERNEL_INT_H_
