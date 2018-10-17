/** @file    S4ALib.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    23.Mar.2018  
 *  @version 1.0 
 *  
 *  @brief   Libray for convenient use of S4A EDU Robotic Controller.
 *
 *  @licence  MIT License
 */
#include <Arduino.h>
#include <SoftwareSerial.h>

#ifndef __SA4LIB_H__
#define __SA4LIB_H__
class S4ALib {
  
  // ---- CONSTANTS
  #define RIGHTDIR    11  //  Right motor: - Direction
  #define RIGHTSPEED  6   //               - Speed
  #define LEFTDIR     10  //  Left motor : - Direction
  #define LEFTSPEED   5   //               - Speed

  // ---- VARIABLES

  public:
    // ---- PROPERTIES
    
    // ---- CONSTRUCTORS
    S4ALib();           // Constructor w/default values

    // ---- PUBLIC METHODS
    void begin();
    void forward();
    void forward(int ms);
    void backward();
    void backward(int ms);
    void left();
    void left(int ms);
    void right();
    void right(int ms);
    void stop();
    void ledOn();
    void ledOff();
    void blink(int ms);
    void setMotors(bool leftVal, bool rightVal);
    void setSpeed(int leftVal, int rightVal);
    
  private:
    // ---- PRIVATE VARIABLES
    int leftSpeed  = 0;          // Value between 0 and 255
    int rightSpeed = 0;          // Value between 0 and 255
};
#endif
