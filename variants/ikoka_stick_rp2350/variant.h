#ifndef _IKOKA_STICK_RP2350_H_
#define _IKOKA_STICK_RP2350_H_

#include <cstdint>

/** Master clock frequency */
#define VARIANT_MCK       (150000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define PINS_COUNT              (20)
#define NUM_DIGITAL_PINS        (11)
#define NUM_ANALOG_INPUTS       (4)
#define NUM_ANALOG_OUTPUTS      (0)

// LEDs
#define PIN_LED                 (LED_RED)
#define LED_PWR                 (PINS_COUNT)
#define PIN_NEOPIXEL            (PINS_COUNT)
#define NEOPIXEL_NUM            (0)

#define LED_BUILTIN             (PIN_LED)

// RP2350 GPIO pin assignments for LEDs
#define LED_RED                 (17)    // GPIO17
#define LED_GREEN               (18)    // GPIO18
#define LED_BLUE                (19)    // GPIO19

#define LED_STATE_ON            (1)     // State when LED is litted

// Buttons
#define PIN_BUTTON1             (PINS_COUNT)
#define PIN_USER_BTN            (0)     // Button on D0

// Digital PINs - Map to Arduino D0-D10 using RP2350 GPIO numbers
// Based on Seeed XIAO RP2350 pinout

// Analog pins
#define PIN_A0                  (26)   // GPIO26
#define PIN_A1                  (27)   // GPIO27
#define PIN_A2                  (28)   // GPIO28
#define PIN_A3                  (29)   // GPIO29
#define PIN_VBAT                (29)   // GPIO29

#define AREF_VOLTAGE            (3.3)
#define ADC_MULTIPLIER          (3.0F)

// I2C pins
#define PIN_WIRE_SDA            (6)     // GPIO6 - D4
#define PIN_WIRE_SCL            (7)     // GPIO7 - D5










#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
