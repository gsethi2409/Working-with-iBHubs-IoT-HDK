/* Gunjan Sethi
 * 19/06/2017, Bangalore, India
 * This code uses the iBHubs IoT HDK(with ESP8266) to publish data to an MQTTBroker(Raspberry Pi) and subscribing to the same.
 * Uses: MQTTBox
 */


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "iBHubs 1";
const char* password = "";
WiFiClient espClient;
PubSubClient client(espClient);
const char* mqtt_server = "192.168.2.207";//broker's IP address-Raspberry Pi
String clientID = "Team6Client";
char* message;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void reconnect()
{
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Client")) 
    {
      Serial.println("connected");
      Serial.println(Serial.read());
      client.subscribe("Topic");
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer(mqtt_server, 1883);//default port for communication=1883
  client.setCallback(callback);
  
}

int value;
void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
  Serial.print("Publish message: HHHEEEEYYYY");
  client.publish("Topic", "HHHEEEEYYYY");
  delay(1000);
  
}
