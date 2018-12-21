//
// Created by Tyhhy on 10/29/2017.
//

#include "Joystick.h"

Joystick::Joystick(uint8_t xPin, uint8_t yPin, uint8_t bPin)
{
    this->_xPin = xPin;
    this->_yPin = yPin;
    this->_buttonPin = bPin;
    
    pinMode(_buttonPin, INPUT_PULLUP);
}

void Joystick::set_x()
{
    this->_xVal = analogRead(this->_xPin);
}

void Joystick::set_y()
{
    this->_yVal = analogRead(this->_yPin);
}

void Joystick::set_button()
{
    this->_buttonVal = digitalRead(this->_buttonPin);
}

void Joystick::read()
{
    this->set_x();
    this->set_y();
    this->set_button();
}

int Joystick::get_x()
{
    return this->_xVal;
}

int Joystick::get_y()
{
    return this->_yVal;
}

int Joystick::get_button()
{
    return this->_buttonVal;
}

void Joystick::print()
{
    Serial.print("x: ");
    Serial.print(this->get_x());
    Serial.print("\ty: ");
    Serial.print(this->get_y());
    Serial.print("\tbutton: ");
    Serial.print(this->get_button());
}

void Joystick::println()
{
    this->print();
    Serial.println();
}