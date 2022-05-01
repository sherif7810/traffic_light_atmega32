#ifndef TMU_PRIV_H_
#define TMU_PRIV_H_

typedef struct
{
	void(*Fptr)(void);
	u16 Periodicity;
	u16 Count;
	u8 state;
}TCB_t;

#define READY 		45
#define PAUSED		78
#define KILLED		31


#define CH0			23
#define CH1			96
#define CH2			67

#define OCR0		*((volatile u8*)0x5C)
#define TIMSK		*((volatile u8*)0x59)
#define TIFR		*((volatile u8*)0x58)

#define TCCR0		*((volatile u8*)0x53)
#define TCNT0		*((volatile u8*)0x52)

#define TCCR1A		*((volatile u8*)0x4F)
#define TCCR1B		*((volatile u8*)0x4E)

#define TCNT1H		*((volatile u8*)0x4D)
#define TCNT1L		*((volatile u8*)0x4C)

#define OCR1AH		*((volatile u8*)0x4B)
#define OCR1AL		*((volatile u8*)0x4A)

#define OCR1BH		*((volatile u8*)0x49)
#define OCR1BL		*((volatile u8*)0x48)

#define OCR1B		*((volatile u16*)0x48)

#define ICR1H		*((volatile u8*)0x47)
#define ICR1L		*((volatile u8*)0x46)

#define TCCR2		*((volatile u8*)0x45)
#define TCNT2		*((volatile u8*)0x44)

#define OCR2		*((volatile u8*)0x43)
#define OCR1BL		*((volatile u8*)0x48)

#define F_CPU 16000000UL

#endif /* TMU_PRIV_H_ */
