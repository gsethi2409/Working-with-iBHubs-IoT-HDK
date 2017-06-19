/* Gunjan Sethi
 * 19/06/2017, Bangalore, India
 * This code uses the iBHubs IoT HDK(with ESP8266) to input distance, humidity and temperature vals from DHT11 
 * and Ultrasonic HC-SR04 module and upload to thinger.io. 
 * The code also uses slider values from thinger.io to control RGB lights on module. 
 */


#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include<Adafruit_NeoPixel.h>

#define USERNAME "gsethi2409"
#define DEVICE_ID "ESP8266"
#define DEVICE_CREDENTIAL "<cred>"

#define SSID "<ssid>"
#define SSID_PASSWORD "<password>"
#include "DHT.h"
#define DHTTYPE DHT11  
#define DHTPIN 2 
#define triggerPin 5
#define echoPin 4
#define PIN 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10,PIN,NEO_GRB+NEO_KHZ800);
int r,g,b;
boolean party;

long duration;
int distance;
DHT dht(DHTPIN, DHTTYPE);

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
float h,t;

void UltrasonicVals()
{
  //delay(2000);
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);
}

void DHTvals()
{
  //delay(2000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t))
    Serial.println("Failed to read from DHT sensor!");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C "); 
}

void setColor()
{
  for(int i=0;i<10;i++)
    strip.setPixelColor(i,strip.Color(r,g,b));
  strip.show();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  thing.add_wifi(SSID, SSID_PASSWORD);

  strip.begin();
  strip.show(); //reflect the changes on to the board
  strip.setBrightness(100);
  
  dht.begin(); 
  thing["Humidity"] >> outputValue(h);
  thing["Temperature"] >> outputValue(t); 
  thing["Distance"] >> outputValue(distance); 

  thing["Red"] << inputValue(r,setColor());
  thing["Blue"] << inputValue(b,setColor());
  thing["Green"] << inputValue(g, setColor());

 
}

void loop() {
  // put your main code here, to run repeatedly
  UltrasonicVals();
  DHTvals();
  thing.handle();
  //thing.call_endpoint("IFTTTendpoint");
}
