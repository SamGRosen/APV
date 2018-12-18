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

#define STOPPING_DIST 8

#define DT 20

int currColorL[3];
int currColorR[3];
int currDist;
int cleanedDriveways = 0;

bool isGreen(int arr[]) {
  return arr[0] < 100 && arr[1] > 100 && arr[2] < 100;
}
bool isRed(int arr[]) {
  return arr[0] > 100 && arr[1] < 100 && arr[2] < 100;
}
bool isBlack(int arr[]) {
  return arr[0] < 100 && arr[1] < 100 && arr[2] < 100;
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
  frequency = map(frequency, 18, 130, 255, 0);
  arr[0] = frequency;

  digitalWrite(S2R, HIGH);
  digitalWrite(S3R, HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = map(frequency, 19, 162, 255, 0);
  arr[1] = frequency;

  digitalWrite(S2R, LOW);
  digitalWrite(S3R, HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = map(frequency, 13, 111, 255, 0);
  arr[2] = frequency;
}

void getColorR(int arr[]) {
  int frequency = 0;

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 4, 23, 255, 0);
  arr[0] = frequency;

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 4, 30, 255, 0);
  arr[1] = frequency;

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 0, 8, 255, 0);
  arr[2] = frequency;
}

void carStraight(int t)
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 120);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 120);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
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

// PRINT FOR DEBUGGING
void printColor(int arr[], String color) {
  Serial.print(color);
  Serial.print(": ");
  for (int i = 0; i < 3; i++) {
    Serial.print(arr[i]);
    Serial.print(",");
  }
  Serial.println();
}
void turnLeft() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 100);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 150);
  delay(1500);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void reverse() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 80);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  analogWrite(EnB, 80);
  delay(1000);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void turnRight() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 120);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 80);
  delay(1500);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
bool GREEN() {
  turnLeft();
  delay(100);
  carStraight(1000);
  delay(100);
  reverse();
  delay(100);
  turnRight();
  delay(100);
  carStraight(1000);
  delay(100);
  return true;
}
void carAdjustLeft(int t)
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 100);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 80);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void carAdjustRight(int t)
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 80);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 100);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void updatePosition() {
  if (currDist < STOPPING_DIST) {
    Serial.println("sees object");
    carStop(DT);
  } else {
    if (isGreen(currColorL) || isGreen(currColorR)) {
      Serial.println("green");
      if (GREEN()) {
        cleanedDriveways++;
      } else {
        carStop(DT);
      }
    }
    else if (isBlack(currColorL) && isBlack(currColorR)) {
      Serial.println("straight");
      carStraight(DT);
    }
    else if (isBlack(currColorL) && !isBlack(currColorR)) {
      Serial.println("adjusting left");
      carAdjustLeft(DT);
    }
    else if (!isBlack(currColorL) && isBlack(currColorR)) {
      Serial.println("adjusting right");
      carAdjustRight(DT);
    }
    else {
      Serial.println("emergency");
      carStop(DT);
    }
  }
}


void loop()
{

  getColorL(currColorL);
  getColorR(currColorR);
  currDist = ping();

  // PRINT FOR DEBUGGING
  //printColor(currColorL, "Left");
  //printColor(currColorR, "Right");
  delay(5);
  updatePosition();
}
