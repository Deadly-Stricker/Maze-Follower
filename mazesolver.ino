#include <Servo.h>

#define LEFT_SENSOR 2
#define FRONT_SENSOR 3
#define RIGHT_SENSOR 4

#define MOTOR_L1 5
#define MOTOR_L2 6
#define MOTOR_R1 9
#define MOTOR_R2 10

int speedValue = 40;  // Adjust this value (0 to 255) to control speed

void setup() {
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(FRONT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);

    pinMode(MOTOR_L1, OUTPUT);
    pinMode(MOTOR_L2, OUTPUT);
    pinMode(MOTOR_R1, OUTPUT);
    pinMode(MOTOR_R2, OUTPUT);

    Serial.begin(9600);
}

void moveForward() {
    analogWrite(MOTOR_L1, speedValue);
    analogWrite(MOTOR_L2, 0);
    analogWrite(MOTOR_R1, speedValue);
    analogWrite(MOTOR_R2, 0);
}

void turnRight() {
    analogWrite(MOTOR_L1, speedValue);
    analogWrite(MOTOR_L2, 0);
    analogWrite(MOTOR_R1, 0);
    analogWrite(MOTOR_R2, speedValue);
    delay(500);
}

void turnLeft() {
    analogWrite(MOTOR_L1, 0);
    analogWrite(MOTOR_L2, speedValue);
    analogWrite(MOTOR_R1, speedValue);
    analogWrite(MOTOR_R2, 0);
    delay(500);
}

void stopRobot() {
    analogWrite(MOTOR_L1, 0);
    analogWrite(MOTOR_L2, 0);
    analogWrite(MOTOR_R1, 0);
    analogWrite(MOTOR_R2, 0);
}

void loop() {
    int left = digitalRead(LEFT_SENSOR);
    int front = digitalRead(FRONT_SENSOR);
    int right = digitalRead(RIGHT_SENSOR);

    Serial.print("L: "); Serial.print(left);
    Serial.print(" F: "); Serial.print(front);
    Serial.print(" R: "); Serial.println(right);

    if (front == HIGH) {  // If there's a wall ahead
        stopRobot();
        delay(300);
        if (right == LOW) {  // If no wall on the right
            turnRight();
        } else if (left == LOW) {  // If no wall on the left
            turnLeft();
        } else {  // Dead end, turn around
            turnRight();
            turnRight();
        }
    } else {  // Move forward if no wall in front
        moveForward();
    }

    delay(100);
}
