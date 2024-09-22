#include <Arduino.h>
#define DIR D0
#define STP D1
void setup() {
  // put your setup code here, to run once:
  pinMode(DIR, OUTPUT);
  pinMode(STP, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(DIR, HIGH);
  for(int i=0; i<200; i++){
    digitalWrite(STP, HIGH);
    delay(1);
    digitalWrite(STP, LOW);
    delay(1);
  }
  delay(1000);
  digitalWrite(DIR, LOW);
  for(int i=0; i<200; i++){
    digitalWrite(STP, HIGH);
    delay(1);
    digitalWrite(STP, LOW);
    delay(1);
  }
  delay(1000);
}
