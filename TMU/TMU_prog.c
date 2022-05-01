#include "STD_TYPES.h"


#include "TMU_config.h"
#include "TMU_priv.h"

static u8 Num_ISR;
static u8 Count_ISR;

static TCB_t Tasks[ MAX_TASKS ];


void TMU_Init(void)
{
#if TIM_CH == CH0
	TCCR0 = 0x0D; // CTC , 1024 , dis OC0
	TIMSK |= (1<<1);
	#if OS_TICK <=16 && OS_TICK > 0

		OCR0 = (OS_TICK * F_CPU) / (1024000ul);
		Num_ISR = 1;
		Count_ISR = 1;

	#elif OS_TICK > 16
		u8 max;
		for (u8 i =1 ; i<=16;i++)//28 -> 1,2,4,7,14
		{
			if (OS_TICK %i ==0)
				max=i;
		}
		OCR0 = (max * F_CPU) / (1024000ul);
		Num_ISR = (OS_TICK / max );
		Count_ISR = Num_ISR;


	#else
	#error"your OS tick exceed 4194 mS"

	#endif

#elif TIM_CH == CH1
	TCCR1A =0;
	TCCR1B =0x0D;
	TIMSK |= (1<<4);
	#if OS_TICK <=4194 && OS_TICK > 0

		u16 counts = (OS_TICK * F_CPU)/ (1024000ul);
		OCR1AH = (u8)(counts>>8);
		OCR1AL = (u8)(counts);

		Num_ISR = 1;
		Count_ISR = 1;

	#else
	#error"your OS tick exceed 4194 mS"

	#endif

#elif TIM_CH == CH2
		TCCR2 = 0x0F; // CTC , 1024 , dis OC0
		TIMSK |= (1<<7);
		#if OS_TICK <=16 && OS_TICK > 0

			OCR2 = (OS_TICK * F_CPU) / (1024000ul);
			Num_ISR = 1;
			Count_ISR = 1;

		#elif OS_TICK > 16
			u8 max;
			for (u8 i =1 ; i<=16;i++)//28 -> 1,2,4,7,14
			{
				if (OS_TICK %i ==0)
					max=i;
			}
			OCR2 = (max * F_CPU) / (1024000ul);
			Num_ISR = (OS_TICK / max );
			Count_ISR = Num_ISR;
		#endif
#else
#error "selection of timer channel is wrong"
#endif
}


void TMU_CreateTask(void (*Fptr)(void), u16 Periodicity , u8 Priority, u8 Offset)
{
	if (Fptr != NULL && Priority < MAX_TASKS)
	{
		Tasks[Priority].Fptr = Fptr;
		Tasks[Priority].Periodicity = Periodicity;
		Tasks[Priority].Count = Offset; //Periodicity -1 ;
		Tasks[Priority].state = READY ;
	}
}


void TMU_StartScheduler(void)
{
	//Enable GIE
	asm("SEI");

	while(1);
}


void TMU_Pause(u8 Priority)
{
	if (Priority < MAX_TASKS)
		Tasks[Priority].state = PAUSED;
}

void TMU_Resume(u8 Priority)
{
	if (Priority < MAX_TASKS)
	{
		Tasks[Priority].state = READY;
		Tasks[Priority].Count = 0;
		//Tasks[Priority].Count = Tasks[Priority].Periodicity -1;
	}
}

void TMU_Delete(u8 Priority)
{
	if (Priority < MAX_TASKS)
	{
		Tasks[Priority].state = KILLED;
		Tasks[Priority].Fptr  = NULL;
	}
}


#if TIM_CH == CH0
//CTC CH0
void __vector_10 (void) __attribute__((signal));
void __vector_10(void)
{
	Count_ISR --;
	if (Count_ISR == 0)
	{
		//count++;
		//for (s8 i=MAX_TASKS -1 ; i >= 0 ; i--)	//high MAX-1 , Lowest 0
		for (u8 i=0; i<MAX_TASKS; i++)			//high 0,      Lowest MAX-1
		{
			if(Tasks[i].Count==0
					&& Tasks[i].Fptr != NULL
					&& Tasks[i].state == READY)
			{
				Tasks[i].Fptr();
				Tasks[i].Count = Tasks[i].Periodicity-1;
			}
			else
			{
				Tasks[i].Count --;
			}
		}

		Count_ISR = Num_ISR;
	}

}

#elif TIM_CH == CH1
void __vector_7 (void) __attribute__((signal));
//CTC CH1
void __vector_7(void)
{
	Count_ISR --;
	if (Count_ISR == 0)
	{
		//count++;
		//for (s8 i=MAX_TASKS -1 ; i >= 0 ; i--)	//high MAX-1 , Lowest 0
		for (u8 i=0; i<MAX_TASKS; i++)			//high 0,      Lowest MAX-1
		{
			if(Tasks[i].Count==0
					&& Tasks[i].Fptr != NULL
					&& Tasks[i].state == READY)
			{
				Tasks[i].Fptr();
				Tasks[i].Count = Tasks[i].Periodicity-1;
			}
			else
			{
				Tasks[i].Count --;
			}
		}

		Count_ISR = Num_ISR;
	}

}

#elif TIM_CH == CH2
void __vector_4 (void) __attribute__((signal));

//CTC CH2
void __vector_4(void)
{
	Count_ISR --;
	if (Count_ISR == 0)
	{
		//count++;
		//for (s8 i=MAX_TASKS -1 ; i >= 0 ; i--)	//high MAX-1 , Lowest 0
		for (u8 i=0; i<MAX_TASKS; i++)			//high 0,      Lowest MAX-1
		{
			if(Tasks[i].Count==0
					&& Tasks[i].Fptr != NULL
					&& Tasks[i].state == READY)
			{
				Tasks[i].Fptr();
				Tasks[i].Count = Tasks[i].Periodicity-1;
			}
			else
			{
				Tasks[i].Count --;
			}
		}

		Count_ISR = Num_ISR;
	}
}

#else
#error "selection of timer channel is wrong"
#endif
