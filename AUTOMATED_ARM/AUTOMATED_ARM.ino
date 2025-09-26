#include <Servo.h>

Servo servo[4];

int interval = 1000;
unsigned long lastupdtime = 0;

void servopos(int servo_num, int angle, int servo_delay){
  servo[servo_num].write(angle);
  delay(servo_delay);

}

void setup() {
  //servo pins
  servo[1].attach(8);
  servo[2].attach(9);
  servo[3].attach(10);
  //starting pos servo
  servo[1].write(0);
  servo[2].write(0);
  servo[3].write(0);
  //int serial monitor
  Serial.begin(9600);

}


void loop() {
    servopos(2, 90, 1000);
    servopos(1, 180, 1000);
    servopos(3, 0, 1000);
    servopos(3, 40, 2000);
    servopos(3, 0, 1000);
    servopos(1, 0, 1000);
    servopos(2, 30, 2000);
}
