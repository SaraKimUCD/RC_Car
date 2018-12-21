#include <SoftwareSerial.h>
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 3
#include "Joystick.h"

// Nano will Transmit on Pin D9, HC-05 will receive from resistor network
const int txPin = 9;  
// Nano will Receive on Pin D10, HC-05 will transmit
const int rxPin = 10; 
SoftwareSerial BTSerial(rxPin, txPin); // RX, TX
Joystick myJoystick = Joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_BUTTON);

// -----------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  // Default communication rate of the Bluetooth module
  BTSerial.begin(38400);                          
}
// -----------------------------------------------------------------------------------------------
void loop() {
  delay(50);
  readJoystick();
  
  int xZone = map(myJoystick.get_x(),0,1023,0,9);
  int yZone = map(myJoystick.get_y(),0,1023,0,9);
  int power = (xZone*10)+(yZone);

  int xtemp = (power - yZone) / 10;
  int ytemp = power - xZone;

  char xchar = xZone + 48;
  char ychar = yZone + 48;

  char arr[3];
  
  arr[0]='9';
  arr[1]=xchar;
  arr[2]=ychar;

  for(int i = 0; i < 3; i++){
    BTSerial.write(arr[i]);
  }
}

void readJoystick() {
  myJoystick.read();
}
