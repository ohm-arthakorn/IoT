#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;
#define LED_PIN 11 //ขาที่ต่อกับ LED
#define DHTPIN 2   //ขาที่ต่อเซนเซอร์ DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Arthakorn"; //อย่าลืมแก้ไข SSID ของ WIFI ที่จะให้ NodeMCU ไปเชื่อมต่อ
const char* password = "123456789"; //อย่าลืมแก้ไข PASSWORD ของ WIFI
const char* mqtt_server = "broker.netpie.io"; //อย่าลืมแก้ไข BROKER
const int mqtt_port = 1883;
const char* mqtt_Client = "b7c1868d-be11-4508-8306-d29a7e3dd2dd";  //อย่าลืมแก้ไข ClientID
const char* mqtt_username = "o6CUmV5SVhdDaZBjAERQfvT2Z3eqk2a8";  //อย่าลืมแก้ไข Token
const char* mqtt_password = "6DVbr2FRr3wstgt1dcqpPdSnprThhMVX"; //อย่าลืมแก้ไข Secret
byte frame[8][12] = {

  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },

  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },

  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },

  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },

  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

};

byte close[8][12] = {

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

};


WiFiClient espClient; 
PubSubClient client(espClient);

long lastMsg = 0;
int value = 0;
char msg[100];
String DataString;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
  if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) { //เชื่อมต่อกับ MQTT BROKER
    Serial.println("connected");
    client.subscribe("@msg/operator");
  }
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("try again in 5 seconds");
    delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + char(payload[i]);
  }
  Serial.println(message);
  if(String(topic) == "@msg/operator") {
    if (message == "ON"){
      digitalWrite(LED_PIN,HIGH);
      //client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"on\"}}");
      Serial.println("LED ON");
      matrix.renderBitmap(frame, 8, 12); 
      }
    else if (message == "OFF") {
      digitalWrite(LED_PIN,LOW);
      //client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"off\"}}");
      Serial.println("LED OFF"); 
      matrix.renderBitmap(close, 8, 12);
      }
    } 
}

void setup() {
  matrix.begin();
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //เชื่อมต่อกับ WIFI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //เชื่อมต่อกับ WIFI สำเร็จ แสดง IP
  client.setServer(mqtt_server, mqtt_port); //กำหนด MQTT BROKER, PORT ที่ใช้
  client.setCallback(callback); //ตั้งค่าฟังก์ชันที่จะทำงานเมื่อมีข้อมูลเข้ามาผ่านการ Subscribe
  client.subscribe("@msg/operator");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) { //จับเวลาส่งข้อมูลทุก ๆ 5 วินาที
    lastMsg = now;
    ++value;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float temp = analogRead(A2);
    float val = map(temp, 1023, 0, 0, 100);
    DataString = "{\"data\":{\"temperature\":"+(String)t+",\"humidity\":"+(String)h+",\"Percent Brightness\":"+(String)val+"}}"; 
    // Example of data : {"data":{"temperature":25 , "humidity": 60}}
    DataString.toCharArray(msg, 100);
    Serial.println("Hello NETPIE2020");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("@shadow/data/update", msg); // อย่าลืมแก้ไข TOPIC ที่จะทำการ PUBLISH ไปยัง MQTT BROKER
  }
  delay(1);
}