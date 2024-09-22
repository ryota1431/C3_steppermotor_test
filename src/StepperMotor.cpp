#include "StepperMotor.h"

StepperMotor::StepperMotor(int dir, int step, int stepsPerRev) 
    : dirPin(dir), stepPin(step), stepsPerRevolution(stepsPerRev), 
      currentSpeed(0), isClockwise(true), lastStepTime(0), stepInterval(0) {
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
}

void StepperMotor::setSpeedFromJoystick(int joystickValue) {
    // ジョイスティック値を-512から511の範囲と仮定
    isClockwise = joystickValue >= 0;
    digitalWrite(dirPin, isClockwise ? HIGH : LOW);

    int absSpeed = abs(joystickValue);
    if (absSpeed < 50) {  // デッドゾーン
        currentSpeed = 0;
        stepInterval = 0;
    } else {
        currentSpeed = map(absSpeed, 50, 512, 1, 100);  // 速度を1-100の範囲にマッピング
        stepInterval = map(currentSpeed, 1, 100, 5000, 500);  // 速度に応じてステップ間隔を調整（マイクロ秒）
    }
}

void StepperMotor::update() {
    if (currentSpeed == 0) return;

    unsigned long currentTime = micros();
    if (currentTime - lastStepTime >= stepInterval) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2);  // パルス幅を2マイクロ秒に設定
        digitalWrite(stepPin, LOW);
        lastStepTime = currentTime;
    }
}