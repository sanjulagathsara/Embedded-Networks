// Medibox Project
// Name - Gathsara J.A.S
// Index Number - 210180L


// Libraries
#include <Wire.h> // I2C Library
#include <Adafruit_GFX.h> // Graphics Library
#include <Adafruit_SSD1306.h> // OLED Display Library
#include <DHTesp.h> // DHT Library
#include <WiFi.h> // WiFi Library
#include <PubSubClient.h>

// Defining OLED display parameters
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_RESET -1
#define DISPLAY_ADDRESS 0x3C

// NTP Server details
#define NTP_SERVER   "pool.ntp.org"
int UTC_OFFSET = (5*3600)+1800;
int UTC_OFFSET_DST = 0;

// Declare objects
Adafruit_SSD1306 display(DISPLAY_WIDTH,DISPLAY_HEIGHT,&Wire,DISPLAY_RESET);
DHTesp dhtSensor;

// Define Pins
#define BUZZER 5
#define LED_1 23
#define PB_CANCEL 36
#define PB_OK 34
#define PB_UP 39
#define PB_DOWN 35
#define DHTPIN 19

// Gllobal Variables
int days = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;

unsigned long  time_now = 0;
unsigned long  time_last = 0;

bool alarm_enabled = true;
int n_alarms = 3;
int alarm_hours[] = {0,1,2};
int alarm_minutes[] = {1,10,33};
bool alarm_triggered[] = {false,false,false};

// Notes for buzzer
int n_notes = 8;
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_H = 523;

int notes[] = {C,D,E,F,G,A,B,C_H};

// Mode parameters
int current_mode = 0;
int max_modes = 5;
String modes[] = {"1 - Set Time Zone","2 - Set Alarm 1","3 - Set Alarm 2","4 - Set Alarm 3","5 - Disable Alarms"};


// Wifi Codes
WiFiClient espClient;
PubSubClient mqttClient(espClient);

float randomNumber;

/****************************************************************************
-----------------------------   Setting Up  ----------------------------------
****************************************************************************/

void setup() {

  pinMode(BUZZER,OUTPUT);

  dhtSensor.setup(DHTPIN,DHTesp::DHT11);


  Serial.begin(115200);
  delay(500);
  Serial.println("MediBox is Initializing!");

  

  //if(!display.begin(SSD1306_SWITCHCAPVCC,DISPLAY_ADDRESS)){
  //  Serial.println(F("Medibox SSD1306 Display Allocation Failed"));
  //  for(;;);
  //}

  //display.clearDisplay();
  //print_line("Smart",30,10,2);
  //print_line("Medibox",20,40,2);


  //WiFi.begin("ElectroCube Wifi2","electrocubesanjula88",6);
  WiFi.begin("Pixel_8025","88888888",6);
  //WiFi.begin("Sanjula's iPhone","chocolate14",6);
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
   // display.clearDisplay();
   // print_line("Connecting to WiFi",0,20,2);
  }

  //display.clearDisplay();
  //print_line("Connected to WiFi",0,20,2);
  Serial.println("Wifi Connected");

  // Displaying buffer on the screen
  //display.display();
  //delay(2000);
  //display.clearDisplay();
  //print_line("Welcome to MediBox!",0,20,2);

  for(int i=0;i<5;i++){
    digitalWrite(BUZZER,HIGH);
    delay(150);
    digitalWrite(BUZZER,LOW);
    delay(50);
  }

  //delay(1000);

  setup_mqtt();
  Serial.println("MQTT Done");
 
  //client.publish("topic/state", "Hello from ESP32");


}

/****************************************************************************
--------------------------   Looping the Code ------------------------------
****************************************************************************/

int counter = 0;

void loop() {

  if(!mqttClient.connected()){
    connectToBroker();
  }
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  delay(1000);
  Serial.println(data.temperature);

  mqttClient.loop();
  char buf3[10];;
  //Serial.println(randNumber);
  sprintf(buf3,"%f",data.temperature);

  //print_line(buf3, 0, 30, 4);
  mqttClient.publish("ESP32-TEMP",buf3);
  delay(100);

  /*
  // put your main code here, to run repeatedly:
  update_time_with_check_alarm();
  if(digitalRead(PB_OK) == LOW){
    button_beep();
    delay(200);
    go_to_menu();
  }
  check_temp();
  */
  
}
