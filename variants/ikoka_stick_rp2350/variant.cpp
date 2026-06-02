#include <Arduino.h>
#include "variant.h"

void initVariant()
{
    // Initialize LED pins
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);
    
    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, HIGH);
    
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, HIGH);
}
