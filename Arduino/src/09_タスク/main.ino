/*
    Timer   Timer0 Timer1 Timer2
    pin        5,6   9,10   3,11
    最大値    8bit  16bit   8bit
 */

#include "Alert.h"

#define UInt8 unsigned short
#define Int32 long
#define UInt32 unsigned long

#define FactorID UInt8

#define False 0
#define True 1

#define LED_READ 11
#define LED_GREEN 5
#define LED_BLUE 3

#define OFFSET_READ 0
#define OFFSET_GREAN 256
#define OFFSET_BLUE 512

UInt32 gs_FrameIndex;

UInt8 gs_DutyRead;
UInt8 gs_DutyGreen;
UInt8 gs_DutyBlue;

enum FactorState
{
    FACTOR_IDLE = 0,
    FACTOR_REQUESTED,
    FACTOR_RUNNING,
};

FactorID ID_TIMER1 = FACTOR_IDLE;

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

#define START_TASK(ID, Task)          \
    do                                \
    {                                 \
        if ((ID) == FACTOR_REQUESTED) \
        {                             \
            Task();                   \
            END_TASK(ID_TIMER1);      \
        }                             \
    } while (0)

#define END_TASK(ID) (ID) = FACTOR_IDLE

UInt8 get_duty(UInt32 FrameIndex, UInt32 Offset);

void Task_A(void);

void setup()
{
    gs_FrameIndex = 0;

    AlertInit();

    /* 周期割込みにTimer1を利用 */
    /* 注意：Pin9,10のPWMが使えなくなる */
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTCmode //prescaler to 64
    OCR1A = 5000 - 1;                                   /* 0.0625μs*64*5000 = 20ms(50Hz) */
    TIMSK1 |= (1 << OCIE1A);                            /* 割込み許可 */
}

ISR(TIMER1_COMPA_vect)
{
    KIC_TASK(ID_TIMER1);

    gs_FrameIndex++;
}

void Task_A(void)
{
    gs_DutyRead = get_duty(gs_FrameIndex, OFFSET_READ);
    gs_DutyGreen = get_duty(gs_FrameIndex, OFFSET_GREAN);
    gs_DutyBlue = get_duty(gs_FrameIndex, OFFSET_BLUE);

    analogWrite(LED_READ, gs_DutyRead);
    analogWrite(LED_GREEN, gs_DutyGreen);
    analogWrite(LED_BLUE, gs_DutyBlue);
}

UInt8 get_duty(UInt32 FrameIndex, UInt32 Offset)
{
    Int32 Duty = (FrameIndex + Offset) % 767;

    if (Duty > 255)
    {
        Duty = 511 - Duty;
    }

    Duty = max(0, Duty);

    return Duty;
}

void loop()
{
    START_TASK(ID_TIMER1, Task_A);
}