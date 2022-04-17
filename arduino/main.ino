// Basic driving mechanics.  The logic will be handled via serial, and assumed to be sent via a raspberry pi.

// Include the library
#include <L298NX2.h>

// Pin defintion
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;


// Create one motor instance
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup()
{
  // Used to display information
  Serial.begin(9600);

  // Wait for Serial Monitor to be opened
  while (!Serial)
  {
    //do nothing
  }

  // Set initial speed
  motors.setSpeedA(70);
  motors.setSpeedB(70);
}

void loop()
{

  if (Serial.available() > 0) {
    int command = Serial.read() - '0';
    
    switch (command) {
      case 0:
        motors.forwardA();
        motors.forwardB();
        printSomeInfo();
        motors.stop();
        break;
      case 1:
        motors.backwardA();
        motors.backwardB();
        printSomeInfo();
        motors.stop();
        break;
      case 2:
        motors.forwardA();
        printSomeInfo();
        motors.stop();
        break;
      case 3:
        motors.forwardB();
        printSomeInfo();
        motors.stop();
        break;
      default: 
        // do nothing
        motors.stop();
        break;
    }
  }
}

/*
Print some informations in Serial Monitor
*/
void printSomeInfo()
{
  // Keeping verbose output to read stdout from the pi for debugging purposes
  Serial.print("Motor A is moving = ");
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedB());
}
