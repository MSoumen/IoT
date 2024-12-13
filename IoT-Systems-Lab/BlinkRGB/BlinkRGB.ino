/*
  BlinkRGB

  Demonstrates usage of onboard RGB LED on some ESP dev boards.

  Calling digitalWrite(LED_PIN, HIGH) will use hidden RGB driver.

  RGBLedWrite demonstrates control of each channel:
  void rgbLedWrite(uint8_t pin, uint8_t red_val, uint8_t green_val, uint8_t blue_val)

  WARNING: After using digitalWrite to drive RGB LED it will be impossible to drive the same pin
    with normal HIGH/LOW level
*/
//#define RGB_BRIGHTNESS 64 // Change white brightness (max 255)
//#define LED_PIN 38
#define LED_PIN 3

// the setup function runs once when you press reset or power the board

void setup() {
  // No need to initialize the RGB LED
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn the RGB LED white
  delay(1000);
  digitalWrite(LED_PIN, LOW);  // Turn the RGB LED off
  delay(1000);

//int red = random(0, 255);
//int green = random(0, 255);
//int blue = random(0, 255);
//      Serial.println(red);
//      Serial.println(green);
//      Serial.println(blue);
//  rgbLedWrite(LED_PIN, red,green, blue);  // Red
//  delay(500);
////  rgbLedWrite(LED_PIN, 0, RGB_BRIGHTNESS, 0);  // Green
////  delay(1000);
////  rgbLedWrite(LED_PIN, 0, 0, RGB_BRIGHTNESS);  // Blue
////  delay(1000);
////  rgbLedWrite(LED_PIN, 0, 0, 0);  // Off / black
////  delay(1000);
}
