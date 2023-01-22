//uses VHF to communicate with tech design car

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SharpIR.h>
int command = 0;
SharpIR sensor(GP2Y0A21YK0F, A4);

int servo = 6; 
int MotorF = 4;
int MotorB = 5;


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  pinMode(servo, OUTPUT);
  pinMode(MotorF, OUTPUT);
  pinMode(MotorB, OUTPUT);
  radio.openReadingPipe(0, address);
    pinMode(LED_BUILTIN, OUTPUT);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  int distance = sensor.getDistance();
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    command = atoi(text);
    Serial.println(command);
  if (command == 1) {
   forward();
    
  }
  else if (command == 2) {
   
    backward();
    
  }
   else if (command == 0) {
   
    stopmotor();
    
  }
  else{
    stopmotor();
  }
  
  
  
  }
 
  if (distance < 40) {
//    Serial.println("EMERGENCY STOP");
//    emergencybrake();  (need sensor attached or else it will loop cause arduino skill issue);
}


}
void forward() {
   digitalWrite(MotorF, HIGH);
    digitalWrite(MotorB, LOW);
    
}


void backward() {
   digitalWrite(MotorF, LOW);
    digitalWrite(MotorB, HIGH);
}
void emergencybrake() {
  backward();
  delay(1000);
  stopmotor();
  delay(1000);
  
}
void stopmotor() {
   digitalWrite(MotorF, LOW);
    digitalWrite(MotorB, LOW);
}
