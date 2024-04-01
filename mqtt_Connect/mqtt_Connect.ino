#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "ElectroCube Wifi2";
const char* password =  "electrocubesanjula88";
const char* mqttServer = "192.168.1.118";
const int mqttPort = 1883;
const char* mqttUser = "ESP32Client";
const char* mqttPassword = "mmcisawesome";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("topic/state", "Hello from ESP32");
 
}
 int i = 0;
 char buf[10];
void loop() {
  client.loop();
  delay(4000);
  sprintf(buf, " Sanjula_%d", i);
  client.publish("topic/state",buf);
  i++;
  Serial.println(buf);
}
