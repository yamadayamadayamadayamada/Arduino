/* 
 ビルドインLEDを1秒間隔で点滅させる
 
 13番のピンの電圧を切り替える
 そのため、13番にLEDをさした場合、そのLEDも点滅する
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);  // LED_BUILTIN(デジタルピン13番ピン)を出力モードに設定
}
 
 
// loop関数は何度も繰り返し実行されます
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);   // LEDを点灯(HIGHは電圧レベルを5Vにする)
  delay(100);                       // 1秒間(1000ms)待つ
  digitalWrite(LED_BUILTIN, LOW);    // LEDを消灯(LOWは電圧レベルを0Vにする)
  delay(100);                       // 1秒間(1000ms)待つ
}