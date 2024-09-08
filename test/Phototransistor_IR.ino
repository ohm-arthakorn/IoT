// code Phototransistor 
// Phototransistor เป็น Sensor สำหรับการรับค่าแสง โดยที่เราเรียนกันในคาบอ่ะ เขาเอามาใช้งานร่วม IR เพื่อเป็น Sensor การวัดระยะ

void setup() {
  // put your setup code here, to run once:
  // เรียกใช้งาน Serial Monitor
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // สร้างตัวแปรสำหรับการเก็บค่าที่ได้จากการอ่าน analogRead()
  int Temp = analogRead(A0);
  // แสดงค่าตัวแปร Temp
  Serial.println(Temp);

}
