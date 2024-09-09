// declare variables for the motor pins
int motorPin1 = 8;     // Blue
int motorPin2 = 9;     // Pink
int motorPin3 = 10;    // Yellow
int motorPin4 = 11;    // Orange
                       // Red
int motorSpeed = 2;  // Variable to set stepper speed.
int stepCount = 0;     // Number of steps the motor has taken.
int i;

void setup() {
  pinMode(motorPin1, OUTPUT);  // declare the motor as the outputs
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(115200);
}

void fullstep() {
  // 1
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 3
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}

void halfstep() {
  // 1
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 3
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 5
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 6
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  // 7
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  // 8
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}

void wavedrive() {
  // 1
  digitalWrite(motorPin4, 1);
  digitalWrite(motorPin3, 0);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin1, 0);
  delay(motorSpeed);

  //2
  digitalWrite(motorPin4, 0);
  digitalWrite(motorPin3, 1);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin1, 0);
  delay(motorSpeed);

  //3
  digitalWrite(motorPin4, 0);
  digitalWrite(motorPin3, 0);
  digitalWrite(motorPin2, 1);
  digitalWrite(motorPin1, 0);
  delay(motorSpeed);

  //4
  digitalWrite(motorPin4, 0);
  digitalWrite(motorPin3, 0);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin1, 1);
  delay(motorSpeed);
}

void Reverse_wavedrive() {
      // 1
      digitalWrite(motorPin4, 1);
      digitalWrite(motorPin3, 0);
      digitalWrite(motorPin2, 0);
      digitalWrite(motorPin1, 0);
      delay(motorSpeed);

      //2
      digitalWrite(motorPin4, 0);
      digitalWrite(motorPin3, 1);
      digitalWrite(motorPin2, 0);
      digitalWrite(motorPin1, 0);
      delay(motorSpeed);

      //3
      digitalWrite(motorPin4, 0);
      digitalWrite(motorPin3, 0);
      digitalWrite(motorPin2, 1);
      digitalWrite(motorPin1, 0);
      delay(motorSpeed);

      //4
      digitalWrite(motorPin4, 0);
      digitalWrite(motorPin3, 0);
      digitalWrite(motorPin2, 0);
      digitalWrite(motorPin1, 1);
      delay(motorSpeed);
    }



void loop() {
  // 512
  int Temp = analogRead(A0);
  Serial.println(Temp);
  delay(100);
  // wavedrive();  // จ่ายไฟให้ทำงานครั้งละ 1 ขด
  //fullstep();   // จ่ายไฟให้ทำงานครั้งละ 2 ขด
  //halfstep();   // ใช้ทั้งสองแบบรวมกันทำให้หมุนได้ครั้งละ ครึ่ง สเตป
  if(Temp>700){
    for(i=stepCount ; i<=1500 ; i++){
      wavedrive();
    }
    digitalWrite(motorPin1, 0);
    digitalWrite(motorPin2, 0);
    digitalWrite(motorPin3, 0);
    digitalWrite(motorPin4, 0);
    i = 0;
  }
  else if(Temp<400){
    for(i=stepCount ; i<=1000 ; i++){
      Reverse_wavedrive();
    }
    digitalWrite(motorPin1, 0);
    digitalWrite(motorPin2, 0);
    digitalWrite(motorPin3, 0);
    digitalWrite(motorPin4, 0);
    i = 0;
  }
  
  
  // Serial.print("steps: ");
  // Serial.println(stepCount);
  // stepCount++;
}