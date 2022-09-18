/*
 複数のLEDを点滅させる

 アナログ入力ピンはデジタル出力として使うこともできる
 */

#define LED_D4 4
#define LED_D7 7
#define LED_A5 A5
#define LED_COUNT 3

#define UInt8 short

static const UInt8 LED_LISTS[] = {
    LED_D4,
    LED_D7,
    LED_A5,
};

void setup()
{
    pinMode(LED_D4, OUTPUT);
    pinMode(LED_D7, OUTPUT);
    pinMode(LED_A5, OUTPUT);
}

void loop()
{
    static UInt8 FrameIndex = 0;
    UInt8 ListIndex;

    ListIndex = FrameIndex % LED_COUNT;

    digitalWrite(LED_LISTS[ListIndex], HIGH);
    delay(100);
    digitalWrite(LED_LISTS[ListIndex], LOW);

    FrameIndex++;
}