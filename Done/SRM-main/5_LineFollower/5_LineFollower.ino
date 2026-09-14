#include <Arduino.h>

// -------- Motor Pins --------
#define ENA 4
#define IN1 1
#define IN2 2

#define ENB 5
#define IN3 9
#define IN4 10

// -------- Variables --------
int speedPercent = 50;
int speedPWM = 127;

String input = "";

// -------- Setup --------
void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Enter Command: F50 B50 L50 R50 S");
}

// -------- Motor Functions --------
void forward() {
  // Motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedPWM);

  // Motor B (FIXED)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedPWM);
}

void backward() {
  // Motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedPWM);

  // Motor B (FIXED)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedPWM);
}

void left() {
  // Left turn → left motor reverse, right motor forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedPWM);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedPWM);
}

void right() {
  // Right turn → left motor forward, right motor reverse
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedPWM);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedPWM);
}
void stopMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// -------- Command Handler --------
void processCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd.length() == 0) return;

  char action = cmd.charAt(0);

  if (action == 'S') {
    stopMotor();
    Serial.println("STOP");
    return;
  }

  int value = cmd.substring(1).toInt();

  if (value < 0) value = 0;
  if (value > 100) value = 100;

  speedPercent = value;
  speedPWM = map(speedPercent, 0, 100, 0, 255);

  Serial.print("Command: ");
  Serial.print(action);
  Serial.print(" Speed: ");
  Serial.print(speedPercent);
  Serial.println("%");

  switch (action) {
    case 'F':
      forward();
      break;

    case 'B':
      backward();
      break;

    case 'L':
      left();
      break;

    case 'R':
      right();
      break;

    default:
      Serial.println("Invalid Command");
      stopMotor();
      break;
  }
}

// -------- Loop --------
void loop() {

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      processCommand(input);
      input = "";
    } else {
      input += c;
    }
  }
}