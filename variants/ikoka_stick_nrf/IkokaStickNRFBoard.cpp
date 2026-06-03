#ifdef XIAO_NRF52

#include <Arduino.h>
#include <Wire.h>
#include <nrf_soc.h>

#include "IkokaStickNRFBoard.h"

void IkokaStickNRFBoard::begin() {
  NRF52Board::begin();

  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, HIGH);

#ifdef PIN_USER_BTN
  pinMode(PIN_USER_BTN, INPUT_PULLUP);
#endif

#if defined(PIN_WIRE_SDA) && defined(PIN_WIRE_SCL)
  Wire.setPins(PIN_WIRE_SDA, PIN_WIRE_SCL);
#endif

  Wire.begin();

#ifdef P_LORA_TX_LED
  pinMode(P_LORA_TX_LED, OUTPUT);
  digitalWrite(P_LORA_TX_LED, HIGH);
#endif

#ifdef LED_GREEN
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);   // power/status LED on (active low)
#endif

#ifdef LED_BLUE
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);   // TX LED idle off
#endif

//  pinMode(SX126X_POWER_EN, OUTPUT);
//  digitalWrite(SX126X_POWER_EN, HIGH);
  delay(10);   // give sx1262 some time to power up
}

void IkokaStickNRFBoard::powerOff() {
#ifdef PIN_USER_BTN
  // Wait for key release to avoid immediate wake from an active-low button.
  while (digitalRead(PIN_USER_BTN) == USER_BTN_PRESSED);

  // Configure user button as wake source while in SYSTEMOFF.
  nrf_gpio_cfg_sense_input(
      digitalPinToInterrupt(g_ADigitalPinMap[PIN_USER_BTN]),
      NRF_GPIO_PIN_NOPULL,
      NRF_GPIO_PIN_SENSE_LOW);
#endif

#ifdef LED_GREEN
  digitalWrite(LED_GREEN, HIGH);
#endif
#ifdef LED_BLUE
  digitalWrite(LED_BLUE, HIGH);
#endif
#ifdef LED_RED
  digitalWrite(LED_RED, HIGH);
#endif

  // Prefer SoftDevice API when available; fall back to direct register write.
  uint8_t sd_enabled = 0;
  sd_softdevice_is_enabled(&sd_enabled);
  if (sd_enabled) {
    sd_power_system_off();
  }

  NRF_POWER->SYSTEMOFF = POWER_SYSTEMOFF_SYSTEMOFF_Enter;
}

#endif
