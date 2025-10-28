#ifndef RCC_STM32F407_H_
#define RCC_STM32F407_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "lib_stm32.h"

/*
Настройка RCC
1. Заполним структуру RCC_Oscillator_t - укажем какие источники генерации нужны
2. Заполним структуру RCC_PLL_t - укажем настройку PLL
3. Заполним структуру
*/

/*-----------------------------------------------------------------------------------------------*/
/*Ошибки RCC*/
typedef enum
{
	RCC_Ok = 0U,
	RCC_Error = 1U,
	RCC_Error_Time = 2U,
	
} RCC_Status_t;

static uint32_t debug_data;
static uint32_t debug_tick;
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Подключим источник частоты*/

/*HSE - Внешний кварц 4-26Мгц*/
#define RCC_HSE_OFF (0U) /*Отключен внешний кварц*/
#define RCC_HSE_ON (RCC_CR_HSEON) /*Подключен внешний кварц*/
#define RCC_HSE_BYPASS ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))/*Отключен внешний кварц, но подключена внешнея синхра*/

/*HSI - Внутрений кварц 16Мгц*/
#define RCC_HSI_OFF ((uint8_t)0x00)/*Отключен внутрений кварц*/
#define RCC_HSI_ON ((uint8_t)0x01)/*Подключен внутрений кварц*/
#define HSI_Freq (16000000)/*Подключен внутрений кварц*/

/*LSE - Внешний часовой кварц 32.768Кгц*/
#define RCC_LSE_OFF (0U) /*Отключен внешний часовой кварц*/
#define RCC_LSE_ON (RCC_BDCR_LSEON) /*Подключен внешний часовой кварц*/
#define RCC_LSE_BYPASS ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))/*Отключен внешний часовой кварц, но подключена внешнея синхра*/

/*LSI - Внутрений часовой кварц 32Кгц*/
#define RCC_LSI_OFF ((uint8_t)0x00)/*Отключен внутрений часовой кварц*/
#define RCC_LSI_ON ((uint8_t)0x01)/*Подключен внутрений часовой кварц*/

typedef struct
{
  uint32_t HSE_State; /*RCC_HSE_ON/RCC_HSE_OFF*/
	uint32_t HSE_Frequence; /*Указать частоту кварца*/
  uint32_t LSE_State; /*RCC_LSE_ON/RCC_LSE_OFF*/
  uint32_t HSI_State; /*RCC_HSI_ON/RCC_HSI_OFF*/
  uint32_t HSI_CalibrationValue; /*Значение подстройки калибровки HSI (по умолчанию RCC_HSICALIBRATION_DEFAULT).
																			Этот параметр должен быть числом в диапазоне от Min_Data = 0x00 до Max_Data = 0x1F */
  uint32_t LSI_State; /*RCC_LSI_ON/RCC_LSI_OFF*/

} RCC_Oscillator_t;

RCC_Status_t RCC_Oscillator_Init(RCC_Oscillator_t *osc);
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Подключим PLL*/

/*Варианты включения PLL*/
#define RCC_PLL_NONE (0x00) /*Нет PLL*/
#define RCC_PLL_OFF (0x01) /*Отключен PLL*/
#define RCC_PLL_ON (0x02) /*Подключен PLL*/

/*Источник сигнала PLL*/
#define RCC_PLLSOURCE_HSI RCC_PLLCFGR_PLLSRC_HSI /*Коммутатор входного сигнала для PLL - внутрений кварц*/
#define RCC_PLLSOURCE_HSE RCC_PLLCFGR_PLLSRC_HSE /*Коммутатор входного сигнала для PLL - внешний кварц*/

typedef struct
{
  uint32_t PLL_State; /*RCC_PLL_NONE/RCC_PLL_OFF/RCC_PLL_ON*/
  uint32_t PLL_Sourse; /*RCC_PLLSOURCE_HSI/RCC_PLLSOURCE_HSE*/
  uint32_t PLL_M; /*!< M-делитель (общий для PLL) от Min_Data = 0 до Max_Data = 63 */
	uint32_t PLL_N; /*!< N-умножитель PLL от Min_Data = 50 до Max_Data = 432. За исключением устройств STM32F411xE, для которых Min_Data = 192 */
	uint32_t PLL_P; /*!< P-делитель(для основного системного тактового сигнала SYSCLK или PLLCLK) 2,4,6,8*/
	uint32_t PLL_Q; /*!< Q-делитель для тактовых сигналов OTG FS, SDIO, RNG, USB от Min_Data = 2 до Max_Data = 15 */

} RCC_PLL_t;

RCC_Status_t RCC_PLL_Init(RCC_PLL_t *pll);
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Выбор источника SYSCLK и ее деление(настройка AHB)*/

/*Источники для SYSCLK*/
#define RCC_SYSCLK_SOURCE_HSI	(RCC_CFGR_SW_HSI)
#define RCC_SYSCLK_SOURCE_HSE	(RCC_CFGR_SW_HSE)
#define RCC_SYSCLK_SOURCE_PLL	(RCC_CFGR_SW_PLL)

/*Делим SYSCLK для получения основной шины AHB(HCLK)*/
#define RCC_AHB_DIV1 (RCC_CFGR_HPRE_DIV1)
#define RCC_AHB_DIV2 (RCC_CFGR_HPRE_DIV2)
#define RCC_AHB_DIV4 (RCC_CFGR_HPRE_DIV4)
#define RCC_AHB_DIV8 (RCC_CFGR_HPRE_DIV8)
#define RCC_AHB_DIV16 (RCC_CFGR_HPRE_DIV16)
#define RCC_AHB_DIV64 (RCC_CFGR_HPRE_DIV64)
#define RCC_AHB_DIV128 (RCC_CFGR_HPRE_DIV128)
#define RCC_AHB_DIV256 (RCC_CFGR_HPRE_DIV256)
#define RCC_AHB_DIV512 (RCC_CFGR_HPRE_DIV512)

/*Делим AHB(HCLK) для получения шины APB1(PCLK1)*/
#define RCC_APB1_DIV1 (RCC_CFGR_PPRE1_DIV1)
#define RCC_APB1_DIV2 (RCC_CFGR_PPRE1_DIV2) 
#define RCC_APB1_DIV4 (RCC_CFGR_PPRE1_DIV4) 
#define RCC_APB1_DIV8 (RCC_CFGR_PPRE1_DIV8) 
#define RCC_APB1_DIV16 (RCC_CFGR_PPRE1_DIV16)

/*Делим AHB(HCLK) для получения шины APB2(PCLK2)*/
#define RCC_APB2_DIV1 (RCC_CFGR_PPRE2_DIV1) 
#define RCC_APB2_DIV2 (RCC_CFGR_PPRE2_DIV2)
#define RCC_APB2_DIV4 (RCC_CFGR_PPRE2_DIV4) 
#define RCC_APB2_DIV8 (RCC_CFGR_PPRE2_DIV8) 
#define RCC_APB2_DIV16 (RCC_CFGR_PPRE2_DIV16)


typedef struct
{
  uint32_t SYSCLK_Sourse; /*RCC_SYSCLK_SOURCE_HSI/RCC_SYSCLK_SOURCE_HSE/RCC_SYSCLK_SOURCE_PLLCLK*/
  uint32_t AHB_Divider; /*Делитель SYSCLK для получения основной шины AHB(HCLK)*/
	uint32_t APB1_Divider; /*Делим AHB(HCLK) для получения шины APB1(PCLK1)*/
	uint32_t APB2_Divider; /*Делим AHB(HCLK) для получения шины APB2(PCLK2)*/

} RCC_Sysclk_t;

RCC_Status_t RCC_Sysclk_Init(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll);/**/
RCC_Status_t Connect_SYSCLK_Sourse(RCC_Sysclk_t *sysclk);/*Выбор источника SYSCLK*/
RCC_Status_t Set_AHB(RCC_Sysclk_t *sysclk);/*Настройка шин(AHB)*/

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Выбор латенсии (коэфицент пропуска тактовой частоты для флеш)*/
/*
| Частота ядра | Циклы ожидания |
| ------------ | -------------- |
|  До 30 МГц   |      0 WS      |
|  До 60 МГц   |      1 WS      |
|  До 90 МГц   |      2 WS      |
|  До 120 МГц  |      3 WS      |
|  До 150 МГц  |      4 WS      |
|  До 168 МГц  |      5 WS      |
|  спец        |      6 WS      |
|  спец        |      7 WS      |
*/

RCC_Status_t Set_Latency(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll);/*Установим латенсию*/
RCC_Status_t Calculated_Frequence(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll,uint32_t *calculated_frequence);/*Расчитаем расчетную частоту SysClk*/
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Настройка delay*/
#define US (SystemCoreClock / 1000000)
#define SYSTICK_MAX_VALUE (16777215) /*max = 168МГц*/
#define US_MAX_VALUE (SYSTICK_MAX_VALUE / (US))

void delay_us(int us);
void delay_ms(int ms);
void delay_s(int s);

/*-----------------------------------------------------------------------------------------------*/

#endif