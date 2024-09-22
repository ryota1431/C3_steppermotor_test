#include <Arduino.h>
#include "StepperMotor.h"

#define DIR_PIN D0
#define STEP_PIN D1

StepperMotor motor(DIR_PIN, STEP_PIN);

int joystickValue = 0;
int count = 0;
int dir = 1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if(count < 511 && count > -511){
    if(dir == 1){
      count++;
      joystickValue = count;  // 0-1023の値を-512から511の範囲に変換
    }else{
      count--;
      joystickValue = count;  // 0-1023の値を-512から511の範囲に変換
    }
    }else if(count >= 511){
      dir = 0;
    }else if(count <= -511){
      dir = 1;
    }
    motor.setSpeedFromJoystick(joystickValue);
    motor.update();

    // デバッグ出力（必要に応じて）
    Serial.print("Joystick: ");
    Serial.println(joystickValue);
    delay(100);  // 短い遅延を入れてCPU負荷を軽減
}
