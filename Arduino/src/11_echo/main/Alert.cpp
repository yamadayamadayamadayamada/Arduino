#include <Arduino.h>

#include "Alert.h"

void AlertInit(void)
{
    pinMode(LED_ERROR, OUTPUT);
}

void AlertError(const char* mess)
{
    Serial.printls(mess);

    digitalWrite(LED_ERROR, HIGH);
}
