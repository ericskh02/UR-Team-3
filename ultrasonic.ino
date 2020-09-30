#define TRIG_1 12
#define ECHO_1 A0
#define TRIG_2 
#define ECHO_2
#define TRIG_3
#define ECHO_3

double distance;
double duration;

void setup(){
  pinMode (TRIG_1, OUTPUT);
  pinMode (ECHO_1, INPUT);
  pinMode(TRIG_2,OUTPUT);
  pinMode(ECHO_2,INPUT);
  pinMode(TRIG_3,OUTPUT);
  pinMode(ECHO_3,INPUT);
  Serial.begin (9600);
}

void loop(){
  digitalWrite(TRIG_1, LOW);
  digitalWrite(TRIG_2, LOW);
  digitalWrite(TRIG_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_1, HIGH);
  digitalWrite(TRIG_2, HIGH);
  digitalWrite(TRIG_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_1, LOW);
  digitalWrite(TRIG_2, LOW);
  digitalWrite(TRIG_3, LOW);
  delayMicroseconds(2);
  duration_1 = pulseIn(ECHO_1, HIGH);
  duration_2 = pulseIn(ECHO_2, HIGH);
  duration_3 = pulseIn(ECHO_3, HIGH);
  distance_1 = duration_1*0.034/2;
  distance_2 = duration_2*0.034/2;
  distance_3 = duration_3*0.034/2;
  Serial.println(distance_1);
  Serial.println(distance_2);
  Serial.println(distance_3);
  delay(1000);
}
