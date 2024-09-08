// Code สำหรับการต่อปุ่มแบบง่าย ๆ 
// สร้างตัวแปรสำหรับการกำหนด pin ว่า pin ไหนเป็น pin สำหรับปุ่ม
int Button = 4;

void setup() {
  // put your setup code here, to run once:
  // เรียกใช้งาน Serial Monitor
  Serial.begin(115200);
  // กำหนด pin ว่าใช้งาน pin ไหนสำหรับการส่งสัญญาณออก 
  pinMode(Button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // สร้างตัวแปรสำหรับการรับค่าโดยค่าที่รับมาได้จะเรียกว่า Temp 
  int Temp = digitalRead(Button);

  // แสดง Temp ใน Serial Monitor
  Serial.println(Temp);
}
