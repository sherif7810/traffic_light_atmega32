#ifndef TMU_INT_H_
#define TMU_INT_H_

void TMU_Init(void);

void TMU_CreateTask(void (*Fptr)(void), u16 Periodicity , u8 Priority, u8 Offset);

void TMU_StartScheduler(void);

void TMU_Pause(u8 Priority);

void TMU_Resume(u8 Priority);

void TMU_Delete(u8 Priority);

#endif /* TMU_INT_H_ */
