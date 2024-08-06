#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial serialBT;

// Bluetooth signal store in this variable
char btSignal;

// Initial Speed
int Speed = 200;

// PWM Pins for Controlling the speed
int enA = 2;  // Enable pin for right motor
int enB = 4; // Enable pin for left motor

// Motor controlling pins
int IN1 = 21; // Right motor input 1
int IN2 = 19; // Right motor input 2
int IN3 = 5; // Left motor input 1
int IN4 = 18; // Left motor input 2

void setup() {
  Serial.begin(115200);
  
  // Bluetooth Name
  serialBT.begin("bluethooth car");
  
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initial State of Car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  while (serialBT.available()) {
    btSignal = serialBT.read();
    
    // Speed control
    if (btSignal >= '0' && btSignal <= '9') {
      Speed = map(btSignal - '0', 0, 9, 100, 240);
    } else if (btSignal == 'q') {
      Speed = 255;
    }
    
    // To see the incoming signal in serial monitor
    Serial.println(btSignal);
    
    // Movement control
    switch(btSignal) {
      case 'B': backward(); break;
      case 'F': forward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stop(); break;
    }
  }
}

// Functions for motor control
void backward() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}