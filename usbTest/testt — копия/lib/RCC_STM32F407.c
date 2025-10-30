#include "RCC_STM32F407.h"
/*-----------------------------------------------------------------------------------------------*/

RCC_Status_t RCC_Oscillator_Init(RCC_Oscillator_t *osc)
{
  uint32_t tick = 0;

  /*------------------------------- HSE Configuration ------------------------*/
  if ((osc->HSE_State == RCC_HSE_ON) || (osc->HSE_State == RCC_HSE_BYPASS))
    {
      /*Если используем BYPASS*/
      if (osc->HSE_State == RCC_HSE_BYPASS)
        {
          Enable_BIT(RCC->CR, RCC_CR_HSEBYP);/*включим BYPASS*/
          Enable_BIT(RCC->CR, RCC_CR_HSEON);/*включим HSE*/
        }
				
      Enable_BIT(RCC->CR, RCC_CR_HSEON);/*включим HSE*/

      /* Проверка состояния HSE */
      if ((osc->HSE_State) != RCC_HSE_OFF)
        {
          /* Подождите, пока HSE будет готова */
          tick = 0;

          while (Read_BIT(RCC->CR, RCC_CR_HSERDY) == 0)
            {
              tick++;

              if (tick > 25000)
                {
                  return RCC_Error_Time;
                }
            }
        }
    }

  else
    {
      Disable_BIT(RCC->CR, RCC_CR_HSEON);/*отключим HSE*/
      Disable_BIT(RCC->CR, RCC_CR_HSEBYP);/*отключим BYPASS*/
    }

  /*----------------------------- HSI Configuration --------------------------*/
  if (osc->HSI_State == RCC_HSI_ON)
    {
      /*Установим калибровку */
      if (osc->HSI_CalibrationValue == 0)
        {
          osc->HSI_CalibrationValue = 10U;//10U - калибровка в дефолте,0 and 0x1F
        }

      if (osc->HSI_CalibrationValue != 0)
        {
          Modify_REG(RCC->CR, RCC_CR_HSITRIM, osc->HSI_CalibrationValue << RCC_CR_HSITRIM_Pos);
        }

      Enable_BIT(RCC->CR, RCC_CR_HSION);/*включим HSI*/

      /* Подождите, пока HSI будет готова */
      tick = 0;

      while (Read_BIT(RCC->CR, RCC_CR_HSIRDY) == 0)
        {
          tick++;

          if (tick > 25000)
            {
              return RCC_Error_Time;
            }
        }
    }
  else
    {
      Disable_BIT(RCC->CR, RCC_CR_HSION);/*отключим HSI*/
    }

  /*------------------------------ LSI Configuration -------------------------*/
  if (osc->LSI_State == RCC_LSI_ON)
    {

      Enable_BIT(RCC->CSR, RCC_CSR_LSION);/*включим LSI*/

      /* Подождите, пока LSI будет готова */
      tick = 0;

      while (Read_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0)
        {
          tick++;

          if (tick > 45000)
            {
              return RCC_Error_Time;
            }
        }
    }
  else
    {
      Disable_BIT(RCC->CSR, RCC_CSR_LSION);/*отключим LSI*/
    }

  /*------------------------------ LSE Configuration -------------------------*/
  if ((osc->LSE_State == RCC_LSE_ON) || (osc->LSE_State == RCC_LSE_BYPASS))
    {
      Enable_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
      Enable_BIT(PWR->CR, PWR_CR_DBP);

      /*Если используем BYPASS*/
      if (osc->LSE_State == RCC_LSE_BYPASS)
        {
          Enable_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);/*включим BYPASS*/
          Enable_BIT(RCC->BDCR, RCC_BDCR_LSEON);/*включим LSE*/
        }

      Enable_BIT(RCC->BDCR, RCC_BDCR_LSEON);/*включим LSE*/

      /* Проверка состояния LSE */
      if ((osc->LSE_State) != RCC_LSE_OFF)
        {
          /* Подождите, пока LSE будет готова */
          tick = 0;

          while (Read_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0)
            {
              tick++;

              if (tick > 45000)
                {
                  return RCC_Error_Time;
                }
            }
        }

      Disable_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    }

  else
    {
      Disable_BIT(RCC->BDCR, RCC_BDCR_LSEON);/*отключим LSE*/
      Disable_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);/*отключим BYPASS*/
    }

  return RCC_Ok;
}

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
RCC_Status_t RCC_PLL_Init(RCC_PLL_t *pll)
{
  if (pll->PLL_State == RCC_PLL_ON)
    {
      uint32_t tick = 0;

      Disable_BIT(RCC->CR, RCC_CR_PLLON);/*отключим PLL для настроек*/

      /*подождем отключение PLL*/
      while (Read_BIT(RCC->CR, RCC_CR_PLLRDY) == 1)
        {
          tick++;

          if (tick > 20000)
            {
              return RCC_Error_Time;
            }
        }

      /*проверим структуру на 0 заполнение*/
      if (pll->PLL_M == 0) 
        {
          pll->PLL_M = 2;
        }

      if (pll->PLL_N == 0)
        {
          pll->PLL_M = 50;
        }

      if (pll->PLL_P == 0)
        {
          pll->PLL_P = 2;
        }

      if (pll->PLL_Q == 0)
        {
          pll->PLL_Q = 2;
        }
				
      /*пишем в регистр*/
      Write_REG(RCC->PLLCFGR, (pll->PLL_Sourse | pll->PLL_M | (pll->PLL_N << RCC_PLLCFGR_PLLN_Pos) | (((pll->PLL_P >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos)) | (pll->PLL_Q << RCC_PLLCFGR_PLLQ_Pos));

      Enable_BIT(RCC->CR, RCC_CR_PLLON);/*включим PLL*/

      /*подождем включение PLL*/
      while (Read_BIT(RCC->CR, RCC_CR_PLLRDY) == 0)
        {
          tick++;

          if (tick > 20000)
            {
              return RCC_Error_Time;
            }
        }
				
    }

  return RCC_Ok;
}

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Выбор источника SYSCLK и ее деление(настройка AHB)*/
RCC_Status_t RCC_Sysclk_Init(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll)
{
	if(Set_Latency(sysclk, osc, pll) != RCC_Ok)
	{
		return RCC_Error;
	}
	
	if(Connect_SYSCLK_Sourse(sysclk) != RCC_Ok)
	{
		return RCC_Error;
	}
	
	/*обновим переменую SystemCoreClock*/
	SystemCoreClockUpdate();
	
	if(Set_AHB(sysclk) != RCC_Ok)
	{
		return RCC_Error;
	}

	return RCC_Ok;
}

/*Выбор источника SYSCLK*/
RCC_Status_t Connect_SYSCLK_Sourse(RCC_Sysclk_t *sysclk)
{
	  uint32_t tick = 0;

  if (sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_HSI)
    {
			
      Write_REG(RCC->CFGR, RCC_SYSCLK_SOURCE_HSI);

      while (Read_BIT(RCC->CFGR, RCC_CFGR_SWS_HSI) == 0)
        {
          tick++;

          if (tick > 5000)
            {
              return RCC_Error_Time;
            }
        }
    }
  else if (sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_HSE)
    {
      Write_REG(RCC->CFGR, RCC_SYSCLK_SOURCE_HSE);

      while (Read_BIT(RCC->CFGR, RCC_CFGR_SWS_HSE) == 0)
        {
          tick++;

          if (tick > 5000)
            {
              return RCC_Error_Time;
            }
        }
    }
  else if (sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_PLL)
    {
			RCC->CFGR &= ~RCC_CFGR_SW;
      Write_REG(RCC->CFGR, RCC_SYSCLK_SOURCE_PLL);

      while (Read_BIT(RCC->CFGR, RCC_CFGR_SWS_PLL) == 0)
        {
          tick++;

          if (tick > 5000)
            {
              return RCC_Error_Time;
            }
        }
    }
		
	return RCC_Ok;
}

/*Настройка шин(AHB)*/
RCC_Status_t Set_AHB(RCC_Sysclk_t *sysclk)
{
		/*-------------------------- HCLK Configuration --------------------------*/
		if(sysclk->AHB_Divider != 0)
		{
			Modify_REG(RCC->CFGR, RCC_CFGR_HPRE, sysclk->AHB_Divider);
		}
		else
		{
			sysclk->AHB_Divider = RCC_AHB_DIV1;
			Modify_REG(RCC->CFGR, RCC_CFGR_HPRE, sysclk->AHB_Divider);
		}
		
	/*-------------------------- PCLK1 Configuration ---------------------------*/	
		if(sysclk->APB1_Divider != 0)
		{
			Modify_REG(RCC->CFGR, RCC_CFGR_PPRE1, sysclk->APB1_Divider);
		}
		else
		{
			sysclk->APB1_Divider= RCC_APB1_DIV1;
			Modify_REG(RCC->CFGR, RCC_CFGR_PPRE1, sysclk->APB1_Divider);
		}
		
	/*-------------------------- PCLK2 Configuration ---------------------------*/
	  if(sysclk->APB2_Divider != 0)
		{
			Modify_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((sysclk->APB2_Divider) << 3U));
		}
		else
		{
			sysclk->APB2_Divider= RCC_APB2_DIV1;
			Modify_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((sysclk->APB2_Divider) << 3U));
		}
		
  return RCC_Ok;
}

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Выбор латенсии (коэфицент пропуска тактовой частоты для флеш)*/
/*Установим латенсию*/
RCC_Status_t Set_Latency(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll)
{
	uint32_t _calculated_frequence;
	uint32_t *calculated_frequence = &_calculated_frequence;
	
	if(Calculated_Frequence(sysclk,osc,pll,calculated_frequence) != RCC_Ok)
	{
		return RCC_Error;
	}
	
	uint32_t temp_latency;
	
	if(_calculated_frequence <= 30000000)
	{
		temp_latency = FLASH_ACR_LATENCY_0WS;
	}
	else if(_calculated_frequence <= 60000000)
	{
		temp_latency = FLASH_ACR_LATENCY_1WS;
	}
	else if(_calculated_frequence <= 90000000)
	{
		temp_latency = FLASH_ACR_LATENCY_2WS;
	}
	else if(_calculated_frequence <= 120000000)
	{
		temp_latency = FLASH_ACR_LATENCY_3WS;
	}
	else if(_calculated_frequence <= 150000000)
	{
		temp_latency = FLASH_ACR_LATENCY_4WS;
	}
	else if(_calculated_frequence <= 168000000)
	{
		temp_latency = FLASH_ACR_LATENCY_5WS;
	}
	else
	{
		return RCC_Error;
	}
	
	FLASH->ACR |= temp_latency; /*настроим регистр флеш*/
	
	return RCC_Ok;
}

/*Расчитаем расчетную частоту SysClk*/
RCC_Status_t Calculated_Frequence(RCC_Sysclk_t *sysclk, RCC_Oscillator_t *osc, RCC_PLL_t *pll,uint32_t *calculated_frequence)
{
	if(sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_HSI)
	{
		*calculated_frequence = HSI_Freq;
	}
	else if(sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_HSE)
	{
		*calculated_frequence = osc->HSE_Frequence;
	}
	else if(sysclk->SYSCLK_Sourse == RCC_SYSCLK_SOURCE_PLL)
	{
		if(pll->PLL_Sourse == RCC_PLLSOURCE_HSI)
		{
			uint32_t trmpHSI = HSI_Freq;
			trmpHSI = trmpHSI / pll->PLL_M;
			trmpHSI = trmpHSI * pll->PLL_N;
			trmpHSI = trmpHSI / pll->PLL_P;
			*calculated_frequence = trmpHSI;
		}
		else if(pll->PLL_Sourse == RCC_PLLSOURCE_HSE)
		{
			uint32_t trmpHSE = osc->HSE_Frequence;
			trmpHSE = trmpHSE / pll->PLL_M;
			trmpHSE = trmpHSE * pll->PLL_N;
			trmpHSE = trmpHSE / pll->PLL_P;
			*calculated_frequence = trmpHSE;
		}
	}
	else
	{
		return RCC_Error;
	}
	
	return RCC_Ok;
}

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*Настройка delay*/

int count = 0;

void delay_us(int us)
{
    if (us > US_MAX_VALUE || us == 0)
    {
        return;
    }
	
		Enable_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);/*разрешить прерывания по достижении 0*/
		Disable_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);/*запретить прерывания по достижении 0*/

		Enable_BIT(SysTick->CTRL,SysTick_CTRL_CLKSOURCE_Msk);/*ставим тактирование от процессора*/
    Write_REG(SysTick->LOAD,(US * us - 1));/*устанавливаем в регистр число от которого считать*/
    Clear_REG(SysTick->VAL); /*обнуляем текущее значение регистра SYST_CVR*/

    Enable_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Msk);/*запускаем счетчик*/

		while (!(Read_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Msk)))/*ждем установку флага COUNFLAG в регистре SYST_CSR*/
    {
    }

		Disable_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Msk);/*скидываем бит COUNTFLAG*/
		Disable_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Msk);/*выключаем счетчик*/
}

void delay_ms(int ms)
{
    for (int i = 0; i < ms; i++)
    {
        delay_us(1000);
    }
}

void delay_s(int s)
{
    for (int i = 0; i < s; i++)
    {
        delay_ms(1000);
    }
}

void SysTick_Handler(void)/*Обработчик прерывания SysTick*/
{
    // count++;
}