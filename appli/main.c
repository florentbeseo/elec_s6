/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "servo.h"
#include "affichage.h"


void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);

#define utilisation_LCD
#ifdef utilisation_LCD
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	ILI9341_DrawCircle(20,20,5,ILI9341_COLOR_BLUE);
	//ILI9341_DrawLine(20,20,100,20,ILI9341_COLOR_RED);
	//ILI9341_DrawLine(20,20,20,100,ILI9341_COLOR_RED);
	ILI9341_Putc(110,11,'x',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	ILI9341_Putc(15,110,'y',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	//ILI9341_Puts(200,200, "chaine", &Font_11x18, ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);

	ILI9341_DrawRectangle(281,31,301,211,ILI9341_COLOR_RED);
	//ILI9341_INT_Fill(400, 0, ILI9341_Opts.width - 1, ILI9341_Opts.height, color);

	//ILI9341_DrawLine(0,0,320,240,ILI9341_COLOR_RED);
#define horloge_
#ifdef horloge
	SERVO_init();
	SERVO_process_test(0);
	//HAL_Delay(1000);
	SERVO_process_test(100);
	//HAL_Delay(1000);
	SERVO_process_test(150);
	//HAL_Delay(1000);
	uint8_t pos = 100;
	uint8_t angle = pos*0.9;
	uint8_t rad = (angle * 3.14)/180;
	uint8_t x = cos(rad);
	uint8_t y = sin(rad);
	ILI9341_DrawLine(160,120,160+x,120 + y,ILI9341_COLOR_RED);

	SERVO_process_test(pos);
//pour que l'ecran affiche l'angle du servo
#endif

#endif

	Init_Jauge();
	//uint16_t infrar;
	uint32_t i = 0;
	uint8_t cnt = 0;
	uint32_t vitesse = 0;

	uint8_t button = 0;
	uint8_t button1 = 0;
	uint8_t button2 = 0;
	uint8_t button3 = 0;

	uint8_t button1_p = 0;
	uint8_t button2_p = 0;
	uint8_t button3_p = 0;
	//uint8_t button_p;

	while(1)	//boucle de t�che de fond
	{
		//button_p = 1;
		//button = HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
		if (i== 10000){
			//Remplir_Jauge(cnt*50);
			cnt++;
			if (cnt>19)
				cnt = 0;
			i=0;
		}
		button1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
		//if (button1!=button1_p)
			debug_printf("button = %d \n",button1);

		button1_p = button1;
		i++;
		/*if (!button){
			while (!button){
				//infrar = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
				button = HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);

			}
			debug_printf("cnt*100 : %d",cnt*100);
			Remplir_Jauge(cnt*50);
			cnt++;

			if (cnt>19)
				cnt = 0;
		}*/


	}
}
