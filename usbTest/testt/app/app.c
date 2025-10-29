#include "app.h"
#include <stdint.h>


uint32_t USB_CDC_recieve_data(uint16_t length){
	uint8_t *data = EndPoint[1].rxBuffer_ptr;
	uint8_t data1[100];
	for(uint32_t i = 0; i < length; i++){
		data1[i] = data[i];
	}
	
	
	USB_CDC_send_data(data1, length);
	return length;
}

int main ()
{
	
//	RCC_MCO_Connect(MCO1, RCC_MCO1_MUX_PLLCLK, RCC_MCO_DIV_1);/*Configure GPIO pin : PA8 */
//	RCC_MCO_Connect(MCO2, RCC_MCO2_MUX_SYSCLK, RCC_MCO_DIV_1);/*Configure GPIO pin : PC9 */
	

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


  AHB2_ENABLE_PERIPHERY(RCC_AHB2ENR_OTGFSEN);//включим OTGFS

	
	__disable_irq ();

	
	USB_Init_GPIO();
	
	//USB_Init_Registr();
	USB_OTG_FS_init_device();

	__enable_irq ();
	


	while(1)
	{
		ODR_Xor(&LED_7);
		delay_ms(100);
	}
	
	return 0;
}


/*
Используйте функцию EndPoint[1].rxCallBack для обработки данных, поступающих с хоста (терминала COM-порта).

Используйте функцию EndPoint[1].setTxBuffer, чтобы задать и отправить данные, которые вы хотите отправить на хост.

Отредактируйте файл usb_cdc_desc.h, если хотите использовать дескрипторы, отличные от тех, что приведены в примере STM HAL.
*/


