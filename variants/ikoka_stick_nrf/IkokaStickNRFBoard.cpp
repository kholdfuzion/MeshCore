#ifdef XIAO_NRF52

#include <Arduino.h>
#include <Wire.h>

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

#endif
