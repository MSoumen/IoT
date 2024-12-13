#include <WiFi.h>
#include "time.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
//#include <dht.h>

//#define DHT_TYPE DHT22
//#define DHT_PIN 14
#define TRIG_INPUT 19
#define ECHO_OUT 20

//DHT dht(DHT_PIN, DHT_TYPE);

float temp, humi, temp_faren;
long duration;

const char* ssid     = "Aircrack-ng";
const char* password = "RedChille";
//const char* ssid     = "gimil";
//const char* password = "kkkkkkkk";

const char* ntpServer = "in.pool.ntp.org";
//const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

#define TFT_MOSI 35 // Data out
#define TFT_SCLK 36 // Clock out
#define TFT_DC 37  
#define TFT_RST 38
#define TFT_CS 5
#define TFT_BACKLIGHT 4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_White        = 0xFFFF;

// The colors we actually want to use
uint16_t        Display_Text_Color         = Display_Color_White;
uint16_t        Display_Backround_Color    = Display_Color_Black;

// assume the display is off until configured in setup()
bool            isDisplayVisible        = false;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t    MaxString               = 38;

// the string being displayed on the SSD1331 (initially empty)
char timeString[MaxString]           = { 0 };

void setup(){
  Serial.begin(115200);
//  pinMode(DHT_PIN, INPUT);
  pinMode(TRIG_INPUT, INPUT);
  pinMode(TRIG_INPUT, OUTPUT);
  // pinMode(ECHO_OUT, OUTPUT);
//  dht.begin();
  delay(100);
  

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);  
  delay(250);
      pinMode(TFT_BACKLIGHT, OUTPUT);
      digitalWrite(TFT_BACKLIGHT, HIGH);
      tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
    tft.setFont();
    tft.fillScreen(Display_Backround_Color);
    tft.setTextColor(Display_Text_Color);
    tft.setTextSize(1);
}

void loop(){
  isDisplayVisible = true;
  delay(1000);
  printLocalTime();
  tft.setCursor(10,90);
  tft.print("Group-3 : S.B.S.D");
//  char count[] ={++aount};
//  tft.print(count);
}

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
  digitalWrite(TRIG_INPUT, LOW);
  delay(2);
  digitalWrite(TRIG_INPUT, HIGH);
  delay(5);
  digitalWrite(TRIG_INPUT, LOW);

  duration = pulseIn(TRIG_INPUT, HIGH);
  Serial.println("\n");
  Serial.print("Distance : ");
  int distance = duration/29/2;
  Serial.print(duration/29/2);
  Serial.println("cm\n");

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return ;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    char *dest = asctime(&timeinfo);
  
//  sprintf(dest, "%01d, %02d/%02d/%04d %02d:%02d:%02d",timeinfo.tm_wday,timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year,   timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
   tft.setCursor(0,5);

        // change the text color to the background color
        tft.setTextColor(Display_Backround_Color);

        // redraw the old value to erase
        tft.setTextColor(Display_Text_Color);
        tft.print(dest);
//byte weekday_len=9;
//byte month_len=10;
//int i;
//for(i=0; i<weekday_len; i++) {tft.print(dest[i]); tft.setCursor(i+1, 5);}

  tft.setCursor(0,20);
  tft.setTextColor(Display_Backround_Color);
  tft.setTextColor(Display_Text_Color);
//  tft.print("temp : %d,  Humidity : %d\n", temp,   humi);
  tft.setCursor(0,30);
  tft.print("distance : %d cm\n");
  tft.print(distance);
  

return;
}
