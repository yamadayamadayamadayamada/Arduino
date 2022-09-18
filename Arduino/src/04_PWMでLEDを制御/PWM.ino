/*
 PWMを使う

 3・5・6・9・10・11番(~が書かれていないやつ)
 pinMode()は必要ない

  */
#define UInt8 short

#define LED_D3 3
#define LED_D4 4
#define LED_D7 7
#define LED_D9 9
#define LED_D10 10
#define LED_D11 11
#define LED_A5 A5

#define PWM_OFFSET 255
#define OFFSET_READ 0
#define OFFSET_GREAN 0
#define OFFSET_BLUE 0

UInt8 WAIT_TIME = 10; // 待ち時間を指定
UInt8 STEP = 1;       // デューティー比の変化(ステップ数)
UInt8 DutyBlue;

UInt8 Duty = 0;

void setup()
{
}

void loop()
{
    DutyBlue = abs((Duty + OFFSET_BLUE) % 512 - PWM_OFFSET);

    analogWrite(LED_D9, DutyBlue);
    delay(WAIT_TIME);

    Duty = Duty + STEP;
}