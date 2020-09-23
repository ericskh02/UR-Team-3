String command;
 
void setup() {
    Serial.begin(9600); 
}
 
void loop() {
    if(Serial.available()){
        command = Serial.readStringUntil('\n');
         
        if(command.equals("init")){
            initialize();
        }
        else if(command.equals("send")){
            send_message();
        }
        else if(command.equals("data")){
            get_data();
        }
        else if(command.equals("reboot")){
            reboot();
        }
        else{
          println(command);
        }
    }
}
