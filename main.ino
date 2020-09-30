#define TRIG_2 2
#define ECHO_2 3

void setup(){
  pinMode (12, OUTPUT);
  pinMode (A1, INPUT);
  pinMode(TRIG_2,OUTPUT);
  pinMode(ECHO_2,INPUT);
//  pinMode(TRIG_3,OUTPUT);
//  pinMode(ECHO_3,INPUT);
  Serial.begin (9600);
}

void loop(){
  digitalWrite(12, LOW);
  digitalWrite(TRIG_2, LOW);
  //digitalWrite(TRIG_3, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  digitalWrite(TRIG_2, HIGH);
  //digitalWrite(TRIG_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  digitalWrite(TRIG_2, LOW);
  //digitalWrite(TRIG_3, LOW);
  delayMicroseconds(2);
  double duration_1 = pulseIn(A1, HIGH);
  double distance_1 = (duration_1)*0.034/2;
  Serial.print("sensor 1: ");
  Serial.println(distance_1);
  double duration_2 = pulseIn(ECHO_2, HIGH);
  //int duration_3 = pulseIn(ECHO_3, HIGH);
  double distance_2 = (duration_2)*0.034/2;
  //int distance_3 = (duration_3)*0.034/2;
  Serial.print("sensor 2: ");
  Serial.println(distance_2);
  //Serial.print("sensor 3: ");
  //Serial.println(distance_3);
}
