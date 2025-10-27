#include "app.h"

int main ()
{
	
	RCC_MCO_Connect(MCO1, RCC_MCO1_MUX_PLLCLK, RCC_MCO_DIV_1);/*Configure GPIO pin : PA8 */
	RCC_MCO_Connect(MCO2, RCC_MCO2_MUX_SYSCLK, RCC_MCO_DIV_1);/*Configure GPIO pin : PC9 */
	

	AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);/*LED2 PA6,LED3 PA7*/
	GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Pull = GPIO_PUPDR_PULLUP};
	GPIO_Init(&LED_7);
	
	RCC_Oscillator_t osc;
	osc.HSE_State = RCC_HSE_ON;
	osc.HSE_Frequence = 8000000;
	osc.HSI_State = RCC_HSI_ON;
	osc.HSI_CalibrationValue = 30;
	osc.LSI_State = RCC_LSI_ON;
	
	RCC_Oscillator_Init(&osc);

	RCC_PLL_t pll;
	pll.PLL_State = RCC_PLL_ON;
	pll.PLL_Sourse = RCC_PLLSOURCE_HSE;//HSI 1-1,HSE 1-3
	pll.PLL_M = 4;
	pll.PLL_N = 168;
	pll.PLL_P = 2;
	pll.PLL_Q = 7;
	
	RCC_PLL_Init(&pll);
	
	RCC_Sysclk_t sysclk;
	sysclk.SYSCLK_Sourse = RCC_SYSCLK_SOURCE_PLL;
	sysclk.AHB_Divider = RCC_AHB_DIV1;
		
	RCC_Sysclk_Init(&sysclk, &osc, &pll);

	while(1)
	{
		ODR_Xor(&LED_7);
		delay_ms(500);
	}
	
	return 0;
}