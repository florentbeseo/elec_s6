#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "servo.h"


#define PERIOD_TIMER 10 //ms

void SERVO_init(void){
	//initialisation et lancement du timer1 à une période de 10 ms

	TIMER_run_us(TIMER1_ID, PERIOD_TIMER *1000, FALSE); //10000us = 10ms
	//TIMER_run_us(TIMER4_ID, PERIOD_TIMER *1000, FALSE); //10000us = 10ms

	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)

	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE);
	//TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);

	//rapport cyclique reglé pour une position servo de 50%
	SERVO_set_position(0);
}

//position est exprimée de 0 à 100.
void SERVO_set_position(uint16_t position){
	//if(position > 100)
		//position = 100; //écretage si l'utilisateur demande plus de 100%

	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3,position+100);
	//TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1,position+100);

		//TODO : mise à jour du rapport cyclique.
		//duty doit être exprimé ici de 100 à 200 (sur 1000) (pour un rapport cyclique
		//de 10% à 20%, c’est-à-dire une durée de pulse de 1 à 2ms dans la période de 10ms)
		//Donc on additionne 100 à position.
}
void SERVO_process_test(uint16_t position)//uint16_t position)
{
	static uint16_t;

	//SERVO_set_position(position);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3,position+100);
	HAL_Delay(10); //anti-rebond "de fortune" en cadencant la lecture du bouton
}
