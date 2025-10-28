#include "DRIVER1_USB.h"

// Internal global variable to track USB state
volatile uint32_t usb_state = 0;

// Helper macro to enable USB peripheral
#define ENABLE_USB_PERIPH() do { \
    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN; \
    USB_OTG_FS_GCCFG |= USB_OTG_GCCFG_PWRDWN; \
    USB_OTG_FS_GAHBCFG |= USB_OTG_GAHBCFG_GINT; \
} while(0)

// Soft reset the USB controller
void USB_SoftReset(void) {
    USB_OTG_FS_GRSTCTL |= USB_OTG_GRSTCTL_CSRST; 
    while(USB_OTG_FS_GRSTCTL & USB_OTG_GRSTCTL_CSRST) {}
}

// Perform basic initialization sequence
void USB_Init(void) {
    // Enable USB peripheral
    ENABLE_USB_PERIPH();

    // Do a soft reset to ensure clean state
    USB_SoftReset();

    // Clear any pending interrupts
    USB_OTG_FS_GINTSTS = 0;

    // Включить глобальную маску прерываний
    USB_OTG_FS_GINTMSK |= USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM_Msk;

    // Опрос на предмет события сброса USB
    while(!(USB_OTG_FS_GINTSTS & USB_OTG_GINTSTS_USBRST)) {}

    // Reset event detected, proceed with further configuration
    usb_state = 1;
}