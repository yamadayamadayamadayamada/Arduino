#include <Arduino.h>

#include "FullColorLed.h"

#define ON 1
#define OFF 0

UInt8 gs_LedState;

UInt8 gs_DutyRead;
UInt8 gs_DutyGreen;
UInt8 gs_DutyBlue;

static UInt8 get_duty(UInt32 FrameIndex, UInt32 Offset);

void TaskFullColorLedInit(void)
{
    gs_LedState = ON;
}

void TaskFullColorLed(UInt32 FrameIndex)
{
    if (gs_LedState == OFF)
    {
        analogWrite(LED_READ, 0);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 0);

        return;
    }

    gs_DutyRead = get_duty(FrameIndex, OFFSET_READ);
    gs_DutyGreen = get_duty(FrameIndex, OFFSET_GREAN);
    gs_DutyBlue = get_duty(FrameIndex, OFFSET_BLUE);

    analogWrite(LED_READ, gs_DutyRead);
    analogWrite(LED_GREEN, gs_DutyGreen);
    analogWrite(LED_BLUE, gs_DutyBlue);
}

void CmdFullColorLed(int argc, char **argv)
{
  if (argc != 2)
    {
        Serial.println("led on/off");
        return;
    }

    if (!strcmp(argv[1],"on"))
    {
        gs_LedState = ON;
    }

    if (!strcmp(argv[1],"off"))
    {
        gs_LedState = OFF;
    }
}

static UInt8 get_duty(UInt32 FrameIndex, UInt32 Offset)
{
    Int32 Duty = (FrameIndex + Offset) % 767;

    if (Duty > 255)
    {
        Duty = 511 - Duty;
    }

    Duty = max(0, Duty);

    return Duty;
}
