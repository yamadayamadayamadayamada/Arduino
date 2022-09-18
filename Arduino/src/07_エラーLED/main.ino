/*
 ERROR() 実施時に赤色LEDを光らせて戻る
 */

#include "error_def.h"

#define UInt8 short

#define LED_READ 11
#define LED_GREEN 10
#define LED_BLUE 9

#define PWM_OFFSET 255
#define OFFSET_READ 0
#define OFFSET_GREAN 0
#define OFFSET_BLUE 0
UInt8 Counter = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN(デジタルピン13番ピン)を出力モードに設定

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_READ, OUTPUT);
    pinMode(LED_ERROR, OUTPUT);

    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTCmode //prescaler to 64
    OCR1A = 5000 - 1;                                   /* 0.0625μs*64*5000 = 20ms(50Hz) */
    TIMSK1 |= (1 << OCIE1A);                            /* 割込み許可 */
}

ISR(TIMER1_COMPA_vect)
{
    if ((Counter++) % 50 == 0)
    {
        digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
        digitalWrite(LED_READ, !digitalRead(LED_GREEN));
    }

    if(Counter ==1000)
    {
        ERROR();
    }
}

void loop()
{
}

