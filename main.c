#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LCD.h"
#include "P_B.h"
#include "TMU_int.h"
#include "DIO.h"

void Task0(void);
void Task1(void);
void Task2(void);
void Task3(void);
void PBTask1(void);
void PBTask2(void);
void LCDTask(void);

static u8 max_count = 15;
static u8 count = 15, state = 0;

int
main (void)
{
	//Initialization
	TMU_Init();
	
	P_B_INIT(P_B_1);
	P_B_INIT(P_B_2);
	
	LCD_INIT();
	
	u8 max_value_str[] = "Max value:";
	LCD_WRITE_STR(max_value_str);
	
	// LEDs
	PIN_MODE(PA0, OUTPUT);
	PIN_MODE(PA1, OUTPUT);
	PIN_MODE(PA2, OUTPUT);
	
	// 7 segment display
	PIN_MODE(PA3, OUTPUT);
	PIN_MODE(PA4, OUTPUT);
	PIN_MODE(PA5, OUTPUT);
	PIN_MODE(PA6, OUTPUT);
	PIN_MODE(PB0, OUTPUT);
	PIN_MODE(PB1, OUTPUT);
	PIN_MODE(PB2, OUTPUT);
	PIN_MODE(PB3, OUTPUT);

	TMU_CreateTask(Task0, 5, 6, 0);
	TMU_CreateTask(Task1, 5, 3, 0);
	TMU_CreateTask(Task2, 5, 4, 0);
	TMU_CreateTask(Task3, 5, 5, 0);
	TMU_CreateTask(PBTask1, 1, 0, 0);
	TMU_CreateTask(PBTask2, 1, 1, 0);
	TMU_CreateTask(LCDTask, 1, 2, 0);

	TMU_StartScheduler();
}

void ssd_display(u8 number)
{
	u8 l_number = number / 10;
	u8 r_number = number % 10;
	
	PIN_WRITE(PA3,GET_BIT(r_number,0));
	PIN_WRITE(PA4,GET_BIT(r_number,1));
	PIN_WRITE(PA5,GET_BIT(r_number,2));
	PIN_WRITE(PA6,GET_BIT(r_number,3));
	PIN_WRITE(PB0,GET_BIT(l_number,0));
	PIN_WRITE(PB1,GET_BIT(l_number,1));
	PIN_WRITE(PB2,GET_BIT(l_number,2));
	PIN_WRITE(PB3,GET_BIT(l_number,3));
}

void Task0( void)
{
	if (count == 1)
	{
		count = max_count + 1;
		TOG_BIT(state, 0);
		ssd_display(1);
	}
	else
	{
		ssd_display(count);
	}
	count--;
}

void Task1( void)
{
	if (state == 1)
	{
		PIN_WRITE(PA0,HIGH);
	}
	else
	{
		PIN_WRITE(PA0,LOW);
	}
}

void Task2( void)
{
	if (state == 0)
	{
		PIN_WRITE(PA1,HIGH);
	}
	else
	{
		PIN_WRITE(PA1,LOW);
	}
}

void Task3( void)
{
	if (count <= 3 && count >= 1)
	{
		PIN_WRITE(PA2,HIGH);
	}
	else
	{
		PIN_WRITE(PA2,LOW);
	}
}

void PBTask1(void)
{
	if (P_B_READ(P_B_1) == PRESSED)
	{
		max_count++;
	}
}

void PBTask2(void)
{
	if (P_B_READ(P_B_2) == PRESSED)
	{
		max_count--;
	}
}

void LCDTask(void)
{
	// 0 to display in first time
	static u8 previous;
	
	// It assumes only 2 digits will be displayed, because there are two 7 segment displays
	if (previous != max_count)
	{
		LCD_GOTO(1,0);
		// 0 is displayed, so that the 2 digits are overwritten
		if (max_count < 10)
		{
			LCD_WRITE_INT(0);
		}
		LCD_WRITE_INT(max_count);	
	}
	previous = max_count;
}
