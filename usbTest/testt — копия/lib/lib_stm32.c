#include "lib_stm32.h"

/*-----------------------------------------------------------------------------------------------*/
/*Спец.функции RCC - вывод частот на PA8 и PC9 (MCO)*/
void RCC_MCO_Connect(type_MCO_t MCOx, uint32_t RCC_MCO_MUXx, uint32_t RCC_MCO_DIV_x)
{

  if (MCOx == MCO1)
    {
      uint32_t temp_MCO1;
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);

      /*Configure GPIO pin : PA8 */
      GPIO_Structure MCO1 = {.GPIOx = GPIOA, .Pin = PIN8, .Mode = GPIO_MODE_AF, .Pull = GPIO_PUPDR_NOPULL,
                             .Otyper = GPIO_OTYPER_PUSHPULL, .Speed = GPIO_SPEED_HIGH, .Alternate = GPIO_AF0
                            };
      GPIO_Init(&MCO1);

      temp_MCO1 = (READ_REG(RCC->CFGR) & (~RCC_CFGR_MCO1)) | RCC_MCO_MUXx;
      Write_REG(RCC->CFGR, temp_MCO1);

      temp_MCO1 = (READ_REG(RCC->CFGR) & (~RCC_CFGR_MCO1PRE)) | RCC_MCO_DIV_x;
      Write_REG(RCC->CFGR, temp_MCO1);

    }

  if (MCOx == MCO2)
    {
      uint32_t temp_MCO2;
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);

      /*Configure GPIO pin : PC9 */
      GPIO_Structure MCO2 = {.GPIOx = GPIOC, .Pin = PIN9, .Mode = GPIO_MODE_AF, .Pull = GPIO_PUPDR_NOPULL,
                             .Otyper = GPIO_OTYPER_PUSHPULL, .Speed = GPIO_SPEED_HIGH, .Alternate = GPIO_AF0
                            };
      GPIO_Init(&MCO2);

      temp_MCO2 = (READ_REG(RCC->CFGR) & (~RCC_CFGR_MCO2)) | RCC_MCO_MUXx;/**/
      Write_REG(RCC->CFGR, temp_MCO2);/**/

      temp_MCO2 = (READ_REG(RCC->CFGR) & (~RCC_CFGR_MCO2PRE)) | RCC_MCO_DIV_x << 3U;
      Write_REG(RCC->CFGR, temp_MCO2);

    }
}
/*-----------------------------------------------------------------------------------------------*/
