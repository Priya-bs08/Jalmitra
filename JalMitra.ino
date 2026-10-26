/*
  JalMitra — ESP32 starter firmware
  Status: prototype scaffold, not field-ready.
  Serial commands at 115200 baud:
    F = forward, B = backward, L = left, R = right, S = stop

  IMPORTANT:
  - Do not connect motors directly to ESP32 GPIO.
  - Confirm driver logic, current ratings, pin compatibility, and fail-safe behavior.
  - This sketch outputs direction/PWM signals to a compatible motor driver.
  - Depth sensor integration is intentionally left as a clearly marked placeholder.
*/

#include <Arduino.h>

const int LEFT_PWM  = 25;
const int LEFT_IN1  = 26;
const int LEFT_IN2  = 27;
const int RIGHT_PWM = 14;
const int RIGHT_IN1 = 12;
const int RIGHT_IN2 = 13;

const int PWM_FREQ = 1000;
const int PWM_RESOLUTION = 8;
const int LEFT_PWM_CHANNEL = 0;
const int RIGHT_PWM_CHANNEL = 1;
const int DEFAULT_SPEED = 120; // 0..255; start low during bench tests
const unsigned long COMMAND_TIMEOUT_MS = 1500;

unsigned long lastCommandMs = 0;
char currentCommand = 'S';

void setMotor(int in1, int in2, int pwmChannel, int speedValue) {
  speedValue = constrain(speedValue, -255, 255);
  if (speedValue > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(pwmChannel, speedValue);
  } else if (speedValue < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(pwmChannel, -speedValue);
  } else {
    ledcWrite(pwmChannel, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void stopMotors() {
  setMotor(LEFT_IN1, LEFT_IN2, LEFT_PWM_CHANNEL, 0);
  setMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM_CHANNEL, 0);
  currentCommand = 'S';
}

void drive(char command) {
  switch (command) {
    case 'F':
      setMotor(LEFT_IN1, LEFT_IN2, LEFT_PWM_CHANNEL, DEFAULT_SPEED);
      setMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM_CHANNEL, DEFAULT_SPEED);
      break;
    case 'B':
      setMotor(LEFT_IN1, LEFT_IN2, LEFT_PWM_CHANNEL, -DEFAULT_SPEED);
      setMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM_CHANNEL, -DEFAULT_SPEED);
      break;
    case 'L':
      setMotor(LEFT_IN1, LEFT_IN2, LEFT_PWM_CHANNEL, -DEFAULT_SPEED);
      setMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM_CHANNEL, DEFAULT_SPEED);
      break;
    case 'R':
      setMotor(LEFT_IN1, LEFT_IN2, LEFT_PWM_CHANNEL, DEFAULT_SPEED);
      setMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM_CHANNEL, -DEFAULT_SPEED);
      break;
    case 'S':
    default:
      stopMotors();
      return;
  }
  currentCommand = command;
}

void setup() {
  Serial.begin(115200);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);

  ledcSetup(LEFT_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(RIGHT_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LEFT_PWM, LEFT_PWM_CHANNEL);
  ledcAttachPin(RIGHT_PWM, RIGHT_PWM_CHANNEL);

  stopMotors();
  lastCommandMs = millis();
  Serial.println("JalMitra starter ready. Commands: F B L R S");
}

void loop() {
  if (Serial.available() > 0) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    line.toUpperCase();

    if (line.length() == 1 && String("FBLRS").indexOf(line.charAt(0)) >= 0) {
      char command = line.charAt(0);
      drive(command);
      lastCommandMs = millis();
      Serial.print("ACK ");
      Serial.println(command);
    } else if (line.length() > 0) {
      stopMotors();
      Serial.println("ERR invalid command; motors stopped");
      lastCommandMs = millis();
    }
  }

  // Fail-safe: stop if the operator's command stream goes quiet.
  if (millis() - lastCommandMs > COMMAND_TIMEOUT_MS) {
    stopMotors();
  }

  // TODO: Add a supported depth sensor library and validated sensor read here.
  // TODO: Add battery voltage monitoring and a hardware emergency stop.
}
