#include <DHT.h>
//#include <DHTesp.h> //negative temp only when dht_type is wrong
//#include <dht.h> //not supported for ESP8266

#define TRIG_PIN 12 //D6
#define ECHO_PIN 13 //D7

#define DHT_PIN 2 //3 //RX
#define DHT_TYPE DHT22 //DHT11

//DHTesp DHTobject;
DHT DHTobject = DHT(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
//  DHTobject.setup(DHT_PIN, DHTesp::DHT_TYPE);
  DHTobject.begin();
}

void loop() {
   
  int distance = getDistance(TRIG_PIN, ECHO_PIN);
  
//  delay(DHTobject.getMinimumSamplingPeriod());
//  float temp = DHTobject.getTemperature();
//  float humi = DHTobject.getHumidity();
  delay(2000);
  float temp = DHTobject.readTemperature(); //in celsius
  float humi = DHTobject.readHumidity();
  
  // Prints the distance on the Serial Monitor
  Serial.printf("Distance: %d cm\n", distance);
  Serial.printf("Temp. %0.2f\tHumidity %0.2f\n", temp, humi);
  delay(2000);

}

int getDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in micro second 
  long duration = pulseIn(echoPin, HIGH)/2; // duration is Round Trip Time

  // Calculating the distance
  //sound velocity=340m/s | (D=V.T) | 1s=1000ms => 0.034cm/microSec
  return (duration*0.034);
}
