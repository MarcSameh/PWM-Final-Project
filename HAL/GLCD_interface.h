/***************************************************************************/
/***************************************************************************/
/*********************	Author: Marc Sameh		  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

/*Graphical LCD initialization*/
void GLCD_Init(void);

/*Sending string on LCD*/
void GLCD_VoidSendString(const char* Copy_pchString);

/*Sending command to LCD*/
void GLCD_VoidSendCommand(uint8 Copy_u8Command);

/*Sending Data to LCD*/
void GLCD_VoidSendData(uint8 Copy_u8Data);

/*Sending number to LCD*/
void GLCD_SendNumber(uint16 Copy_u32Number);

/*Clearing the  LCD*/
void GLCD_CLR(void);

/*PWM Graph drawing on LCD*/
void PWM_Graph(float dutyCycle,uint8 PeriodTime);
void drawUpLine(uint8 OnTime);
void drawPulse(void);
void drawDownLine(uint8 OffTime);
void drawMiddleLine(uint8 Copy_Sahm);

#endif
