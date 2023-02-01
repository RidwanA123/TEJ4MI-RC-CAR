#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
int acButton = 2;
int brButton = 3;

const byte address[6] = "00001";

void setup() {
  pinMode(acButton, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(brButton, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  if (digitalRead(acButton) == LOW) {
     const char text[] = "1";
     Serial.println("A");
  radio.write(&text, sizeof(text));
  }
  
   else if(digitalRead(brButton) == LOW) {
        const char text[] = "2";
         Serial.println("B");
  radio.write(&text, sizeof(text));
    }
   else {
      const char text[] = "0";
       Serial.println("OFF");
  radio.write(&text, sizeof(text));
   }

  


}
