/*
 周期処理

 https://garchiving.com/how-to-use-timer-interrupt-with-arduino/?msclkid=c63f76ecad7311ecadb00c32707cad49
 Timer1を使用して割込み処理を行う
 Timer0は関数で使われているので割込みとして使用できない

 Arduinoのクロック周波数は16MHzのため、1カウントは1/16MHz=0.0625μs
 */

#define UInt8 short

#define LED_READ 11
#define LED_GREEN 10
#define LED_BLUE 9

#define PWM_OFFSET 255
#define OFFSET_READ 0
#define OFFSET_GREAN 0
#define OFFSET_BLUE 0

UInt8 STEP = 1; // デューティー比の変化(ステップ数)
UInt8 DutyBlue;

UInt8 Duty = 0;

void setup()
{
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_READ, OUTPUT);

    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS12); // CTCmode //prescaler to 256
    OCR1A = 31250 - 1;                    /* 0.0625μs*31250*256 = 500ms */
    TIMSK1 |= (1 << OCIE1A);              /* 割込み許可 */
}

ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    digitalWrite(LED_READ, !digitalRead(LED_GREEN));
}

void loop()
{
}