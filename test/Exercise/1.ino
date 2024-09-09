// Code 7 segment;
// Code ตัวนี้อาจจะไม่ได้มีให้เปลี่ยนตัวเลข digit อื่น ๆ เอาไว้สำหรับการเตรียมสอบ IoT ในวันจันทร์ที่ 9 กันยนยน เท่านั้น!
// สร้างตัวแปรสำหรับการกำหนดให้ไฟสว่างคล้าย ๆ กับ LED
int segmentA = A0;
int segmentB = A1;
int segmentC = A2;
int segmentD = 2;
int segmentE = 4;
int segmentF = 7;
int segmentG = 8;
int segmentDP = 13;
int led = 6;
int num;

// กำหนด Pin ให้ส่งสัญญาณขาออก (ลักษณะคล้าย ๆ กับการทำให้ LED สว่าง)
void setup(){
  Serial.begin(115200);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(segmentDP, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop(){
  int Temp = analogRead(A3);
  Serial.println(Temp);
  // เรียกใช้งานฟังก์ชันที่ชื่อว่า DisplayNumber();
  // displayNumber();
  if(Temp<800){
    num++;
    displaySegment(num);
    delay(1000);
  }
  if(num==6){
    for(int i = 0; i<=2; i++){
      digitalWrite(led, 1);
      delay(250);
      digitalWrite(led, 0);
      delay(250);
    num = 0;
    }
  }
}


// void displayNumber(){
//   // สร้างลูปสำหรับการแสดงผลตัวเลขตั้งแต่ 0-9 ใน 7 segment
//   for(int NumberDigit = 0; NumberDigit <= 9; NumberDigit++){
//     displaySegment(NumberDigit);
//     delay(500);
//   }
// }

// ฟังก์ชันสำหรับการรับค่าแต่ละตัวแล้วเอามาแสดงใน 7 segment
void segment(byte A,byte B,byte C,byte D,byte E,byte F,byte G,byte DP){
  digitalWrite(segmentA, A);
  digitalWrite(segmentB, B);
  digitalWrite(segmentC, C);
  digitalWrite(segmentD, D);
  digitalWrite(segmentE, E);
  digitalWrite(segmentF, F);
  digitalWrite(segmentG, G);
  digitalWrite(segmentDP, DP);
}

// ฟังก์ชันสำหรับการเปิด-ปิด 7 segment ให้เป็นตัวเลขตั้งแต่ 0-9
void displaySegment(int numberToDisplay){
  switch(numberToDisplay){
    // number 0
    case 0:
    segment(1,1,1,1,1,1,0,0);
    break;
    // number 1 
    case 1:
    segment(0,1,1,0,0,0,0,0);
    break;
    // number 2
    case 2:
    segment(1,1,0,1,1,0,1,0);
    break;
    // number 3
    case 3:
    segment(1,1,1,1,0,0,1,0);
    break;
    // number 4
    case 4:
    segment(0,1,1,0,0,1,1,0);
    break;
    // number 5
    case 5:
    segment(1,0,1,1,0,1,1,0);
    break;
    // number 6
    case 6:
    segment(1,0,1,1,1,1,1,0);
    break;
    // number 7
    case 7:
    segment(1,1,1,0,0,0,0,0);
    break;
    // number 8
    case 8:
    segment(1,1,1,1,1,1,1,0);
    break;
    // number 9
    case 9:
    segment(1,1,1,1,0,1,1,0);
    break;
  }
}
