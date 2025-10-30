#ifndef USB_FS_STM32F407_H_
#define USB_FS_STM32F407_H_

#include <string.h>
#include "USB_DECRIPT_STM32F407.h"
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "lib_stm32.h"
#include "GPIO_STM32F407.h"

/*-----------------------------------------------------------------------------------------------*/
/*Статусы USB*/
typedef enum
	{
	DEVICE_STATE_DEFAULT = 0,
	DEVICE_STATE_RESET = 1,
	DEVICE_STATE_ADDRESSED = 2,
	DEVICE_STATE_LINECODED = 4,
	DEVICE_STATE_TX_PR = 8, /* TX transmission active */
	DEVICE_STATE_TX_FIFO1_ERROR = 16 
	} eDeviceState;

/*-----------------------------------------------------------------------------------------------*/
/*Инициализация USB*/

/*Инициализация USB-port*/
void USB_Init_GPIO();
/*Инициализация USB-регистров*/
#define USB_OTG_DEVICE ((USB_OTG_DeviceTypeDef *) (USB_OTG_FS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
void USB_Init_Reg();

/*-----------------------------------------------------------------------------------------------*/
/*Установить размер и смещение FIFO RX и TX для каждого EP*/
#define RX_FIFO_SIZE (36) 									// 35 - minimum working   / 128
#define TX_EP0_FIFO_SIZE (16)								// 16 - minimum working  64
#define TX_EP1_FIFO_SIZE (320-(RX_FIFO_SIZE+TX_EP0_FIFO_SIZE))   // 128
//#define TX_EP2_FIFO_SIZE		0
//#define TX_EP3_FIFO_SIZE		0
	
void Set_FIFO_EP();

/*-----------------------------------------------------------------------------------------------*/
/*Инициализация EndPoints*/
typedef struct EndPointStruct{
	uint16_t status_Rx;
	uint16_t status_Tx;

	uint16_t rxCounter;
	uint16_t tx_Counter;
	
	uint8_t *rxBuffer_ptr;
	uint8_t *tx_Buffer_ptr;
	
	uint32_t (*tx_Call_Back)(uint8_t EPnum);
	uint32_t (*rxCallBack)(uint32_t param);
	uint32_t (*Set_Tx_Buffer)(uint8_t EPnum, uint8_t *tx_Buff, uint16_t len);	
} EndPointStruct;

/*Статусы EndPoints*/
#define EP_READY 				0U
#define EP_BUSY  				1U
#define EP_ZLP   				2U

extern EndPointStruct EndPoint[];//участвует в обработчике


void Init_EP();

/*-----------------------------------------------------------------------------------------------*/
/*Установка Tx буфера*/
#define MAX_CDC_EP0_TX_SIZ  		64/*Максимальный размер транзакции TX для EP0. «64» означает, что вы можете отправить максимум один пакет максимального размера
в TXCallback, затем вы отправляете оставшиеся байты (или ZLP) в следующем вызове функции. Максимальное значение USB_OTG_DIEPTSIZ_XFRSIZ. */
#define MAX_CDC_EP1_TX_SIZ  		256/*Максимальный размер транзакции TX для EP1. Максимальное значение USB_OTG_DIEPTSIZ_XFRSIZ*/

/*Статусы EndPoints*/
#define EP_OK					1U
#define EP_FAILED			0U

#define USB_EP_OUT(i) 			((USB_OTG_OUTEndpointTypeDef *) ((USB_OTG_FS_PERIPH_BASE +  USB_OTG_OUT_ENDPOINT_BASE) + ((i) * USB_OTG_EP_REG_SIZE)))
#define USB_EP_IN(i)    		((USB_OTG_INEndpointTypeDef *)	((USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE) + ((i) * USB_OTG_EP_REG_SIZE)))

#define RX_BUFFER_EP0_SIZE 8U 										/* Enough to set linecoding */
#define RX_BUFFER_EP1_SIZE 128U

uint32_t USB_Set_Tx_Buffer(uint8_t EPnum, uint8_t *tx_Buff, uint16_t len);

/*-----------------------------------------------------------------------------------------------*/
/*Загрузить транзакцию TX для определенного EP*/

uint32_t USB_Transfer_TX_Callback(uint8_t EPnum);

/*-----------------------------------------------------------------------------------------------*/
/*Отправить пакет нулевой длины*/

uint32_t Send_ZLP(uint8_t EPnum);

/*-----------------------------------------------------------------------------------------------*/
/*Включение EP зависло*/
uint32_t Endpoint_Enable_Stuck(uint8_t EPnum);

/*-----------------------------------------------------------------------------------------------*/
/*Если EP IN занята и данные застряли в TX FIFO*/
uint32_t Recovery_Routine_EP_IN(uint8_t EPnum);

/*-----------------------------------------------------------------------------------------------*/
/*проверить свободное место в Fifo*/
uint32_t Check_Free_Space_Fifo(uint8_t dfifo, uint32_t space);

/*-----------------------------------------------------------------------------------------------*/
/*Функции состояния устройства. Установка/очистка/проверка.*/
void Set_Device_Status(eDeviceState state);
void Clear_Device_Status(eDeviceState state);
uint32_t Check_Device_Status(eDeviceState state);
























/***************************************************
 * 			User settings
***************************************************/


#define FLUSH_FIFO_TIMEOUT		2000
#define DTFXSTS_TIMEOUT 		1024 //TODO

#define EP1_DTFXSTS_SIZE    		TX_EP1_FIFO_SIZE	/* TX FIFO empty level */
#define EP1_MIN_DTFXSTS_LVL		16		/* Minimum TX FIFO empty level */



#define DOEPT_TRANSFER_SIZE		0x40		/* Value used in DOEPTSIZ for EP1 */
#define DOEPT_TRANSFER_PCT 		0x01		/* Value used in DOEPTSIZ for EP1 */







/***************************************************
 * 			Device states
***************************************************/


	typedef enum{
	LINK_STATE_DEFAULT =							0, 
	LINK_STATE_DISCONNECTED =					1,
	LINK_STATE_CONNECTED =						2 } eLinkState;


/***************************************************
 * 			SETUP stage request templates
***************************************************/
	
#define REQ_TYPE_HOST_TO_DEVICE_GET_DEVICE_DECRIPTOR		0x0680
#define REQ_TYPE_DEVICE_TO_HOST_SET_ADDRESS							0x0500
#define REQ_TYPE_DEVICE_TO_HOST_SET_CONFIGURATION				0x0900

#define DESCRIPTOR_TYPE_DEVICE													0x0100
#define DESCRIPTOR_TYPE_CONFIGURATION										0x0200
#define DESCRIPTOR_TYPE_LANG_STRING											0x0300
#define DESCRIPTOR_TYPE_MFC_STRING											0x0301
#define DESCRIPTOR_TYPE_PROD_STRING											0x0302
#define DESCRIPTOR_TYPE_SERIAL_STRING										0x0303
#define DESCRIPTOR_TYPE_CONFIGURATION_STRING						0x0304
#define DESCRIPTOR_TYPE_INTERFACE_STRING								0x0305
#define DESCRIPTOR_TYPE_DEVICE_QUALIFIER								0x0600

#define CDC_GET_LINE_CODING															0x21A1
#define CDC_SET_LINE_CODING															0x2021
#define CDC_SET_CONTROL_LINE_STATE											0x2221

#define CLEAR_FEATURE_ENDP				0x0102
#define USB_FEATURE_EP_HALT				0x0000

/***************************************************
 * 		RX packet statuses
***************************************************/

#define STS_GOUT_NAK                           1
#define STS_DATA_UPDT                          2
#define STS_XFER_COMP                          3
#define STS_SETUP_COMP                         4
#define STS_SETUP_UPDT                         6

/***************************************************
* 		Endpoint structure
***************************************************/


/***************************************************
*
* 	Setup packet structure
* 	is used in union to access data both
* 	as structure and as raw data
*
***************************************************/
typedef struct{
	uint16_t  wRequest;
	uint16_t  wValue;
	uint16_t  wIndex;
	uint16_t  wLength;
} USB_setup_req;	/* SETUP packet buffer. Always 8 bytes */
 

typedef union{
	USB_setup_req setup_pkt;
	uint32_t raw_data[2];
} USB_setup_req_data;


/***************************************************
 *
 * 		Functions' declaration
 *
***************************************************/

/* init functions */

void enumerate_Reset(void);
void enumerate_Setup(void);
// void initEndPoints(void); -> static

/* FIFO access */
uint32_t write_Fifo(uint8_t dfifo, uint8_t *src, uint16_t len);
void read_Setup_Fifo(void);
void read_Fifo(uint8_t dfifo, uint16_t len);
// uint32_t DTFXSTS_timeout(uint8_t Epnum, uint32_t dtxfsts_val); -> static

/* Endpoint functions */
//uint32_t USB_CDC_setTxBuffer(uint8_t EPnum, uint8_t *txBuff, uint16_t len);
//uint32_t USB_CDC_transferTXCallback(uint8_t EPnum);
uint32_t USB_CDC_transferRXCallback_EP0(uint32_t param);
uint32_t USB_CDC_transferRXCallback_EP1(uint32_t param);
// inline void toggle_Rx_EP_Status(uint8_t EPnum, uint8_t param);

/* misc */
uint32_t USB_CDC_transmit_scheduler(void); /* this function monitors if any data is pending in circ buffer or whatever */
uint32_t USB_FlushTxFifo(uint32_t EPnum, uint32_t timeout);
uint32_t USB_FlushRxFifo(uint32_t timeout);

//uint32_t check_USB_device_status(eDeviceState state);
//void clear_USB_device_status(eDeviceState state);

/* User code functions */
uint32_t USB_CDC_send_data(uint8_t *txBuff, uint16_t len);
uint32_t USB_CDC_recieve_data(uint16_t length);
eLinkState USB_CDC_process_watchdog(void);

uint32_t getdevstat(void);









#define USB_CLEAR_INTERRUPT(IRQ)    ((USB_OTG_FS->GINTSTS) &= (IRQ))
#define USB_MASK_INTERRUPT(IRQ)     (USB_OTG_FS->GINTMSK &= ~(IRQ))
#define USB_UNMASK_INTERRUPT(IRQ)   (USB_OTG_FS->GINTMSK |= (IRQ))

#define CLEAR_IN_EP_INTERRUPT(NUM, IRQ)          (USB_EP_IN(NUM)->DIEPINT = (IRQ))
#define CLEAR_OUT_EP_INTERRUPT(NUM, IRQ)         (USB_EP_OUT(NUM)->DOEPINT = (IRQ))




 
 
#define USB_OTG_DFIFO(i)    *(__IO uint32_t *)((uint32_t)USB_OTG_FS_PERIPH_BASE  + USB_OTG_FIFO_BASE + (i) * USB_OTG_FIFO_SIZE)


typedef struct{
	__IO uint32_t PCGCCTL;
}
USB_OTG_PCGCCTLTypeDef;

#define USB_OTG_PCGCCTL      ((USB_OTG_PCGCCTLTypeDef *)( USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))

#endif