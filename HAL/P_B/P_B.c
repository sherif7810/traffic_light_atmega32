#include "P_B_CFG.h"
#include "P_B.h"
#include "DIO.h"

void P_B_INIT(u8 p_b)
{
	PIN_MODE(P_B_COMMON_GND,OUTPUT);
	PIN_WRITE(P_B_COMMON_GND,LOW);
	switch (p_b)
	{
		case P_B_1:
		PIN_MODE(P_B_1_PIN,INPUT);
		PIN_PULL_UP(P_B_1_PIN,ENABLE);
		break;
		case P_B_2:
		PIN_MODE(P_B_2_PIN,INPUT);
		PIN_PULL_UP(P_B_2_PIN,ENABLE);
		break;
		case P_B_3:
		PIN_MODE(P_B_3_PIN,INPUT);
		PIN_PULL_UP(P_B_3_PIN,ENABLE);
		break;
		case P_B_4:
		PIN_MODE(P_B_4_PIN,INPUT);
		PIN_PULL_UP(P_B_1_PIN,ENABLE);
		break;
	}
}

u8 P_B_READ(u8 p_b)
{
	switch (p_b)
	{
		case P_B_1:
		if (PIN_READ(P_B_1_PIN) == PRESSED)
		{
			return PRESSED;
		}
		break;
		case P_B_2:
		if (PIN_READ(P_B_2_PIN) == PRESSED)
		{
			return PRESSED;
		}
		break;
		case P_B_3:
		if (PIN_READ(P_B_3_PIN) == PRESSED)
		{
			return PRESSED;
		}
		break;
		case P_B_4:
		if (PIN_READ(P_B_4_PIN) == PRESSED)
		{
			return PRESSED;
		}
		break;
		default:
		break;
	}
	return RELEASED;
}
