#ifndef LIB_STM32_H_
#define LIB_STM32_H_

/*-----------------------------------------------------------------------------------------------*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "GPIO_STM32F407.h"/*для спец.функций*/

/*-----------------------------------------------------------------------------------------------*/
/*Битовые операции*/
#define Enable_BIT(reg, bit)	(reg |= (uint32_t)(bit))
#define Disable_BIT(reg, bit)	(reg &= ~(uint32_t)(bit))
#define Read_BIT(reg, bit)	((reg) & (bit))

/*Регистовые операции*/
#define Write_REG(REG, VAL)	((REG) = (VAL))
#define Read_REG(REG)	((REG))
#define Clear_REG(REG)	((REG) = (0))
#define Modify_REG(REG, OLD_BIN, NEW_BIT)	(Write_REG((REG), (((Read_REG(REG)) & (~(OLD_BIN))) | (NEW_BIT))))
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Вкл. периферии*/
#define AHB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->AHB1ENR |= _RCC_PERIPHERY_)/*вкл что то по AHB1*/
#define APB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB1ENR |= _RCC_PERIPHERY_)/*вкл что то по APB1*/
#define APB2_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB2ENR |= _RCC_PERIPHERY_)/*вкл что то по APB2*/
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Спец.функции RCC - вывод частот на PA8 и PC9 (MCO)*/

/*Выбор канала коммутатора*/
#define RCC_MCO1_MUX_HSI (0)
#define RCC_MCO1_MUX_LSE (RCC_CFGR_MCO1_0)
#define RCC_MCO1_MUX_HSE (RCC_CFGR_MCO1_1)
#define RCC_MCO1_MUX_PLLCLK (RCC_CFGR_MCO1)

#define RCC_MCO2_MUX_SYSCLK (0)
#define RCC_MCO2_MUX_PLLI2SCLK (RCC_CFGR_MCO2_0)
#define RCC_MCO2_MUX_HSE (RCC_CFGR_MCO2_1)
#define RCC_MCO2_MUX_PLLCLK (RCC_CFGR_MCO2)

/*Выбор деления на 1-5*/
#define RCC_MCO_DIV_1 (0)
#define RCC_MCO_DIV_2 (RCC_CFGR_MCO1PRE_2)
#define RCC_MCO_DIV_3 (RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCO_DIV_4 (RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCO_DIV_5 (RCC_CFGR_MCO1PRE)

typedef enum
{
  MCO1,
  MCO2,
} type_MCO_t;

void RCC_MCO_Connect(type_MCO_t MCOx, uint32_t RCC_MCO_MUXx, uint32_t RCC_MCO_DIV_x);
/*-----------------------------------------------------------------------------------------------*/

#endif