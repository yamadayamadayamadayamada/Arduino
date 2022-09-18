#include <Arduino.h>

#include "Task.h"

#define STRING(str) #str

FactorID ID_TIMER1 = FACTOR_IDLE;
FactorID ID_COMMAND = FACTOR_IDLE;

typedef struct tagTask
{
    const char *Name;
    FactorID *ID;
} STask;

STask gs_TaskList[] = {
    {STRING(ID_TIMER1), &ID_TIMER1},
    {STRING(ID_COMMAND), &ID_COMMAND},
};

void TaskInit(void)
{
}

void TaskPrintState(void)
{
    UInt32 i;
    for (i = 0; i < sizeof(gs_TaskList) / sizeof(STask); i++)
    {
        Serial.print(gs_TaskList[i].Name);
        Serial.print(":");
        switch (*gs_TaskList[i].ID)
        {
        case FACTOR_IDLE:
            Serial.println("Idle");
            break;
        case FACTOR_REQUESTED:
            Serial.println("Requested");
            break;
        case FACTOR_RUNNING:
            Serial.println("Running");
            break;
        default:
            ERROR("[error]task state");
            break;
        }
    }
}