/***************************************************************************/
/***************************************************************************/
 /*********************	Author: Marc Sameh	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: Timer		 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "TIMER_reg.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"

static void (*TIMER0_pvOVFCallBackFunc)(void)=NULL;
static void (*TIMER0_pvCTCCallBackFunc)(void)=NULL;
static void (*TIMER1_pvOFCallBackFunc)(void)=NULL;
static void (*TIMER1_pvOCCallBackFunc)(void)=NULL;
static void (*HWICU_pvCallBackFunc)(void)=NULL;
static uint8 Schedule_u8Periodicity;
static uint32 Schedule_u32TimeMS;
static uint8 OF_KEY=0;

void TIMER0_voidInit(void)
{

	//fast PWM mode
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	//compare output mode :set on top clear on compare(non inverted)
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	//set prescaler /64
	TCCR0 &= 0b11111000;
	TCCR0 |= 3;



	//set compare value =64 for 32 usec*/
	 OCR0= 64;

	//compare match interrupt enable
	SET_BIT(TIMSK,TIMSK_OCIE0);
}

void TIMER0_voidSetCompVal(uint8 Copy_u8CompVal)
{
	OCR0=Copy_u8CompVal;
}


uint8 Timer0_u8SetCallBack(uint8 Copy_u8IntType,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		if(Copy_u8IntType == TIMER_u8_OVF_INT)
		{
			TIMER0_pvOVFCallBackFunc=Copy_pvCallBackFunc;
		}
		else if(Copy_u8IntType==TIMER_u8_CTC_INT)
		{
			TIMER0_pvCTCCallBackFunc=Copy_pvCallBackFunc;
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER0 CTC ISR
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCTCCallBackFunc!=NULL)
	{
		TIMER0_pvCTCCallBackFunc();
	}
	else
	{
		//Do nothing
	}
}

void TIMER1_voidInit(void)
{

	//default is normal mode
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);




	//Interrupt Enable (overflow)
	SET_BIT(TIMSK,TIMSK_TOIE1);

	//Prescaler division by 8
	SET_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}

void Timer1_voidDisableOVInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE1);
}

uint8 Timer1_u8OFSetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER1_pvOFCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER1 overflow ISR
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(TIMER1_pvOFCallBackFunc!=NULL)
	{
		TIMER1_pvOFCallBackFunc();
	}
	else
	{
		//Do nothing
	}
}

void TIMER1_voidSetCompVal(uint16 Copy_u16CompVal)
{
	OCR1A=Copy_u16CompVal;
}

void TIMER1_voidSetTimerVal(uint16 Copy_u16Val)
{
	TCNT1=Copy_u16Val;
}

uint16 TIMER1_u16GetTimerReading(void)
{
	return TCNT1;
}




