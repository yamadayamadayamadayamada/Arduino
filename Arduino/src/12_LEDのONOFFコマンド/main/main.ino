#include "CommonDef.h"
#include "Serial.h"
#include "Alert.h"
#include "Task.h"
#include "FullColorLed.h"

UInt32 gs_FrameIndex;

void setup()
{
    gs_FrameIndex = 0;

    AlertInit();
    TaskFullColorLedInit();
    SerialInit();

    /* Timer1 割込み設定 */
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTCmode //prescaler to 64
    OCR1A = 5000 - 1;                                   /* 0.0625μs*64*5000 = 20ms(50Hz) */
    TIMSK1 |= (1 << OCIE1A);                            /* 割込み許可 */

    /* setup end */
    Serial.print(">");
}

ISR(TIMER1_COMPA_vect)
{
    KIC_TASK(ID_TIMER1);

    gs_FrameIndex++;
}

void loop()
{
    START_TASK(ID_TIMER1, gs_FrameIndex, TaskFullColorLed);    /* TIMER1_COMPA_vect でキック */
    START_TASK(ID_COMMAND, gs_FrameIndex, TaskCmd); /* SerialRead() でキック */

    SerialRead();
}
