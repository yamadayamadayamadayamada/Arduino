#include <Arduino.h>

#include "Alert.h"

void AlertInit(void)
{
    pinMode(LED_ERROR, OUTPUT);
}

void AlertError(void)
{
    digitalWrite(LED_ERROR, HIGH);
}
