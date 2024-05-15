
#include "stm32f1_uart.h"

#include "tft_ili9341/stm32f1_ili9341.h"
#include "stm32f1_gpio.h"


void Init_Jauge(){
	uint16_t jauge_x0 = 281;
	uint16_t jauge_x1 = 301;
	uint16_t jauge_y0 = 31;
	uint16_t jauge_y1 = 211;
	uint16_t rapport = (jauge_y1 - jauge_y0) / 4;

	uint32_t c0 = ILI9341_COLOR_GREEN;
	uint32_t c1 = ILI9341_COLOR_YELLOW;
	uint32_t c2 = ILI9341_COLOR_ORANGE;
	uint32_t c3 = ILI9341_COLOR_RED;

	ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 0* rapport, jauge_x1, jauge_y0 + 1* rapport, c3 );
	ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 1* rapport, jauge_x1, jauge_y0 + 2* rapport, c2 );
	ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 2* rapport, jauge_x1, jauge_y0 + 3* rapport, c1 );
	ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 3* rapport, jauge_x1, jauge_y0 + 4* rapport, c0 );
	ILI9341_Puts(200,190, "vitesse", &Font_11x18, ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);

}


void Remplir_Jauge(uint16_t vitesse){
	//debug_printf("vitesse : %d \n", vitesse);
	static uint16_t jauge_precedent = 0;
	uint16_t jauge_x0 = 260;
	uint16_t jauge_x1 = 280;
	uint16_t jauge_y0 = 30;
	uint16_t jauge_y1 = 210;
	uint16_t v = vitesse;

	uint16_t vMax = 1000;// a modifier pour les vitesses
	//uint16_t rapport = (jauge_y1 - jauge_y0) / 4;
	float jauge_actu = ((float)v/vMax);
	jauge_actu = jauge_y1 -( jauge_actu * (jauge_y1-jauge_y0));//pour mettre la vitesse/vMax sur 210-30

	ILI9341_DrawLine(jauge_x0,jauge_precedent, jauge_x1, jauge_precedent, ILI9341_COLOR_WHITE );
	ILI9341_DrawLine(jauge_x0,jauge_actu, jauge_x1, jauge_actu, ILI9341_COLOR_BLACK );

	ILI9341_printf(100,100,&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE,"vitesse : %d \n jauge : %d \n",v, jauge_actu );

	jauge_precedent = jauge_actu ;
	//debug_printf("affich\n");

/*(jauge_actu >jauge_y0 + 2 * dy) ? ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0, jauge_x1, jauge_actu,c0 ) : ILI9341_DrawFilledRectangle(jauge_x0, 2 * jauge_y0, jauge_x1, jauge_actu,c0);
	(jauge_actu > jauge_y0 + 4 * dy) ? ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 1* rapport, jauge_x1, jauge_actu,c4 ) : ILI9341_DrawFilledRectangle(jauge_x0, 2 * jauge_y0, jauge_x1, jauge_actu,c2 );
	(jauge_actu > jauge_y0 + 5 * dy) ? ILI9341_DrawFilledRectangle(jauge_x0, jauge_y0 + 1* rapport, jauge_x1, jauge_actu,c5 ) : ILI9341_DrawFilledRectangle(jauge_x0, 2 * jauge_y0, jauge_x1, jauge_actu,c3 );
	*/
	/*if (pourcentage  > 3)
		ILI9341_DrawFilledRectangle(jauge_x0,
									(jauge_actu < jauge_y0 + rapport)? jauge_actu : jauge_y0+rapport,
									jauge_x1,
									jauge_y1,
									c0);

	/*if (jauge_actu > 3 * rapport + jauge_y0)
		ILI9341_DrawFilledRectangle(jauge_x0, 4* jauge_y0, jauge_x1, jauge_actu,c3 );

	if (jauge_actu > 4 * rapport + jauge_y0)
			ILI9341_DrawFilledRectangle(jauge_x0, 4* jauge_y0, jauge_x1, jauge_actu,c3 );

	if (jauge_actu > 5 * rapport + jauge_y0)
			ILI9341_DrawFilledRectangle(jauge_x0, 5* jauge_y0, jauge_x1, jauge_actu,c4 );

	if (jauge_actu > 6 * dy)
			ILI9341_DrawFilledRectangle(jauge_x0, 6* jauge_y0, jauge_x1, jauge_actu,c5 );*/



}

