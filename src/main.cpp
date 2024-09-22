#include <Arduino.h>
#include <AccelStepper.h>
#include <WiiChuck.h>
#include <ESP32Servo.h>
// サーボモーターのパラメータ
int pwmPin = D2;
Servo servo;
int minUs = 1000;
int maxUs = 2000;

#define STEP_PIN D1
#define DIR_PIN D0

// ステッパーモーターの設定
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
Accessory Classic;

// ステッパーモーターのパラメータ
const int microStep = 1;
const int maxStep = 800 * microStep;
const int maxSpeed = 800 * microStep;
const int acceleration = 400 * microStep;

// ジョイスティックのパラメータ
const int deadZone = 4;          // デッドゾーンを小さくする
const int maxJoystickValue = 64; // ジョイスティックの最大値
const int minJoystickValue = 0;  // ジョイスティックの最小値
const int cyclePeriod = 1000;    // サイクルの周期
void setup()
{
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.attach(pwmPin, minUs, maxUs);
  Serial.begin(9600);
  Classic.begin();
  // ステッパーモーターの初期設定
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(acceleration);
}

void setSpeedFromJoystick(int joystickValue)
{
  float step;
  if (abs(joystickValue - 32) < deadZone)
  {
    step = 0;
  }
  else
  {
    step = map(joystickValue, minJoystickValue, maxJoystickValue, -maxStep, maxStep);
  }
  stepper.setSpeed(step);
  stepper.move(step);
}

void loop()
{
  Classic.readData();
  int joystickValue = Classic.getJoyYLeft();
  setSpeedFromJoystick(joystickValue);
  int servoValue = map(Classic.getJoyXLeft(), 0, 64, 0, 180);
  servo.write(servoValue);

  // デバッグ出力
  Serial.print("JoyYLeft: ");
  Serial.print(joystickValue);
  Serial.print(", Add Step: ");
  Serial.print(map(joystickValue, minJoystickValue, maxJoystickValue, -maxSpeed, maxSpeed));
  Serial.print(", Servo: ");
  Serial.print(servoValue);
  Serial.print(", Angle:");
  Serial.println(servo.read());
  Serial.print(", Actual Speed(before run): ");
  Serial.print(stepper.speed());
  stepper.runSpeed();
  Serial.print(", Actual Speed(after run): ");
  Serial.println(stepper.speed());
}