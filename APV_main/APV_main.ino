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

#define PING_HEIGHT 3
#define EDGE_NOISE 5

int currColorL[3];
int currColorR[3];
 
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

void getColorR(int arr[]){
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

void getColorL(int arr[]){
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

void goStraight(int t) 
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

void goBackward(int t) 
{

  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 200);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  analogWrite(EnB, 200);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void goBackwardCurve(int t) 
{

  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  analogWrite(EnA, 150);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  analogWrite(EnB, 100);
  delay(t);

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
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
void loop()
{
  getColorR(currColorR);
  for (int i = 0; i < 3; i++){
    Serial.print(currColorR[i]);
    Serial.print(",");
  }
  Serial.println();
  
  if (ping() < PING_HEIGHT+EDGE_NOISE) {
     goStraight(5);
  } else {
    goBackwardCurve(1000);
  }
}
