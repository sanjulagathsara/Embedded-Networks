const char* ssid = "ElectroCube Wifi2";
const char* password =  "electrocubesanjula88";
const char* mqttServer = "192.168.1.118";
const int mqttPort = 1883;
const char* mqttUser = "ESP32Client-1002";
const char* mqttPassword = "mmcisawesome";


void setup_mqtt(){
  mqttClient.setServer("test.mosquitto.org",1883);
  mqttClient.setCallback(receiveCallback);
}

void connectToBroker(){
  while(!mqttClient.connected()){
    Serial.println("Attempting MQTT Connection...");
   // display.clearDisplay();
    //print_line("Attempting MQTT Connection",0,20,2);
    if(mqttClient.connect(mqttUser)){
      Serial.println("Connected");
     // print_line("Connected",0,50,2);
      digitalWrite(BUZZER,HIGH);
      delay(200);
      digitalWrite(BUZZER,LOW);
      mqttClient.subscribe("ESP32-BUZZER");
      mqttClient.subscribe("ESP32-CLIENT2");
    }
    else{
      Serial.println("Failed");
     // print_line("Failed",0,50,2);
      Serial.println(mqttClient.state());
      char bufTemp[10];
      sprintf(bufTemp, "%d", mqttClient.state());
     // print_line(bufTemp,80,50,2);
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
      delay(2000);
    }
  }
}

void receiveCallback(char* topic,byte* payload,unsigned int length){
  Serial.print("Message Arrived [");
  Serial.print(topic);
  Serial.print("]");

  for(int i=0;i<3;i++){
    digitalWrite(BUZZER,HIGH);
    delay(30);
    digitalWrite(BUZZER,LOW);
    delay(30);
  }

  char payloadCharAr[length];

  for(int i=0;i<length;i++){
    Serial.print((char)payload[i]);
    payloadCharAr[i] = (char)payload[i];
  }


  char tempArr[10] = {'p','l','a','y','b','u','z','z','e','r'};
  for(int i=0;i<length;i++){
    if(payloadCharAr[i] != tempArr[i]){
      break;
    }
    Serial.print(payloadCharAr[i]);
    Serial.print("  ");
    Serial.println(tempArr[i]);
    if(i==(length-1)){
        for(int i=0;i<3;i++){
            digitalWrite(BUZZER,HIGH);
            delay(200);
            digitalWrite(BUZZER,LOW);
            delay(100);
  }
   Serial.println("Buzzer player");
    }
  }


    char tempArr2[13] = {'c','l','i','e','n','t','2','b','u','z','z','e','r'};
  for(int i=0;i<length;i++){
    if(payloadCharAr[i] != tempArr2[i]){
      break;
    }
    Serial.print(payloadCharAr[i]);
    Serial.print("  ");
    Serial.println(tempArr2[i]);
    if(i==(length-1)){
        for(int i=0;i<2;i++){
            digitalWrite(BUZZER,HIGH);
            delay(800);
            digitalWrite(BUZZER,LOW);
            delay(500);
  }
   Serial.println("Buzzer player");
    }
  }
  

}