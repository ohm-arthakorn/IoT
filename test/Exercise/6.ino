#include "Arduino_LED_Matrix.h"  // Include the LED_Matrix library
ArduinoLEDMatrix matrix;         // Create an instance of the ArduinoLEDMatrix class
const uint32_t frames[][4] = {
  { 0x00000100, 0x00010010, 0x01001000, 100 },
  { 0x00000300, 0x00030020, 0x02003000, 100 },
  { 0x00000700, 0x00060040, 0x04007000, 100 },
  { 0x00000F00, 0x100D0090, 0x0900F000, 100 },
  { 0x00001E00, 0x201A0120, 0x1201E000, 100 },
  { 0x00003D00, 0x50350240, 0x2403D000, 100 },
  { 0x00007B00, 0xA05B0480, 0x4806B000, 100 },
  { 0x0000F701, 0x40D70900, 0x900F7000, 100 },
  { 0x0001EF02, 0x81AF1211, 0x211EF000, 100 },
  { 0x0003DE05, 0x034E2422, 0x423DE000, 100 },
  { 0x0007BD0A, 0x16BD4844, 0x847BD000, 100 },
  { 0x000F7B14, 0x2D7B9089, 0x08F7B000, 100 },
  { 0x000EF728, 0x4AF72102, 0x10EF7000, 100 },
  { 0x000DEF50, 0x85EF4214, 0x21DEF000, 100 },
  { 0x000BDEA1, 0x0BDE8428, 0x42BDE000, 100 },
  { 0x0007BD42, 0x07BD0850, 0x857BD000, 100 },
  { 0x000F7B84, 0x1F7A10A1, 0x0AF7B000, 100 },
  { 0x000EF708, 0x2EF42142, 0x14EF7000, 100 },
  { 0x000DEF10, 0x4DE84284, 0x28DEE000, 100 },
  { 0x000BDF20, 0x9BD98518, 0x51BDD000, 100 },
  { 0x0007BE41, 0x27B20A20, 0xA27BA000, 100 },
  { 0x000F7D82, 0x4F651451, 0x45F75000, 100 },
  { 0x000EFB04, 0x9ECA28A2, 0x8AEEA000, 100 },
  { 0x000DF709, 0x2D945145, 0x14DD4000, 100 },
  { 0x000BEF12, 0x4B28A28A, 0x28BA8000, 100 },
  { 0x0007DF24, 0x96514514, 0x51751000, 100 },
  { 0x000FBE49, 0x2CA28A28, 0xA2EA2000, 100 },
  { 0x000F7D92, 0x59451441, 0x44D45000, 100 },
  { 0x000EFB24, 0xA28B2882, 0x88A8B000, 100 },
  { 0x000DF749, 0x45175105, 0x10417000, 100 },
  { 0x000BEF92, 0x8A2FA21A, 0x21A2F000, 100 },
  { 0x0007DE25, 0x045E4424, 0x4245E000, 100 },
  { 0x0, 0x0, 0x0, 100 }
};

int segmentA = A0;
int segmentB = A1;
int segmentC = A2;
int segmentD = 2;
int segmentE = 4;
int segmentF = 7;
int segmentG = 8;
int segmentDP = 13;

void setup() {
  matrix.loadSequence(frames);
  matrix.begin();
  matrix.play(true);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(segmentDP, OUTPUT);
}
void loop() {
  for(int i = 4 ; i<=9 ; i++){
    displaySegment(i);
    delay(600);
  }
}

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