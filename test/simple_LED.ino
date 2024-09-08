// ไฟล์สำหรับการเปิดไฟ LED 
// สร้างตัวแปรสำหรับการกำหนดว่า pin ไหนคือ pin สำหรับการเปิดหลอดไฟ
int led = 2;


void setup() {
  // put your setup code here, to run once:
  // กำหนด pin ว่าเป็นสัญญาณขาออก
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // ให้ไฟ LED เปิด
  digitalWrite(led, 1);
  delay(1000);

  // ให้ไฟ LED ปิด
  digitalWrite(led, 0);
  delay(1000);
}
