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

#define PING_HEIGHT 3
#define EDGE_NOISE 5

int currColor[3];
 
void setup()
{
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
}

void getColor(int arr[]){
  int frequency = 0;
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  frequency = pulseIn(sensorOut, LOW);
  arr[0] = frequency;

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequency = pulseIn(sensorOut, LOW);
  arr[1] = frequency;

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);

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
  getColor(currColor);
  
  if (ping() < PING_HEIGHT+EDGE_NOISE) {
     goStraight(5);
  } else {
    goBackwardCurve(1000);
  }
}
