/***************************************************************************/
/***************************************************************************/
/*********************	Author: Marc Sameh		  **********************/
/*********************	Date:25/9/2021				  **********************/
/*********************	Layer: MCAL					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/* 1-LOW_LEVEL
 * 2-ON_CHANGE
 * 3-FALLING_EDGE
 * 4-RISING_EDGE
 */
#define EXTI_u8_INT0_SENSE			RISING_EDGE

/* 1-LOW_LEVEL
 * 2-ON_CHANGE
 * 3-FALLING_EDGE
 * 4-RISING_EDGE
 */
#define EXTI_u8_INT1_SENSE			FALLING_EDGE

/*
 * 1-FALLING_EDGE
 * 2-RISING_EDGE
 */
#define EXTI_u8_INT2_SENSE			FALLING_EDGE

/* 1-ENABLED
 * 2-DISABLED
 */
#define EXTI_u8_INT0_INITIAL_STATE  ENABLED

/* 1-ENABLED
 * 2-DISABLED
 */
#define EXTI_u8_INT1_INITIAL_STATE  DISABLED

/* 1-ENABLED
 * 2-DISABLED
 */
#define EXTI_u8_INT2_INITIAL_STATE  DISABLED

#endif
