/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: EXTERNEL          **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef EXTI_config_H_
#define EXTI_config_H_

/*
  options:
    1-LOW_LEVEL:
    2-ON_CHANGE:
    3-FALLING_EDGE:
    4-RASING_EDGE:

*/

#define INT0_SENSE   FALLING_EDGE
#define INT1_SENSE   FALLING_EDGE


/*
  options:
    3-FALLING_EDGE:
    4-RASING_EDGE:
*/

#define INT2_SENSE    FALLING_EDGE



/*
  options:
    1-ENABLED:
    2-DISABLED:

*/

#define INT0_INTILIAL_STATE  ENABLED
#define INT1_INTILIAL_STATE  DISABLED
#define INT2_INTILIAL_STATE  ENABLED

#endif
