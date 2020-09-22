#include <NewPing.h>
 
#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define TRIGGER_PIN_2 4
#define ECHO_PIN_2 5
#define MAX_DISTANCE 200
 
NewPing sonar1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  delay(1000);
  Serial.print("Ping Sensor1: ");
  Serial.print(sonar1.ping_cm());
  Serial.println("cm");
  Serial.print("Ping Sensor2: ");
  Serial.print(sonar2.ping_cm());
  Serial.println("cm");
}
