#include "CommonDef.h"
#include "Alert.h"

#define KIC_TASK(ID)                     \
    do                                   \
    {                                    \
        if ((ID) != FACTOR_IDLE)         \
        {                                \
            TaskPrintState();            \
            ERROR("[error]task matagi"); \
        }                                \
        else                             \
        {                                \
            (ID) = FACTOR_REQUESTED;     \
        }                                \
    } while (0)

#define START_TASK(ID, FrameIndex, Task) \
    do                                   \
    {                                    \
        if ((ID) == FACTOR_REQUESTED)    \
        {                                \
            (ID) = FACTOR_RUNNING;       \
            Task((FrameIndex));          \
            END_TASK((ID));              \
            return;                      \
        }                                \
    } while (0)

#define END_TASK(ID) (ID) = FACTOR_IDLE

enum EFactorState
{
    FACTOR_IDLE = 0,
    FACTOR_REQUESTED,
    FACTOR_RUNNING,
};

extern FactorID ID_TIMER1;
extern FactorID ID_COMMAND;

void TaskPrintState(void);
