#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;
int button = 8;

// number 1
const uint32_t one[] = {
  0x0E01E036,
  0x00600600,
  0x601F81F8
};

// number 2
const uint32_t two[] = {
  0x0E01B031,
  0x80300600,
  0xC01F83F8
};

// number 3
const uint32_t three[] = {
  0x0E01B031,
  0x80700703,
  0x181B00E0
};

// number 4
const uint32_t four[] = {
  0x0600F01B,
  0x033C7FC0,
  0x600601F8
};

// number 5
const uint32_t five[] = {
  0x1F818018,
  0x01F800C1,
  0x8410C1F8
};

// number 6
const uint32_t six[] = {
  0x01803006,
  0x00C01F81,
  0x081980F0
};

// number 7
const uint32_t seven[] ={
  0x1F801803,
  0x00600C01,
  0x80300600
};

// number 8
const uint32_t eight[] = {
  0x1F830C60,
  0x63FC30C6,
  0x0630C1F8
};

// number 9
const uint32_t nine[] = {
  0x1F830C30,
  0xC1F80180,
  0x300600C0
};

// number 0
const uint32_t zero[] = {
  0x1F830C60,
  0x66066066,
  0x0630C1F8
};

void setup() {
  matrix.begin();
}



void loop() {
  // matrix.loadFrame = การแสดงผลที่ต้องการตามที่ตัวเองได้ Render มา
  matrix.loadFrame(one);
  delay(500);
  matrix.loadFrame(two);
  delay(500);
  matrix.loadFrame(three);
  delay(500);
  matrix.loadFrame(four);
  delay(500);
  matrix.loadFrame(five);
  delay(500);
  matrix.loadFrame(six);
  delay(500);
  matrix.loadFrame(seven);
  delay(500);
  matrix.loadFrame(eight);
  delay(500);
  matrix.loadFrame(nine);
  delay(500);
  matrix.loadFrame(zero);
  delay(500);
}
