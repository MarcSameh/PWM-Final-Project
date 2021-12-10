
//#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include "Err_type.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SPI_interface.h"
#include"EXTI_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "GLCD_interface.h"

#include "Font.h"


void SW_ICU (void);

volatile static f32 SWICU_u16PeriodTicks =0;
volatile static f32 SWICU_u16ONTicks =0;

int main()
{
	int Frequency;
	int Frequency2;
	int Periodic_Time;
	int Duty_Cycle;
	/*Port initialization*/
	PORT_voidInit();

	/*external interrupt initialization & Set call back*/
	EXTI_voidInit();
	EXTI_u8SetCallBack(INT0,&SW_ICU);

	/*SPI initialization*/
    SPI_Inits();

    /*Graphical LCD initialization*/
	GLCD_Init();
	GLCD_CLR();


	/*Generates PWM*/
	TIMER0_voidInit();

	/*Reads the PWM signal*/
	TIMER1_voidInit();

	/*General Interrupt initialization*/
	GIE_voidEnableGlobal();

	while(1)
		{
			while((SWICU_u16ONTicks ==0 ) && (SWICU_u16PeriodTicks==0));
			/*Periodic time Calculation*/
			Periodic_Time= SWICU_u16PeriodTicks * 0.5 +1;
			/*Frequency time Calculation*/
			Frequency= 1000000/Periodic_Time;
			Frequency2=Frequency/1000;

			/*Frequency Display*/
			GLCD_setXY(0,0);
			GLCD_VoidSendString("F:");
			GLCD_SendNumber(Frequency2);
			GLCD_VoidSendString(" KHZ");

			/*Duty Cycle calculation and dispaly*/
			Duty_Cycle= (SWICU_u16ONTicks/SWICU_u16PeriodTicks)*100;
			GLCD_setXY(48,0);
			GLCD_VoidSendString("DC:");
			GLCD_SendNumber(Duty_Cycle);
			GLCD_VoidSendString("%");

            /*Periodic time display*/
		    GLCD_setXY(0,3);
		    GLCD_VoidSendString("Time:");
		    GLCD_SendNumber(Periodic_Time);
		    GLCD_VoidSendString(" usec");
		    PWM_Graph(Duty_Cycle,255);



		}


}



void SW_ICU (void)
 {
	 static uint8 Local_u8Counter=0;
	 Local_u8Counter ++;

	 if (Local_u8Counter==1)
	 {
		TIMER1_voidSetTimerVal(0);
	 }
	 else if (Local_u8Counter == 2)
	 {
		 SWICU_u16PeriodTicks= TIMER1_u16GetTimerReading();
		 EXTI_u8SetSenseControl(INT0, FALLING_EDGE);

	 }
	 else if (Local_u8Counter ==3)
	 {
		 SWICU_u16ONTicks = TIMER1_u16GetTimerReading()  - SWICU_u16PeriodTicks;
		 //Local_u8Counter=0;
		 EXTI_u8DisableInterrupt(INT0);

	 }

 }
