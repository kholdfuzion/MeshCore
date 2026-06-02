#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <MeshCore.h>

#ifndef MESH_I2C_WIRE
  #define MESH_I2C_WIRE Wire
#endif

#ifdef XIAO_RP2350

class IkokaStickRP2350Board : public mesh::MainBoard {
public:
  IkokaStickRP2350Board() {}
  virtual ~IkokaStickRP2350Board() = default;
  
  void begin() {
    pinMode(PIN_USER_BTN, INPUT_PULLUP);

#if defined(PIN_WIRE_SDA) && defined(PIN_WIRE_SCL)
  // Drive I2C on the configured XIAO header pins for this variant.
    MESH_I2C_WIRE.setSDA(PIN_WIRE_SDA);
    MESH_I2C_WIRE.setSCL(PIN_WIRE_SCL);
#endif

    MESH_I2C_WIRE.begin();
    delay(100);   // give I2C more time to stabilize on RP2350

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

    delay(10);   // give sx1262 some time to power up
  }

  void onBeforeTransmit() override {
#if defined(LED_BLUE)
    digitalWrite(LED_BLUE, LOW);   // turn TX LED on (active low)
#elif defined(P_LORA_TX_LED)
    digitalWrite(P_LORA_TX_LED, LOW);
#endif
  }

  void onAfterTransmit() override {
#if defined(LED_BLUE)
    digitalWrite(LED_BLUE, HIGH);  // turn TX LED off
#elif defined(P_LORA_TX_LED)
    digitalWrite(P_LORA_TX_LED, HIGH);
#endif
  }

  uint16_t getBattMilliVolts() override {
    int adcvalue = 0;
    analogReadResolution(12);
    delay(10);
    // Ikoka RP2350 battery/system sense is wired to GPIO29 through ~3:1 divider.
    adcvalue = analogRead(29);
    return (uint16_t)((adcvalue * 3300.0f * 3.0f) / 4096.0f);
  }

  uint8_t getStartupReason() const override { return 0; }

  void reboot() override { rp2040.restart(); }

  const char *getManufacturerName() const override {
#ifdef MANUFACTURER_STRING
    return MANUFACTURER_STRING;
#else
    return "Ikoka Stick RP2350";
#endif
  }
};

#endif
