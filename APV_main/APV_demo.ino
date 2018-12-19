#define EnA 10
#define EnB 5
#define In1 9
#define In2 8
#define In3 7
#define In4 6

#define trigPin 12
#define echoPin 13

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define sensorOut 4

#define S0R A0
#define S1R A1
#define S2R A2
#define S3R A3
#define sensorOutR A4

#define GREEN 1
#define RED 2
#define BLACK 3

#define DT 300
#define MOVE_DELAY 50

#define STOPPING_DIST 10

int currColorL[3];
int currColorR[3];
int pingDist;

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
long ping() {
  long duration, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  return cm;
}

bool isGreenL(int arr[]) {
  return arr[0] < 170 && arr[1] > 170 && arr[2] < 170;
}
bool isRedL(int arr[]) {
  return arr[0] > 60 && arr[1] < 100 && arr[2] < 100;
}
bool isBlackL(int arr[]) {
  return arr[0] < 100 && arr[1] < 100 && arr[2] < 100;
}
int interpretColor(int arr[]){
  if (isGreenL(arr)){
    return GREEN;
  } else if (isRedL(arr)){
    return RED;
  } else {
    return BLACK;
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(S0R, OUTPUT);
  pinMode(S1R, OUTPUT);
  pinMode(S2R, OUTPUT);
  pinMode(S3R, OUTPUT);
  pinMode(sensorOutR, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0R, HIGH);
  digitalWrite(S1R, LOW);
}
void getColorL(int arr[]) {
  int frequency = 0;

  digitalWrite(S2R, LOW);
  digitalWrite(S3R, LOW);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = max(map(frequency, 18, 130, 255, 0), 0);
  arr[0] = frequency;

  digitalWrite(S2R, HIGH);
  digitalWrite(S3R, HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = max(map(frequency, 19, 162, 255, 0), 0);
  arr[1] = frequency;

  digitalWrite(S2R, LOW);
  digitalWrite(S3R, HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = max(map(frequency, 13, 111, 255, 0), 0);
  arr[2] = frequency;
}
void getColorR(int arr[]) {
  int frequency = 0;

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = max(map(frequency, 4, 25, 255, 0), 0);
  arr[0] = frequency;

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = max(map(frequency, 4, 32, 255, 0), 0);
  arr[1] = frequency;

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = max(map(frequency, 2, 22, 255, 0), 0);
  arr[2] = frequency;
}
void carStop(int t) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 0);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 0);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void carStraight(int t) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 200);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 200);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}


void turnLeft() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 120);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 150);
  delay(1500);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}


void turnLeft(int t) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 70);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 200);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void reverse(int t) {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 120);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  analogWrite(EnB, 120);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void turnRight() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 150);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 120);
  delay(1500);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}


void turnRight(int t) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 200);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 70);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
//void updatePosition(int leftColor, int rightColor) {
//  if (leftColor == GREEN || rightColor == GREEN) {
//    Serial.println("green");
//  // GREEN_()
//  }
//  else if (leftColor == BLACK && rightColor == BLACK) {
//    Serial.println("straight");
//    carStraight(DT/2);
//  }
//  else if (leftColor == BLACK && rightColor != BLACK) {
//    Serial.println("adjusting to the right");
//    turnRight(DT/2);
//    //carStop(DT);
//  }
//  else if (leftColor != BLACK && rightColor == BLACK) {
//    Serial.println("adjusting to the left");
//    turnLeft(DT/2);
//    //carStop(DT);
//  }
//  else {
//    Serial.println("emergency");
//    carStop(DT);
//  }
//}
void carTurnAround(int t) {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 200);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 200);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void updatePosition(int leftColor, int rightColor){
  if (leftColor == GREEN || rightColor == GREEN){
    Serial.println("GREEN");
    AVOID_();
  } else if (leftColor == BLACK && rightColor == BLACK) {
    carStraight(DT/2);
    Serial.println("straight");
  } else if (leftColor!= BLACK || rightColor!= BLACK) {
    carTurnAround(1000);
    Serial.println("turning");
  } else {
    carStop(DT);
  }
}

bool AVOID_() {
  delay(1000);
  reverse(750);
  delay(1000);
  carTurnAround(500);
  delay(1000);
  return true;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(MOVE_DELAY);
  getColorL(currColorL);
  getColorR(currColorR);
  pingDist = ping();

  int left = interpretColor(currColorL);
  int right = interpretColor(currColorR);
  Serial.println(pingDist);

  if (pingDist < STOPPING_DIST){
     Serial.println("seen object");
     AVOID_();
  } else {
     updatePosition(left, right);
  }
}
