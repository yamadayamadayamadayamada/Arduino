#include "CommonDef.h"
#include "Alert.h"
#include "TaskA.h"

#define KIC_TASK(ID)                 \
    do                               \
    {                                \
        if ((ID) != FACTOR_IDLE)     \
        {                            \
            ERROR();                 \
        }                            \
        else                         \
        {                            \
            (ID) = FACTOR_REQUESTED; \
        }                            \
    } while (0)

#define START_TASK(ID, FrameIndex, Task) \
    do                                   \
    {                                    \
        if ((ID) == FACTOR_REQUESTED)    \
        {                                \
            Task((FrameIndex));          \
            END_TASK((ID));              \
        }                                \
    } while (0)

#define END_TASK(ID) (ID) = FACTOR_IDLE

UInt32 gs_FrameIndex;

enum EFactorState
{
    FACTOR_IDLE = 0,
    FACTOR_REQUESTED,
    FACTOR_RUNNING,
};

FactorID ID_TIMER1 = FACTOR_IDLE;

void setup()
{
    gs_FrameIndex = 0;

    AlertInit();
    TaskAInit();

    /* Timer1 割込み設定 */
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTCmode //prescaler to 64
    OCR1A = 5000 - 1;                                   /* 0.0625μs*64*5000 = 20ms(50Hz) */
    TIMSK1 |= (1 << OCIE1A);                            /* 割込み許可 */
}

/*
 50Hzで呼ばれる割込みタスク

 タスクのキックとフレームインデクスの管理を行う
 重い処理を行わないこと ※20msを超えないように注意
 */
ISR(TIMER1_COMPA_vect)
{
    KIC_TASK(ID_TIMER1);

    gs_FrameIndex++;
}

void loop()
{
    START_TASK(ID_TIMER1, gs_FrameIndex, TaskA);    /* TIMER1_COMPA_vect でキック */
}