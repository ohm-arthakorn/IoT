#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// ? Variable Definition
const int sampleWindow = 50;
int sample;
const char* ssid = "Arthakorn"; // * WIFI ssid 
const char* password = "123456789"; // * Password WIFI
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_Client = "Arthakorn";
const char* mqtt_username = "";
const char* mqtt_password = "";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;
char msg[100];    
String DataString;

// ? Pin Definition
#define SENSOR_PIN A0
#define Blue_LED 2
#define Green_LED 4
#define Yellow_LED 7
#define Red_LED 8
#define Buzzer 12

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]");
  String message;
  for(int i = 0; i< length; i++){
    message = message + char(payload[i]);
  }
  Serial.println(message);
  if(String(topic) == "sound/value"){
    if(message == "ON"){
      Serial.println("LED ON");
    }
    else if(message == "OFF"){
      Serial.println("LED OFF");
    }
  }
}

// * Function to connect internet with board 
void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
  if(client.connect(mqtt_Client, mqtt_username, mqtt_password)){
    Serial.println("Connected!");
    client.subscribe("sound/value");
  }
  else{
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("Try again in 3 seconds");
    delay(3000);
    }
  }
}

void setup()
{
  pinMode(SENSOR_PIN, INPUT); // Set the signal pin as input
  pinMode(Green_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(115200);
  Serial.println();;
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address : ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.subscribe("sound/value");
}



// * function สำหรับการแสดงผลไฟ LED Bar 
void LightBar(byte Blue_INPUT, byte Green_INPUT, byte Yellow_INPUT, byte Red_INPUT){
  digitalWrite(Blue_LED, Blue_INPUT);
  delay(10);
  digitalWrite(Green_LED, Green_INPUT);
  delay(10);
  digitalWrite(Yellow_LED, Yellow_INPUT);
  delay(10);
  digitalWrite(Red_LED, Red_INPUT);
}

// * VOID LOOP RIGHT HERE 
void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  float peakToPeak = 0;                 // peak-to-peak level

  unsigned int signalMax = 0;    // minimum value
  unsigned int signalMin = 1024; // maximum value

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(SENSOR_PIN); // get reading from microphone
    if (sample < 1024)               // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample; // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample; // save just the min levels
      }
    }
  }

  peakToPeak = signalMax - signalMin;          // max - min = peak-peak amplitude
  int db = map(peakToPeak, 20, 900, 49.5, 90); // calibrate for deciBels

  Serial.print("Loudness: ");
  Serial.print(db);
  Serial.println("dB");

  // ? This is OLD Code to turn on LIGHTBAR!
  /*if ((db > 65) && (db < 80))
  {
    digitalWrite(Green_LED, 1);
    delay(10);
    digitalWrite(Yellow_LED, 1);
    delay(10);
    digitalWrite(Red_LED, 1);
    delay(10);
    digitalWrite(Blue_LED, 0);
    tone(Buzzer, 2000, 1000);
  }
  else if (db >= 80)
  {
    digitalWrite(Green_LED, 1);
    delay(10);
    digitalWrite(Yellow_LED, 1);
    delay(10);
    digitalWrite(Red_LED, 1);
    delay(10);
    digitalWrite(Blue_LED, 1);
    delay(10);
  }
  else if ((db > 60) && (db < 65))
  {
    digitalWrite(Green_LED, 1);
    delay(10);
    digitalWrite(Yellow_LED, 1);
    delay(10);
    digitalWrite(Red_LED, 0);
    digitalWrite(Blue_LED, 0);
  }
  else if ((db > 50) && (db < 55))
  {
    digitalWrite(Green_LED, 1);
    delay(10);
    digitalWrite(Yellow_LED, 0);
    digitalWrite(Red_LED, 0);
    digitalWrite(Blue_LED, 0);
  }
  else
  {
    digitalWrite(Red_LED, 0);
    digitalWrite(Yellow_LED, 0);
    digitalWrite(Green_LED, 0);
    digitalWrite(Blue_LED, 0);
  }
*/

  // ? This is a NEW Code to turn on LIGHTBAR!
  if(db>=80){
    LightBar(1,1,1,1);
    tone(Buzzer, 4000, 1000);
  }
  else if((db>=65)&&(db<80)){
    LightBar(1,1,1,0);
  }
  else if((db>60)&&(db<65)){
    LightBar(1,1,0,0);
  }
  else if((db>50)&&(db<=60)){
    LightBar(1,0,0,0);
  }
  else {
    LightBar(0,0,0,0);
  }

  delay(50);

  // ? Sending Data to NETPIE
  if(startMillis - lastMsg > 5000){
    lastMsg = startMillis;
    ++value;
    DataString = "{\"data\":{\"Loudness\" : "+(String)db+"}}";
    DataString.toCharArray(msg, 100);
    Serial.println("Hello NETPIE2020");
    Serial.print("Publish message : ");
    Serial.println(msg);
    client.publish("sound/status", msg);
  }
  delay(1);
}
