#include <ESP8266WiFi.h>
#include "time.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define TRIG_PIN 12 //D6
#define ECHO_PIN 13 //D7
#define DHT_PIN 2 //3 //RX
#define DHT_TYPE DHT22 //DHT11

//OLED RELETED STUFF//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

//DHT22 object initialization
DHT DHTobject = DHT(DHT_PIN, DHT_TYPE);

//OLED init
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid     = "Aircrack-ng";
const char* password = "RedChille";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;
struct tm timeinfo;

long distance;
float temp, humi;

void setup(){
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  DHTobject.begin();
  
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
  display.print("SOU");
  display.write(3);
  display.println("MEN");
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
  display.setCursor(0, display.getCursorY()+10);
  display.println("WiFi connected. ");
  display.setTextSize(2);
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
  display.clearDisplay();
  // Init and get the time and sensor data
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  fetchLocalTime();
  fetchSensorData();
  WiFi.disconnect(true);
//  WiFi.mode(WIFI_OFF); 

}

void loop(){
  displayTimeAndSensorData();
  delay(1000);
}

String weekDayArr[] = {"Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void fetchLocalTime(){
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return ;
  }
}

void displayTimeAndSensorData(){ 
  fetchLocalTime();
  Serial.println(asctime(&timeinfo));
  String weekday = weekDayArr[timeinfo.tm_wday];
  
  display.clearDisplay();
  display.setRotation(0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(weekday);
  display.print("  ");
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
  display.setRotation(0); //rotation reset

  //displaying sensor data
  fetchSensorData();
  display.setTextSize(2);
  display.setCursor(13,50);
  display.print("D:");
  if(distance>900)display.print("---- ");
  else display.print(distance);
  display.setTextSize(1);
  display.setCursor(display.getCursorX(),56);
  display.println(" cm.");
  
  display.setCursor(13,12); //left, down
  display.setTextSize(2);
  display.print("T:");
  display.print(temp);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.print("C");
  
  display.setCursor(13,30);
  display.setTextSize(2);
  display.print("H:");
  display.print(humi);
  display.setTextSize(1);
  display.setCursor(display.getCursorX(),36);
  display.print(" %");
  

  display.display();
  
  return;
}

void fetchSensorData(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW); 
  distance = pulseIn(ECHO_PIN, HIGH)/2 * 0.034;
//  delay(500);
  temp = DHTobject.readTemperature(); //in celsius
  humi = DHTobject.readHumidity();
  
  // Prints the distance on the Serial Monitor
  Serial.printf("Distance: %d cm\n", distance);
  Serial.printf("Temp. %0.2f\tHumidity %0.2f\n", temp, humi);
//  delay(2000);
}
