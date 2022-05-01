#ifndef TMU_CONFIG_H_
#define TMU_CONFIG_H_

//		determine the interval of the scheduler in mS
#define OS_TICK			200

//		select the timer hardware channel
//	    	[ CH0  -   CH1   -    CH2 ]
#define TIM_CH			CH2

// 		determine Max Num of Tasks "Do not exceed 5"
#define MAX_TASKS		7

#endif /* TMU_CONFIG_H_ */
