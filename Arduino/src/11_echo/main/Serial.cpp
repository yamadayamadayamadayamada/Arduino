#include <Arduino.h>

#include "CommonDef.h"
#include "Serial.h"
#include "Task.h"

#define BUFFER_SIZE 256

static char gs_Buffer[BUFFER_SIZE];
static const char *gs_BufferEndAdd = &gs_Buffer[BUFFER_SIZE - 1];
static char *p_w;

#define IS_EOF(Character) ((Character) == '\r' || (Character) == '\n' || (Character) == '\0')

void SerialInit(void)
{
    Serial.begin(115200);
    Serial.print("Hello Arduino!\n");

    p_w = &gs_Buffer[0];
}

void SerialRead(void)
{
    if (Serial.available() <= 0)
    {
        return;
    }

    CHECK_NOT_EQ(p_w, gs_BufferEndAdd, "[error]read buffer over");

    *p_w = Serial.read(); // 1バイト分のデータを読み取る
    if (IS_EOF(*p_w))
    {
        *p_w++;
        *p_w = '\0';

        KIC_TASK(ID_COMMAND);
        return;
    }
    *p_w++;
}

void TaskCmd(UInt32 FrameIndex)
{
    Serial.print("Input:");
    Serial.println(gs_Buffer);

    p_w = &gs_Buffer[0];
}
