#ifndef _HWPORT_H_
#define _HWPORT_H_

#include <avr/io.h>
#include <avr/wdt.h>

#ifdef KBDMOD_M3
#define USB_LEVEL_SHIFT_PORT    PORTD
#define USB_LEVEL_SHIFT_DDR     DDRD
#define USB_LEVEL_SHIFT_PIN     0

#define PS2_CLK_PULLUP_PORT     PORTD
#define PS2_CLK_PULLUP_DDR      DDRD
#define PS2_CLK_PULLUP_PIN      1


#define LED_PRT_PORT        (uint8_t *const)&PORTC
#define LED_PRT_PIN         7

#define LED_NUM_PORT        (uint8_t *const)&PORTC
#define LED_NUM_PIN         7

#define LED_CAP_PORT        (uint8_t *const)&PORTC
#define LED_CAP_PIN         6

#define LED_SCR_PORT        (uint8_t *const)&PORTC
#define LED_SCR_PIN         7



#define LED_WASD_PORT       (uint8_t *const)&PORTD
#define LED_WASD_PIN        7

#define LED_PAD_PORT        (uint8_t *const)&PORTC
#define LED_PAD_PIN         7

#define LED_ARROW18_PORT    (uint8_t *const)&PORTC
#define LED_ARROW18_PIN     7

#define LED_VESEL_PORT      (uint8_t *const)&PORTC
#define LED_VESEL_PIN       7


#define LED_Fx_PORT         (uint8_t *const)&PORTD
#define LED_Fx_PIN          5

#define LED_BASE_PORT       (uint8_t *const)&PORTD
#define LED_BASE_PIN        4

#define LED_ESC_PORT        (uint8_t *const)&PORTC
#define LED_ESC_PIN         7

#define BOOTLOADER_ADDRESS 0x7000

#else
#define USB_LEVEL_SHIFT_PORT    PORTD
#define USB_LEVEL_SHIFT_DDR     DDRD
#define USB_LEVEL_SHIFT_PIN     6

#define PS2_CLK_PULLUP_PORT     PORTD
#define PS2_CLK_PULLUP_DDR      DDRD
#define PS2_CLK_PULLUP_PIN      7


#define LED_PRT_PORT        (uint8_t *const)&PORTD
#define LED_PRT_PIN         2

#define LED_NUM_PORT        (uint8_t *const)&PORTD
#define LED_NUM_PIN         3

#define LED_CAP_PORT            (uint8_t *const)&PORTD
#define LED_CAP_PIN         4

#define LED_SCR_PORT        (uint8_t *const)&PORTD
#define LED_SCR_PIN         5



#define LED_WASD_PORT       (uint8_t *const)&PORTB
#define LED_WASD_PIN        7

#define LED_PAD_PORT        (uint8_t *const)&PORTB
#define LED_PAD_PIN         4

#define LED_ARROW18_PORT    (uint8_t *const)&PORTB
#define LED_ARROW18_PIN     6

#define LED_VESEL_PORT      (uint8_t *const)&PORTB
#define LED_VESEL_PIN       5


#define LED_Fx_PORT         (uint8_t *const)&PORTE
#define LED_Fx_PIN          3

#define LED_BASE_PORT       (uint8_t *const)&PORTE
#define LED_BASE_PIN        4

#define LED_ESC_PORT        (uint8_t *const)&PORTE
#define LED_ESC_PIN         5

#define BOOTLOADER_ADDRESS 0x1F000
#endif

#define Reset_AVR() wdt_enable(WDTO_250MS); while(1) {}
typedef void (*AppPtr_t) (void); 
//#define Reset_AVR Bootloader 

#endif
