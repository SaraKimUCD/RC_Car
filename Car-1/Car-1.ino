#include <SoftwareSerial.h>

const int txPin = 7;  // Nano will Transmit on Pin D9, HC-05 will receive from resistor network
const int rxPin = 8; // Nano will Receive on Pin D10, HC-05 will transmit
const int lWheelsForward = 10;                           // digital pin that is responsible for moving both right wheels forward
const int lWheelsBackward = 11;                          // digital pin that is responsible for moving both right wheels backward
const int rWheelsForward = 9;                           // digital pin that is responsible for moving both left wheels forward
const int rWheelsBackward = 5;                          // digital pin that is responsible for moving both left wheels backward

const int lSpeedPin = 0;                                // pin for setting the speed of the left side wheels
const int rSpeedPin = 0;                                // pin for setting the speed of the right side wheels

SoftwareSerial BTSerial(rxPin, txPin); // RX, TX
int x = 0;
int y = 0;
char power[2];

// -----------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);                          // Default communication rate of the Bluetooth module
  // set all the motor control pins to outputs
  pinMode(lWheelsForward, OUTPUT);
  pinMode(lWheelsBackward, OUTPUT);
  pinMode(rWheelsForward, OUTPUT);
  pinMode(rWheelsBackward, OUTPUT);
}
// -----------------------------------------------------------------------------------------------
void loop() {

  delay(60);
  readBluetooth();

  start();






  Serial.print(x);
  Serial.print(' ');
  Serial.println(y);
}
// ------------------------
void readBluetooth()
{
  if (BTSerial.available() > 0)
  {
    char temp = BTSerial.read();
    if (temp == '9') {
      for (int i = 0; i < 2; i++) {
        power[i] = char(BTSerial.read());
      }
      x = power[0] - 52;
      y = power[1] - 52;
      if ( x > 4 || x < -4) {
        x = 0;
      }
      if ( y > 4 || y < -4) {
        y = 0;
      }
      // Change this?
      //            x = map(x,-4,4,-127,127);
      //            y = -map(y,-4,4,-127,127);
      x = map(x, -4, 4, -255, 255);
      y = -map(y, -4, 4, -255, 255);

    }
  }
}

// it activates the pins that are responsible for forward move
// and deactivates the pins that are responsible for backward move
void moveForward(int cSpeed) {

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);

  analogWrite(lWheelsForward, cSpeed);
  analogWrite(rWheelsForward, cSpeed);
}

// deactivates the pins that are responsible for forward move
// and activates the pins that are responsible for backward move
void moveBackward(int cSpeed) {

  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);

  analogWrite(lWheelsBackward, cSpeed);
  analogWrite(rWheelsBackward, cSpeed);
}

void turnLeft(int cSpeed) {

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);

  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, cSpeed);

}

void leftReverse(int cSpeed) {

  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, cSpeed);

}

void rightReverse(int cSpeed) {

  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);

  analogWrite(lWheelsBackward, cSpeed);
  analogWrite(rWheelsBackward, 0);

}

void turnRight(int cSpeed) {

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);

  analogWrite(lWheelsForward, cSpeed);
  analogWrite(rWheelsForward, 0);
}

void stopCar() {
  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);
  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);
}

void start() {
  if (x < 0 && y < 0)
    leftReverse(y + 510);

  else if (x > 0 && y < 0)
    rightReverse(x);

  else if (x < 0 && y > 0)
    turnLeft(y);

  else  if (x > 0 && y > 0 )
    turnRight(x);

  else  if (y < 0 && x == 0)
    moveBackward(y + 510);

  else  if (y > 0 && x == 0)
    moveForward(y);

  else if (x > 0 && y == 0)
    turnRight(x);

  else if (x < 0 && y == 0)
    turnLeft(x + 510);

  else {

    stopCar();

  }

}

