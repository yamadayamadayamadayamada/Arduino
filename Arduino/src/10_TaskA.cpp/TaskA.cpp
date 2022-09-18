#include <Arduino.h>

#include "TaskA.h"

UInt8 gs_DutyRead;
UInt8 gs_DutyGreen;
UInt8 gs_DutyBlue;

static UInt8 get_duty(UInt32 FrameIndex, UInt32 Offset);

void TaskAInit(void)
{
    /* Do Nothing */
}

void TaskA(UInt32 FrameIndex)
{
    gs_DutyRead = get_duty(FrameIndex, OFFSET_READ);
    gs_DutyGreen = get_duty(FrameIndex, OFFSET_GREAN);
    gs_DutyBlue = get_duty(FrameIndex, OFFSET_BLUE);

    analogWrite(LED_READ, gs_DutyRead);
    analogWrite(LED_GREEN, gs_DutyGreen);
    analogWrite(LED_BLUE, gs_DutyBlue);
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