#include <AFMotor.h>

AF_DCMotor motor1(1); // Initialize motors with the appropriate motor numbers
AF_DCMotor motor2(2);

int leftIRPin = A0;
int rightIRPin = A1;
int switchPin = 2; // Pin connected to the mode switch button

bool mazeMode = true; // Flag to indicate the current mode

void setup() {
    motor1.setSpeed(255); // Set motor speed
    motor2.setSpeed(255);
    
    pinMode(leftIRPin, INPUT);
    pinMode(rightIRPin, INPUT);
    pinMode(switchPin, INPUT_PULLUP); // Use internal pull-up resistor

    Serial.begin(9600);
}

void loop() {
    int leftIRValue = digitalRead(leftIRPin);
    int rightIRValue = digitalRead(rightIRPin);
    int switchState = digitalRead(switchPin);

    // Check if the mode switch button is pressed
    if (switchState == LOW) {
        delay(50); // Debounce
        if (mazeMode) {
            mazeMode = false; // Switch to Line Following mode
            Serial.println("Switched to Line Following mode");
        } else {
            mazeMode = true; // Switch to Maze Solving mode
            Serial.println("Switched to Maze Solving mode");
        }
        while (digitalRead(switchPin) == LOW) {
            // Wait until the button is released
        }
    }

    if (mazeMode) {
        // Implement maze-solving algorithm logic here
        if (leftIRValue == LOW && rightIRValue == LOW) {
            // Both sensors see a wall, turn left
            motor1.run(FORWARD);
            motor2.run(BACKWARD);
        } else if (leftIRValue == HIGH && rightIRValue == LOW) {
            // Right side is open, turn right
            motor1.run(BACKWARD);
            motor2.run(FORWARD);
        } else if (leftIRValue == LOW && rightIRValue == HIGH) {
            // Left side is open, turn left
            motor1.run(FORWARD);
            motor2.run(BACKWARD);
        } else {
            // Both sides are open, move forward
            motor1.run(FORWARD);
            motor2.run(FORWARD);
        }
    } else {
        // Implement line-following algorithm logic here
        if (leftIRValue == HIGH && rightIRValue == HIGH) {
            // Both sensors on the line, move forward
            motor1.run(FORWARD);
            motor2.run(FORWARD);
        } else if (leftIRValue == LOW && rightIRValue == HIGH) {
            // Left sensor off the line, adjust left motor
            motor1.run(FORWARD);
            motor2.run(SLOW_FORWARD);  // Slightly slower speed
        } else if (leftIRValue == HIGH && rightIRValue == LOW) {
            // Right sensor off the line, adjust right motor
            motor1.run(SLOW_FORWARD);  // Slightly slower speed
            motor2.run(FORWARD);
        } else {
            // Both sensors off the line, adjust both motors
            motor1.run(SLOW_FORWARD);  // Slightly slower speed
            motor2.run(SLOW_FORWARD);  // Slightly slower speed
        }
    }
}
