//re
// Created by Alex Foreman on 10/29/2017.
//

#ifndef JOYSTICK_JOYSTICK_H
#define JOYSTICK_JOYSTICK_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Joystick {
private:
    uint8_t _xPin;
    uint8_t _yPin;
    uint8_t _buttonPin;

    int _xVal;
    int _yVal;
    int _buttonVal;

    void set_x();
    void set_y();
    void set_button();

public:
    Joystick(uint8_t x, uint8_t y, uint8_t button);
    void read();
    int get_x();
    int get_y();
    int get_button();
    void print();
    void println();
};

#endif //JOYSTICK_JOYSTICK_H
