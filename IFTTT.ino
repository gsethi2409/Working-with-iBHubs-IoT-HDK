/* Gunjan Sethi
 * 19/06/2017, Bangalore, India
 * This code uses the iBHubs IoT HDK(with ESP8266) to trigger an event IFTTT action on button press. 
 */


#include <ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;
int btn;
int httpCode;

const char* ssid ="IOC Bootcamp";
const char* pass ="bmsce@ioc123";

void setup() {
  pinMode(inPin, INPUT);
  Serial.begin(115200);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  
  pixels.begin();

}

void loop() {
  btn = digitalRead(inPin);
  delay(1000);
  httpCode = http.GET();
  
  
  if(btn) {
    
    Serial.println(btn);
    http.begin("maker.ifttt.com",80,"/trigger/...");
  }
  http.end();
  btn = 0;
  
}
