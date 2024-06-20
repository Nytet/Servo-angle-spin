#include <Arduino.h>

// Define servo pin and PWM channel
#define SERVO_PIN 32
#define SERVO_CHANNEL 1

// Servo control variables
const int servoMinUs = 500;   // Minimum pulse width in microseconds
const int servoMaxUs = 2400;  // Maximum pulse width in microseconds
const int servoMaxAngle = 180; // Maximum angle for the servo

// Function to set servo angle
void setServoAngle(int angle) {
  // Map the angle to the pulse width
  int dutyCycle = map(angle, 0, servoMaxAngle, servoMinUs, servoMaxUs);
  // Convert the pulse width to duty cycle for 13-bit resolution
  dutyCycle = (dutyCycle * 8192) / 20000; // 8192 is 2^13 (13-bit resolution)
  // Write the duty cycle to the PWM channel
  ledcWrite(SERVO_CHANNEL, dutyCycle);
}

void setup() {
  // Initialize the serial monitor
  Serial.begin(115200);

  // Configure the PWM channel for the servo control
  ledcSetup(SERVO_CHANNEL, 50, 13);  // 50 Hz frequency, 13-bit resolution
  ledcAttachPin(SERVO_PIN, SERVO_CHANNEL);  // Attach the servo pin to the PWM channel

  // Set the initial servo position to 90 degrees (center)
  setServoAngle(90);

  Serial.println("Setup completed. Enter angle (0-180):");
}

void loop() {
  // Check if data is available on the Serial Monitor
  if (Serial.available() > 0) {
    // Read the input as a string
    String input = Serial.readStringUntil('\n');
    // Trim any whitespace characters
    input.trim();
    
    // Convert the input to an integer
    int angle = input.toInt();

    // Ensure the angle is within the valid range
    if (angle >= 0 && angle <= 180) {
      // Set the servo to the specified angle
      setServoAngle(angle);
      Serial.print("Servo moved to: ");
      Serial.print(angle);
      Serial.println(" degrees");
    } else {
      Serial.println("Invalid angle. Please enter a value between 0 and 180.");
    }
  }
}
