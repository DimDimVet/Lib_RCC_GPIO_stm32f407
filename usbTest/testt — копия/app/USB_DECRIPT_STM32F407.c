#include "USB_DECRIPT_STM32F407.h"

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор устройства*/

uint8_t device_Descriptor[DEVICE_DESCRIPTOR_LENGTH] =
  {
    DEVICE_DESCRIPTOR_LENGTH, //
    0x01, /* Тип дескриптора - устройство */
    0x00, /* 0x0110 = usb 1.1 ; 0x0200 = usb 2.0 */
    0x02,
    0x02, /* CDC */
    0x02, /* Подкласс абстрактной модели управления */
    0x00, /* протокол */
    EP0_SIZE, /* Размер EP0 */
    LOBYTE(USBD_VID),
    HIBYTE(USBD_VID),
    LOBYTE(USBD_PID_FS),
    HIBYTE(USBD_PID_FS),
    0x00, /* версия (BCD) */
    0x02, /* версия (BCD) */
    0x01, /* Индекс строки производителя */
    0x02, /* Индекс строки продукта */
    0x03, /* Индекс строки серийного номера */
    1 /* количество конфигураций */
  };

uint8_t *Get_Device_Descriptor()
{
  return device_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/*Дескриптор конфигурации*/
uint8_t configuration_Descriptor[CONFIGURATION_DESCRIPTOR_LENGTH] =
{
  /*Дескриптор конфигурации*/
  0x09, /* bLength: Размер дескриптора конфигурации */
  0x02, /* bDescriptorType: Конфигурация */
  CONFIGURATION_DESCRIPTOR_LENGTH, /* wTotalLength: Количество возвращаемых байтов */
  0x00,
  0x02, /* bNumInterfaces: 2 интерфейса */
  0x01, /* bConfigurationValue: Значение конфигурации */
  0x00, /* iConfiguration: Индекс строкового дескриптора, описывающего конфигурацию */
  0xC0, /* bmAttributes: Автономное питание */
  0x32, /* MaxPower 0 мА */

  /*Дескриптор интерфейса */
  0x09, /* bLength: Размер дескриптора интерфейса */
  0x04, /* bDescriptorType: Интерфейс */
  /* Тип дескриптора интерфейса */
  0x00, /* bInterfaceNumber: Количество интерфейсов */
  0x00, /* bAlternateSetting: Альтернативная настройка */
  0x01, /* bNumEndpoints: Используется одна конечная точка */
  0x02, /* bInterfaceClass: Класс интерфейса связи */
  0x02, /* bInterfaceSubClass: Абстрактная модель управления */
  0x01, /* bInterfaceProtocol: Общие AT-команды */
  0x00, /* iInterface: */

  /*Функциональный дескриптор заголовка*/
  0x05, /* bLength: Размер дескриптора конечной точки */
  0x24, /* bDescriptorType: CS_INTERFACE */
  0x00, /* bDescriptorSubtype: Описание функции заголовка */
  0x10, /* bcdCDC: Номер версии спецификации */
  0x01,

  /*Функциональный дескриптор управления вызовами*/
  0x05, /* bFunctionLength */
  0x24, /* bDescriptorType: CS_INTERFACE */
  0x01, /* bDescriptorSubtype: Описание функции управления вызовами */
  0x00, /* bmCapabilities: D0+D1 */
  0x01, /* bDataInterface: 1 */

  /*Функциональный дескриптор ACM*/
  0x04, /* bFunctionLength */
  0x24, /* bDescriptorType: CS_INTERFACE */
  0x02, /* bDescriptorSubtype: Описание абстрактного управления */
  0x02, /* bmCapabilities */

  /*Дескриптор функционального объединения*/
  0x05, /* bFunctionLength */
  0x24, /* bDescriptorType: CS_INTERFACE */
  0x06, /* bDescriptorSubtype: Описание функции объединения */
  0x00, /* bMasterInterface: Интерфейс класса связи */
  0x01, /* bSlaveInterface0: Интерфейс класса данных */

  /*Дескриптор конечной точки 2*/
  0x07, /* bLength: Размер дескриптора конечной точки */
  0x05, /* bDescriptorType: Конечная точка */
  0x82, /* bEndpointAddress */
  0x03, /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x10, /* bInterval: */

  /*Дескриптор интерфейса класса данных*/
  0x09, /* bLength: Размер дескриптора конечной точки */
  0x04, /* bDescriptorType: */
  0x01, /* bInterfaceNumber: Количество интерфейсов */
  0x00, /* bAlternateSetting: Альтернативная настройка */
  0x02, /* bNumEndpoints: Используются две конечные точки */
  0x0A, /* bInterfaceClass: CDC */
  0x00, /* bInterfaceSubClass: */
  0x00, /* bInterfaceProtocol: */
  0x00, /* iInterface: */

  /*Исходящий дескриптор конечной точки*/
  0x07, /* bLength: Размер дескриптора конечной точки */
  0x05, /* bDescriptorType: Конечная точка */
  0x01, /* bEndpointAddress */
  0x02, /* bmAttributes: Массовая передача */
  LOBYTE(USB_CDC_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(USB_CDC_MAX_PACKET_SIZE),
  0x00, /* bInterval: игнорировать для массовой передачи */

  /*Входящий дескриптор конечной точки*/
  0x07, /* bLength: Размер дескриптора конечной точки */
  0x05, /* bDescriptorType: Конечная точка */
  0x81, /* bEndpointAddress */
  0x02, /* bmAttributes: Массовая передача */
  LOBYTE(USB_CDC_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(USB_CDC_MAX_PACKET_SIZE),
  0x00 /* bInterval: игнорировать для массовой передачи */
};

uint8_t* Get_Configuration_Descriptor()
{
	return configuration_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/*Дескриптор языковой строки*/
uint8_t language_String_Descriptor[LANG_DESCRIPTOR_LENGTH] =
{
  LANG_DESCRIPTOR_LENGTH, /* USB_LEN_LANGID_STR_DESC */
  0x03, /* USB_DESC_TYPE_STRING */
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING)
};

uint8_t* Get_Language_String_Descriptor()
{
	return language_String_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор производителя*/
uint8_t manufactor_String_Descriptor[MFC_DESCRIPTOR_LENGTH] =
{
  MFC_DESCRIPTOR_LENGTH,
  0x03, /* USB_DESC_TYPE_STRING */
  'S', 0x00,
  'T', 0x00,
  'M', 0x00,
  'i', 0x00,
  'c', 0x00,
  'r', 0x00,
  'o', 0x00,
  'e', 0x00,
  'l', 0x00,
  'e', 0x00,
  'c', 0x00,
  't', 0x00,
  'r', 0x00,
  'o', 0x00,
  'n', 0x00,
  'i', 0x00,
  'c', 0x00,
  's', 0x00
};

uint8_t* Get_Manufactor_String_Descriptor()
{
	return manufactor_String_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/* Строковый дескриптор продукта */
uint8_t product_String_Descriptor[PRODUCT_DESCRIPTOR_LENGTH] =
{
  PRODUCT_DESCRIPTOR_LENGTH,
  0x03, /* USB_DESC_TYPE_STRING */
  'D', 0x00,
  'i', 0x00,
  'D', 0x00,
  'i', 0x00,
  'm', 0x00,
  ' ', 0x00,
  'V', 0x00,
  'i', 0x00,
  'r', 0x00,
  't', 0x00,
  'u', 0x00,
  'a', 0x00,
  'l', 0x00,
  ' ', 0x00,
  'C', 0x00,
  'o', 0x00,
  'm', 0x00,
  'P', 0x00,
  'o', 0x00,
  'r', 0x00,
  't', 0x00
};

uint8_t* Get_Product_String_Descriptor()
{
	return product_String_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/* Строковый дескриптор серийного номера */
uint8_t serial_Number_String_Descriptor[SERIAL_DESCRIPTOR_LENGTH] =
{
  SERIAL_DESCRIPTOR_LENGTH,
  0x03, /* USB_DESC_TYPE_STRING */
  0x34, 0x00,
  0x38, 0x00,
  0x00, 0x00,
  0x45, 0x00,
  0x37, 0x00,
  0x34, 0x00,
  0x46, 0x00,
  0x37, 0x00,
  0x36, 0x00,
  0x33, 0x00,
  0x30, 0x00,
  0x38, 0x00
};

uint8_t* Get_Serial_Number_String_Descriptor()
{
	return serial_Number_String_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор квалификатора устройства*/
uint8_t device_Qualifier_Descriptor[DEVICE_QUALIFIER_LENGTH] =
{
  DEVICE_QUALIFIER_LENGTH,
  0x06, /* Квалификатор устройства */
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00
};

uint8_t* Get_Device_Qualifier_Descriptor()
{
	return device_Qualifier_Descriptor;
}

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор интерфейса устройства*/
uint8_t string_Interface[INTERFACE_STRING_LENGTH] =
{
  INTERFACE_STRING_LENGTH,
  0x03, /* USB_DESC_TYPE_STRING */
  'C', 0x00,
  'D', 0x00,
  'C', 0x00,
  ' ', 0x00,
  'I', 0x00,
  'n', 0x00,
  't', 0x00,
  'e', 0x00,
  'r', 0x00,
  'f', 0x00,
  'a', 0x00,
  'c', 0x00,
  'e', 0x00
};

uint8_t* Get_String_Interface()
{
	return string_Interface;
}

/*-----------------------------------------------------------------------------------------------*/
/*Строковый дескриптор интерфейса устройства*/
uint8_t configuration_String_Descriptor[CONFIG_STRING_LENGTH] =
{
  CONFIG_STRING_LENGTH,
  0x03, /* USB_DESC_TYPE_STRING */
  'C', 0x00,
  'D', 0x00,
  'C', 0x00,
  ' ', 0x00,
  'C', 0x00,
  'o', 0x00,
  'n', 0x00,
  'f', 0x00,
  'i', 0x00,
  'g', 0x00
};

uint8_t* Get_Configuration_String_Descriptor()
{
	return configuration_String_Descriptor;
}