#include <ESP8266WiFi.h>
#include "time.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
//#include <dht.h>

//#define DHT_TYPE DHT22
//#define DHT_PIN 14
//#define TRIG_INPUT 19
//#define ECHO_OUT 20

//OLED RELETED STUFF//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//--------------------------------------//

//DHT dht(DHT_PIN, DHT_TYPE);

//float temp, humi, temp_faren;
//long duration;

const char* ssid     = "Aircrack-ng";
const char* password = "RedChille";
//const char* ssid     = "gimil";
//const char* password = "kkkkkkkk";

const char* ntpServer = "pool.ntp.org";
//const char* ntpServer = "in.pool.ntp.org";
//const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;//3600;

void setup(){
  Serial.begin(9600);
//  pinMode(DHT_PIN, INPUT);
//  pinMode(TRIG_INPUT, INPUT);
//  pinMode(TRIG_INPUT, OUTPUT);
  // pinMode(ECHO_OUT, OUTPUT);
//  dht.begin();
//  delay(100);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  else Serial.println("SSD1306 allocation done.");
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,24);
  display.print("S ");
  display.write(3);
  display.println(" M");
  display.display();
  delay(1000);
  
  // Connect to Wi-Fi
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Connecting to : ");
  display.println(ssid);
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected. [IP: ");
  Serial.println(WiFi.localIP());
  display.print("WiFi connected. ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
  display.clearDisplay();
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
//  WiFi.mode(WIFI_OFF); 

}

void loop(){
  printLocalTime();
  delay(1000);
}

String weekDayArr[] = {"Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void printLocalTime(){
//  temp = dht.readTemperature();
//  temp_faren = dht.readTemperature(true);
//  humi = dht.readHumidity();
//
//  Serial.print("Temp:");
//  Serial.print(temp);
//  Serial.print(" C\n");
//  Serial.print("Temp(F):");
//  Serial.print(temp_faren);
//  Serial.print(" F\n");
//  Serial.print("Humidity:");
//  Serial.print(humi);
//  Serial.print("%\n");

  // Ultrasonic Sensor
//  digitalWrite(TRIG_INPUT, LOW);
//  delay(2);
//  digitalWrite(TRIG_INPUT, HIGH);
//  delay(5);
//  digitalWrite(TRIG_INPUT, LOW);
//
//  duration = pulseIn(TRIG_INPUT, HIGH);
//  Serial.println("\n");
//  Serial.print("Distance : ");
//  int distance = duration/29/2;
//  Serial.print(duration/29/2);
//  Serial.println("cm\n");

  struct tm timeinfo; 
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return ;
  }
//  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//  Serial.println(asctime(&timeinfo));
  Serial.printf("%01d, %02d/%02d/%04d %02d:%02d:%02d\n",timeinfo.tm_wday,timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year,   timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  String weekday = weekDayArr[timeinfo.tm_wday];
  
//  displayTime();
  display.clearDisplay();
  display.setRotation(0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(weekday);
  display.print(" ");
  if(timeinfo.tm_mday<10) display.print(0);
  display.print(timeinfo.tm_mday+1); display.print("/");
  if(timeinfo.tm_mon<10) display.print(0);
  display.print(timeinfo.tm_mon+1); display.print("/");
  display.print(timeinfo.tm_year+1900); display.println(" ");
  
  display.setRotation(3);
  display.setCursor(0, 0);
  if(timeinfo.tm_hour<10) display.print(0);
  display.print(timeinfo.tm_hour); display.print(":");
  if(timeinfo.tm_min<10) display.print(0);
  display.print(timeinfo.tm_min); display.print(":");
  if(timeinfo.tm_sec<10) display.print(0);
  display.println(timeinfo.tm_sec);
  
  display.display();
  
  return;
}

//void displayTime(){}
