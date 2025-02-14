#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150   // Minimum pulse length count
#define SERVOMAX 600   // Maximum pulse length count
#define NUM_SERVOS 7   // Number of servos

void moveServo(int channel, int angle) {
    if (channel >= 0 && channel < NUM_SERVOS && angle >= 0 && angle <= 180) { // Ensure values are within range
        int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(channel, 0, pulse);
        Serial.print("Servo ");
        Serial.print(channel);
        Serial.print(" moved to angle: ");
        Serial.println(angle);
    }
}

void setup() {
    pwm.begin();
    pwm.setPWMFreq(50); // Analog servos run at ~50 Hz
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int channel = Serial.parseInt();
        int angle = Serial.parseInt();
        if (Serial.read() == '\n') {  // Ensure complete command is received
            moveServo(channel, angle);
        }
    }
}
