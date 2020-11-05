String command;
 
void setup() {
    Serial.begin(9600); 
}
 
void loop() {
    if(Serial.available()){
        command = Serial.readStringUntil('\n');
          if(command.equals("hello")){
            Serial.println("test");
          } else {
            Serial.println(command);
          }
    }
}
