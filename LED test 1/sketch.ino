byte initialPin=12;
byte LEDpin=12;
const byte limit=4;
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDpin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDpin, HIGH);
  delay(300);
  digitalWrite(LEDpin, LOW);
  // delay(100);
  LEDpin -= 2;
  if(LEDpin<limit) LEDpin=initialPin;
}
