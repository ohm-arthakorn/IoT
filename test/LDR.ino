// Code LDR ง่าย ๆ 
// LDR Light Dependent Resistor เป็น Sensor ที่จะเพิ่มค่าความต้านทานตามปริมาณแสงที่ Sensor ได้รับ
// แสงมาก ต้านทานน้อย แรงดันมาก
// แสงน้อย ต้านทานมาก แรงดันน้อย

void setup() {
  // put your setup code here, to run once:
  // เรียกใช้งาน Serial Monitor
  Serial.begin(115200);
}

void loop() {
  // สร้างตัวแปรสำหรับการรับค่าที่อ่านได้เป็นสัญญาณแอนาล็อคจาก pin A0;
  int Temp = analogRead(A0);
  // แสดงค่าตัวแปร Temp ที่รับได้
  Serial.println(Temp);
  delay(250);
}
