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

#define DT 250

#define QSIZE 10;

// INTENSITY IS MAX AT 0 AND MIN AT 255
#define LEFT_RED_THRESHOLD 30
#define LEFT_GREEN_THRESHOLD 30
// RIGHT HAS MUCH SMALLER RANGE THAN LEFT
#define RIGHT_RED_THRESHOLD 15
#define RIGHT_GREEN_THRESHOLD 15

#define GREEN 100
#define RED 200
#define BLACK 300

int currColorL[3];
int currColorR[3];
int currDist;
int cleanedDriveways = 0;

int leftRedReadingQueue[QSIZE];
int lrrqIndex = 0;
int leftGreenReadingQueue[QSIZE];
int lgrqIndex = 0;
int rightRedReadingQueue[QSIZE];
int rrrqIndex = 0;
int rightGreenReadingQueue[QSIZE];
int rgrqIndex = 0;

int leftColor;
int rightColor;

bool isGreen(int arr[]) {
  return arr[0] < 100 && arr[1] > 100 && arr[2] < 100;
}
bool isRed(int arr[]) {
  return arr[0] > 100 && arr[1] < 100 && arr[2] < 100;
}
bool isBlack(int arr[]) {
  return arr[0] < 100 && arr[1] < 100 && arr[2] < 100;
}

void bubble_sort(int arr[], int arr_size) {
  int i, j;
  for(i = 0; i < arr_size - 1; i ++) {
    for(j = 0; j < arr_size - i - 1; j++) {
      if(arr[j] > arr[j+1]) {
        int tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
    }
  }
}

int getMedian(int arr[], int arr_size) {
 int sorted_arr[arr_size];
 int i = 0;
 for(i = 0; i < QSIZE; i++) {
  sorted_arr[i] = arr[i];
 }

 bubble_sort(sorted_arr, arr_size);

 return sorted_arr[arr_size/2];  
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
//  int frequency = 0;
//
//  digitalWrite(S2R, LOW);
//  digitalWrite(S3R, LOW);
//  frequency = pulseIn(sensorOutR, LOW);
//  Serial.print("Left raw red = ");
//  Serial.println(frequency);
//  frequency = map(frequency, 18, 130, 255, 0);
//  arr[0] = frequency;
//
//  digitalWrite(S2R, HIGH);
//  digitalWrite(S3R, HIGH);
//  frequency = pulseIn(sensorOutR, LOW);
//  Serial.print("Left raw green = ");
//  Serial.println(frequency);
//  frequency = map(frequency, 19, 162, 255, 0);
//  arr[1] = frequency;
//
//  digitalWrite(S2R, LOW);
//  digitalWrite(S3R, HIGH);
//  frequency = pulseIn(sensorOutR, LOW);
//  frequency = map(frequency, 13, 111, 255, 0);
//  arr[2] = frequency;

   // Read red
   int frequency = 0;

   digitalWrite(S2, LOW);
   digitalWrite(S3, LOW);
   frequency = pulseIn(sensorOut, LOW);
   Serial.print("Left raw red = ");
   Serial.println(frequency);
   leftRedReadingQueue[lrrqIndex] = frequency;
   lrrqIndex = (lrrqIndex + 1) % QSIZE;

   // Read green
   digitalWrite(S2, HIGH);
   digitalWrite(S3, HIGH);
   frequency = pulseIn(sensorOut, LOW);
   Serial.print("Left raw green = ");
   Serial.println(frequency);
   leftGreenReadingQueue[lgrqIndex] = frequency;
   lgrqIndex = (lgrqIndex + 1) % QSIZE;

   if(getMedian(leftGreenReadingQueue, QSIZE) < LEFT_GREEN_THRESHOLD) {
     return GREEN;
   } else if (getMedian(leftRedReadingQueue, QSIZE) < LEFT_RED_THRESHOLD) {
     return RED;
   } else {
      return BLACK;
   }
}

void getColorR() {
//  int frequency = 0;
//
//  digitalWrite(S2, LOW);
//  digitalWrite(S3, LOW);
//  frequency = pulseIn(sensorOut, LOW);
//  Serial.print("Right raw red = ");
//  Serial.println(frequency);
//  frequency = map(frequency, 4, 23, 255, 0);
//  arr[0] = frequency;
//
//  digitalWrite(S2, HIGH);
//  digitalWrite(S3, HIGH);
//  frequency = pulseIn(sensorOut, LOW);
//  Serial.print("Right raw green = ");
//  Serial.println(frequency);
//  frequency = map(frequency, 4, 30, 255, 0);
//  arr[1] = frequency;
//
//  digitalWrite(S2, LOW);
//  digitalWrite(S3, HIGH);
//  frequency = pulseIn(sensorOut, LOW);
//  frequency = map(frequency, 0, 8, 255, 0);
//  arr[2] = frequency;

   // Read red
   int frequency = 0;

   digitalWrite(S2, LOW);
   digitalWrite(S3, LOW);
   frequency = pulseIn(sensorOut, LOW);
   Serial.print("Right raw red = ");
   Serial.println(frequency);
   rightRedReadingQueue[rrrqIndex] = frequency;
   rrrqIndex = (rrrqIndex + 1) % QSIZE;

   // Read green
   digitalWrite(S2, HIGH);
   digitalWrite(S3, HIGH);
   frequency = pulseIn(sensorOut, LOW);
   Serial.print("Right raw green = ");
   Serial.println(frequency);
   rightGreenReadingQueue[rgrqIndex] = frequency;
   rgrqIndex = (rgrqIndex + 1) % QSIZE;

   if(getMedian(rightGreenReadingQueue, QSIZE) < RIGHT_GREEN_THRESHOLD) {
     return GREEN;
   } else if (getMedian(rightRedReadingQueue, QSIZE) < RIGHT_RED_THRESHOLD) {
     return RED;
   } else {
      return BLACK;
   }
}

void carStraight(int t)
{
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
  Serial.println("CAR STOPPING");
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
void reverse() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 120);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  analogWrite(EnB, 120);
  delay(1000);

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

  analogWrite(EnA, 140);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 120);
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

  analogWrite(EnA, 120);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 140);
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
        Serial.println("FAILED GREEN");
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

  leftColor = getColorL();
  rightColor = getColorR();
  currDist = ping();

  // PRINT FOR DEBUGGING
  //printColor(currColorL, "Left");
  //printColor(currColorR, "Right");
  delay(50);
  updatePosition();
}
