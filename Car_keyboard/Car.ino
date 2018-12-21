const int rWheelsForward = 11;                           // digital pin that is responsible for moving both right wheels forward
const int rWheelsBackward = 10;                          // digital pin that is responsible for moving both right wheels backward
const int lWheelsForward = 5;                           // digital pin that is responsible for moving both left wheels forward
const int lWheelsBackward = 6;                          // digital pin that is responsible for moving both left wheels backward

const int lSpeedPin = 0;                                // pin for setting the speed of the left side wheels
const int rSpeedPin = 0;                                // pin for setting the speed of the right side wheels

const unsigned int MAX_SPEED = 255;
void setup() {

  Serial.begin(9600);                                   // set up serial link


  //  // set all the motor control pins to outputs
  pinMode(lWheelsForward, OUTPUT);
  pinMode(lWheelsBackward, OUTPUT);
  pinMode(rWheelsForward, OUTPUT);
  pinMode(rWheelsBackward, OUTPUT);
}

void loop() {

  if (Serial.available()) {
    char ch = Serial.read();
    switch (ch) {
      case 'w': {
          moveForward(MAX_SPEED);
          break;
        }

      case 'a': {
          turnLeft(MAX_SPEED);
          break;
        }
      case 'd': {
          turnRight(MAX_SPEED);
          break;
        }
      case 's': {
          moveBackward(MAX_SPEED);
          break;
        }

      case 'e': {
          stopCar();
          break;
        }
    }
  }

}


// it activates the pins that are responsible for forward move
// and deactivates the pins that are responsible for backward move
void moveForward(const int &cSpeed) {

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);

  analogWrite(lWheelsForward, cSpeed);
  analogWrite(rWheelsForward, cSpeed);
}

// deactivates the pins that are responsible for forward move
// and activates the pins that are responsible for backward move
void moveBackward(const int &cSpeed) {
  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);

  analogWrite(lWheelsBackward, cSpeed);
  analogWrite(rWheelsBackward, cSpeed);
}

void turnLeft(int cSpeed) {

  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, cSpeed);

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);
}

void turnRight(int cSpeed) {
  analogWrite(lWheelsForward, cSpeed);
  analogWrite(rWheelsForward, 0);

  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);
}

void stopCar() {
  analogWrite(lWheelsForward, 0);
  analogWrite(rWheelsForward, 0);
  analogWrite(lWheelsBackward, 0);
  analogWrite(rWheelsBackward, 0);
}

