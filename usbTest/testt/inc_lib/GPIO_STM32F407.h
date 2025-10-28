#ifndef GPIO_STM32F407_H_
#define GPIO_STM32F407_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "lib_stm32.h"

/*defaines*/

/*
Когда порт ввода/вывода запрограммирован как вход:
• выходной буфер отключается
• вход триггера Шмитта активируется
• подтягивающие резисторы активируются в зависимости от значения в
регистре GPIOx_PUPDR
• Данные, присутствующие на выводе ввода/вывода, считываются в регистр входных данных каждый такт AHB1
• Доступ к регистру входных данных для чтения предоставляет состояние ввода/вывода
*/

/*
Когда порт ввода/вывода запрограммирован как выход:
• Выходной буфер включен:
– Режим открытого стока: «0» в выходном регистре активирует N-МОП-транзистор, тогда как «1»
в выходном регистре оставляет порт в состоянии Hi-Z (P-МОП-транзистор никогда не активируется).
– Двухтактный режим: «0» в выходном регистре активирует N-МОП-транзистор, тогда как «1»
в выходном регистре активирует P-МОП-транзистор.
• Активируется вход триггера Шмитта.
• Слаботочные подтягивающие резисторы (подтягивающие к земле) и к земле активируются или нет в зависимости от значения
в регистре GPIOx_PUPDR.
• Данные, присутствующие на выводе ввода/вывода, считываются во входной регистр данных каждый
такт AHB1.
• Доступ к входному регистру данных для чтения возвращает состояние ввода/вывода.
• Доступ к выходному регистру данных для чтения возвращает последнее записанное значение.
*/

/*
Когда порт ввода/вывода запрограммирован на альтернативную функцию:
• Выходной буфер может быть сконфигурирован как с открытым стоком или двухтактный
• Выходной буфер управляется сигналом, поступающим от периферийного устройства (разрешение передатчика
и данные)
• Активируется вход триггера Шмитта
• Слаботочные подтягивающие резисторы вверх и вниз активируются или нет в зависимости от значения
в регистре GPIOx_PUPDR
• Данные, присутствующие на выводе ввода/вывода, считываются во входной регистр данных каждый такт AHB1
• Доступ к чтению входного регистра данных позволяет получить состояние ввода/вывода
*/

/*
Когда порт ввода/вывода запрограммирован как аналоговый:
• Выходной буфер отключается
• Вход триггера Шмитта деактивируется, обеспечивая нулевое потребление для каждого аналогового
значения на выводе ввода/вывода. Выход триггера Шмитта принудительно устанавливается на постоянное значение (0).
• Слаботочные подтягивающие резисторы вверх и вниз отключаются
• Доступ к регистру входных данных при чтении получает значение «0»
*/

/*RM0090 Reference manual STM32F405/415, STM32F407/417, STM32F427/437 and STM32F429/439*/
/*8.4 GPIO registers*/
/*8.4.1 Регистр режимов (GPIOx_MODER) (x = A..I/J/K) Address offset: 0x00*/
#define GPIO_MODE_INPUT (0U) /*Input (reset state)*/
#define GPIO_MODE_OUTPUT (1U) /*General purpose output mode*/
#define GPIO_MODE_AF (2U) /*Alternate function mode*/
#define GPIO_MODE_ANALOG (3U) /*Analog mode*/

/*8.4.2 Регистр типа выхода порта GPIO (GPIOx_OTYPER)(x = A..I/J/K) Address offset: 0x04*/
#define GPIO_OTYPER_PUSHPULL (0U) /*Output push-pull (reset state)*/
#define GPIO_OTYPER_OPENDRAIN (1U) /*Output open-drain*/

/*8.4.3 GPIO port output speed register (GPIOx_OSPEEDR)(x = A..I/J/K) Address offset: 0x08*/
#define GPIO_SPEED_LOW (0U) /* Low speed*/
#define GPIO_SPEED_MEDIUM (1U) /*Medium speed*/
#define GPIO_SPEED_HIGH (2U) /*High speed*/
#define GPIO_SPEED_VERY_HIGH (3U) /*AVery high speed*/

/*8.4.4 Регистр подтягивания(pull-up)/опускания(pull-down) порта GPIO (GPIOx_PUPDR)(x = A..I/J/K) Address offset: 0x0C*/
#define GPIO_PUPDR_NOPULL (0U) /* No pull-up, pull-down*/
#define GPIO_PUPDR_PULLUP (1U) /*Pull-up*/
#define GPIO_PUPDR_PULLDOWN (2U) /*Pull-down*/

/*8.4.5 Регистр входных данных порта GPIO (GPIOx_IDR) (x = A..I/J/K) Address offset: 0x10*/
/*Эти биты доступны только для чтения и доступны только в режиме слова. Они содержат входное значение соответствующего порта ввода/вывода.*/
//#define GPIO_IDR_Pos 0x10
/*#define GPIO_IDR_ID0*/

/*8.4.6 Регистр выходных данных порта GPIO (GPIOx_ODR) (x = A..I/J/K) Address offset: 0x14*/
/*Эти биты могут быть прочитаны и записаны программным обеспечением.*/
//#define GPIO_ODR_Pos 0x14
/*#define GPIO_ODR_OD0*/

/*8.4.7 Регистр установки/сброса бита порта GPIO (GPIOx_BSRR) (x = A..I/J/K) Address offset: 0x18*/
/*Эти биты доступны только для записи и могут быть доступны в режиме слова, полуслова или байта. Чтение этих битов возвращает значение 0x0000.*/
//#define GPIO_BSRR_Pos 0x18
/*#define GPIO_BSRR_BS0 = 0x1 - установить бит в 1*/
/*#define GPIO_BSRR_BR0 = 0x1 - сбросить бит в 0*/

/*8.4.8 Регистр блокировки конфигурации порта GPIO (GPIOx_LCKR)(x = A..I/J/K) Address offset: 0x1C*/
/*Эти биты доступны только для записи и могут быть доступны в режиме слова, полуслова или байта. Чтение этих битов возвращает значение 0x0000.*/
//#define GPIO_LCKR_Pos 0x1C
/*#define GPIO_LCKR_LCKK = 0x1 - заблокировать весь порт. Регистр GPIOx_LCKR заблокирован до сброса микроконтроллера или сброса периферийного устройства.*/
/*#define GPIO_LCKR_LCK0 = 0x1 - заблокировать бит, Эти биты доступны для чтения и записи, но могут быть записаны только тогда, когда бит LCKK равен «0».*/

/*8.4.9 Альтернативная функция GPIO нижнего регистра 0-7 (GPIOx_AFRL) (x = A..I/J/K) Address offset: 0x20*/
/*8.4.10 Альтернативная функция GPIO верхнего регистра 8-15 (GPIOx_AFRH)(x = A..I/J) Address offset: 0x24*/
#define GPIO_AF0 (0x0)
#define GPIO_AF1 (0x1)
#define GPIO_AF2 (0x2)
#define GPIO_AF3 (0x3)
#define GPIO_AF4 (0x4)
#define GPIO_AF5 (0x5)
#define GPIO_AF6 (0x6)
#define GPIO_AF7 (0x7)
#define GPIO_AF8 (0x8)
#define GPIO_AF9 (0x9)
#define GPIO_AF10 (0xA)
#define GPIO_AF11 (0xB)
#define GPIO_AF12 (0xC)
#define GPIO_AF13 (0xD)
#define GPIO_AF14 (0xE)
#define GPIO_AF15 (0xF)

/*var*/

/*structures*/

typedef enum
{
PIN0 = 0,  
PIN1 = 1,  
PIN2 = 2,  
PIN3 = 3,  
PIN4 = 4,  
PIN5 = 5,  
PIN6 = 6,  
PIN7 = 7,  
PIN8 = 8,  
PIN9 = 9,  
PIN10 = 10,  
PIN11 = 11,  
PIN12 = 12,  
PIN13 = 13,  
PIN14 = 14,  
PIN15 = 15,
	
}PINx;

typedef struct
{
	GPIO_TypeDef* GPIOx;	/*Указывает настраиваемые порт GPIO GPIO_TypeDef*/
	
  uint32_t Pin;	/*Указывает настраиваемые контакты GPIO */

  uint32_t Mode;	/*Задает режим работы для выбранных контактов */

  uint32_t Pull;	/*Задает активацию подтягивания вверх(Pull-up) или опускания(Pull-Down) вниз для выбранных контактов.*/
	
	uint32_t Otyper;	/*Задать выход или открытый коллектор*/

  uint32_t Speed;	/*Задает скорость для выбранных контактов */

  uint32_t Alternate;	/*Периферийное устройство, подключаемое к выбранным контактам */
	
}GPIO_Structure;

/*func*/
void GPIO_Init(GPIO_Structure *GPIO_Str);

/* побитовые выполнители*/
void ODR_Xor(GPIO_Structure *GPIO_Str);
void ODR_1(GPIO_Structure *GPIO_Str);
void ODR_0(GPIO_Structure *GPIO_Str);

#endif