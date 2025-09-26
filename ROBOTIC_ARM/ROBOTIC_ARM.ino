#include <Servo.h>

Servo servo1;  // Servo on pin 2
Servo servo2;  // Servo on pin 3
Servo servo3;

const int potPin = A0;       // Single potentiometer
const int button1 = 4;       // Controls servo1
const int button2 = 5;       // Controls servo2
const int button3 = 6;       // Controls both servos
int angle1 = 90;             // Current angle for servo1
int angle2 = 90;
int angle3 = 90;             // Current angle for servo2
unsigned long lastUpdateTime = 0;  // For smooth updates (throttle to avoid overload)
int updateInterval = 15;     // ms between pot reads (matches your delay)

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);  // Buttons: HIGH unpressed, LOW pressed
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo1.write(angle1);  // Start at center
  servo2.write(angle2);
  servo3.write(angle3);
  Serial.println("Setup ready! Hold Button1 for Servo1, Button2 for Servo2, Button3 for both.");
  Serial.println("Pot on A0 controls angle (0-180°).");
}

void loop() {
  // Read button states (LOW = pressed)
  bool btn1Pressed = (digitalRead(button1) == LOW);
  bool btn2Pressed = (digitalRead(button2) == LOW);
  bool btn3Pressed = (digitalRead(button3) == LOW);

  // Throttle updates for smoothness (like your 15ms delay)
  if (millis() - lastUpdateTime >= updateInterval) {
    
    // Always read the pot
    int potValue = analogRead(potPin);  // 0-1023
    int targetAngle = map(potValue, 0, 1023, 0, 180);  // Scale to 0-180°

    // Priority: Button3 (both) > Button1 > Button2 (if multiple pressed)
    if (btn3Pressed) {
      // Control both servos
      angle3 = targetAngle;
      servo3.write(angle3);
      Serial.print("Servo3: ");
      Serial.println(targetAngle);
    } else if (btn1Pressed) {
      // Control only servo1
      angle1 = targetAngle;
      servo1.write(angle1);
      Serial.print("Servo1: ");
      Serial.println(targetAngle);
    } else if (btn2Pressed) {
      // Control only servo2
      angle2 = targetAngle;
      servo2.write(angle2);
      Serial.print("Servo2: ");
      Serial.println(targetAngle);
    }
    // If no buttons pressed, servos hold current angles (no write needed)

    lastUpdateTime = millis();
  }

  // No additional delay needed—throttling handles it
}
