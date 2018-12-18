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

#define STOPPING_DIST 15

#define DT 100

int currColorL[3];
int currColorR[3];
int currDist;
int cleanedDriveways = 0;

bool isGreen(int arr[]){
  return true;
}
bool isRed(int arr[]){
  return true;
}
bool isBlack(int arr[]){
  return true;
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
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(S0R, OUTPUT);
  pinMode(S1R, OUTPUT);
  pinMode(S2R, OUTPUT);
  pinMode(S3R, OUTPUT);
  pinMode(sensorOutR, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0R,HIGH);
  digitalWrite(S1R,LOW);
}

void getColorL(int arr[]){
  int frequency = 0;
  
  digitalWrite(S2R,LOW);
  digitalWrite(S3R,LOW);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = map(frequency, 18,152,255,0);
  arr[0] = frequency;

  digitalWrite(S2R,HIGH);
  digitalWrite(S3R,HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = map(frequency, 20,176,255,0);
  arr[1] = frequency;

  digitalWrite(S2R,LOW);
  digitalWrite(S3R,HIGH);
  frequency = pulseIn(sensorOutR, LOW);
  frequency = map(frequency, 14,114,255,0);
  arr[2] = frequency;
}

void getColorR(int arr[]){
  int frequency = 0;
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 2,31,255,0);
  arr[0] = frequency;

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 2,34,255,0);
  arr[1] = frequency;

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 2,23,255,0);
  arr[2] = frequency;
}

void carStraight(int t) 
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  analogWrite(EnA, 180);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  analogWrite(EnB, 180);
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
void carStop(int t){
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
void printColor(int arr[], String color){
  Serial.print(color);
  Serial.print(": ");
  for (int i = 0; i < 3; i++){
    Serial.print(arr[i]);
    Serial.print(",");
  }
  Serial.println();
}
bool GREEN() {
  turnLeft();
  plowForward();
  reverse()
  turnRight()
  plowForward();
  return true;
}
void loop()
{ 
  
  getColorL(currColorL);
  getColorR(currColorR);
  currDist = ping();

  // PRINT FOR DEBUGGING
  printColor(currColorL, "Left");
  printColor(currColorR, "Right");

  if (currDist < STOPPING_DIST){
    carStop(DT);
  } else {
    if (isGreen(currColorL) || isGreen(currColorR)){
      if (GREEN()){
        cleanedDriveways++;
      } else {
        carEmergency(DT);
      }
    }
    else if (isBlack(currColorL) && isBlack(currColorR)){
      carStraight(DT);
    }
    else if (isBlack(currColorL) && isRed(currColorR)){
      carAdjustLeft(DT);
    }
    else if (isRed(currColorL) && isBlack(currColorR)){
      carAdjustRight(DT);
    }
    else {
      carEmergency(DT);
    }
  }
}
