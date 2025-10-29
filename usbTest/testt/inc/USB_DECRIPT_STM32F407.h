#ifndef USB_DECRIPT_STM32F407_H_
#define USB_DECRIPT_STM32F407_H_

/*-----------------------------------------------------------------------------------------------*/
#include "stm32f407xx.h"

#define LOBYTE(x) ((uint8_t)(x & ~0xFF00))
#define HIBYTE(x) ((uint8_t)((x >> 8) & ~0xFF00))

#define EP_COUNT (3)
#define CDC_LINE_CODING_LENGTH (7)

#define USBD_VID (1155)
#define USBD_LANGID_STRING (1033)
#define USBD_MANUFACTURER_STRING ("STMicroelectronics")
#define USBD_PID_FS (22336)
#define USBD_PRODUCT_STRING_FS ("DimDim Virtual ComPort")

/*-----------------------------------------------------------------------------------------------*/
/* Строковый дескриптор устройства */
#define DEVICE_DESCRIPTOR_LENGTH (18)
#define EP0_SIZE (64)

uint8_t* Get_Device_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/* Дескриптор конфигурации */
#define USB_CDC_MAX_PACKET_SIZE (64)
#define CDC_CMD_PACKET_SIZE (8)/*Размер пакета конечной точки управления*/
#define CONFIGURATION_DESCRIPTOR_LENGTH (67)

uint8_t* Get_Configuration_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/* Дескриптор языковой строки */
#define LANG_DESCRIPTOR_LENGTH (4)

uint8_t* Get_Language_String_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор производителя*/
#define MFC_DESCRIPTOR_LENGTH (38)

uint8_t* Get_Manufactor_String_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор продукта*/
#define PRODUCT_DESCRIPTOR_LENGTH (44)

uint8_t* Get_Product_String_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор серийного номера*/
#define SERIAL_DESCRIPTOR_LENGTH (26)

uint8_t* Get_Serial_Number_String_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор квалификатора устройства*/
#define DEVICE_QUALIFIER_LENGTH (10)

uint8_t* Get_Device_Qualifier_Descriptor();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор интерфейса устройства*/
#define INTERFACE_STRING_LENGTH (28)

uint8_t* Get_String_Interface();

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор интерфейса устройства*/
#define CONFIG_STRING_LENGTH (22)

uint8_t* Get_Configuration_String_Descriptor();


#endif