# Robot Control Project

![Arduino Logo](https://www.arduino.cc/en/uploads/Trademark/ArduinoCommunityLogo.png)

This repository contains the code for controlling a robot using an Arduino and Adafruit Motor Shield.

## Features
- Maze Solving Mode
- Line Following Mode
- Switch between modes using a button
- Basic algorithm implementations

## Setup
1. Connect the Adafruit Motor Shield to your Arduino board.
2. Connect the infrared sensors to the specified pins.
3. Upload the code to your Arduino board.

## Usage
Switch between modes using the mode switch button. In Maze Solving mode, the robot navigates a maze based on IR sensor readings. In Line Following mode, the robot follows a line using the sensors.

## Code Sample
```cpp
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
```

## Contributing
Feel free to contribute to this project by opening issues or pull requests.

## License
This project is licensed under the MIT License.