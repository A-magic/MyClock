/** @file    S4ALib.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    23.Mar.2018  
 *  @version 1.0 
 *  
 *  @brief   Libray for convenient use of S4A EDU Robotic Controller.
 *
 *  @licence  MIT License
 */
#include "S4ALib.h"

/** 
 *   @brief  Constructor
 */
S4ALib::S4ALib(){
}  // constructor

/** 
 *   @brief  Initialize the class
 *  
 *   @return void
 */ 
void S4ALib::begin(){
  // ---- Initialize the digital ports
  pinMode(RIGHTDIR  , OUTPUT);
  pinMode(RIGHTSPEED, OUTPUT);
  pinMode(LEFTDIR   , OUTPUT);
  pinMode(LEFTSPEED , OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  //  ---- Stops both motors
  stop();
}  // void begin

/** 
 *   @brief  Move forward both motors.   
 *  
 *   @return void
 */ 
void S4ALib::forward() {
  setMotors(LOW, LOW);
  setSpeed(leftSpeed, rightSpeed);
}  // void forward

/** 
 *   @brief  Move forward just for ms period
 *  
 *   @param  ms is the time in milliseconds to move forward  
 *   @return void
 */ 
void S4ALib::forward(
  int ms
){
  forward();
  delay(ms);
  stop();
}  // void forward

/** 
 *   @brief  Move backward both motors.   
 *  
 *   @return void
 */ 
void S4ALib::backward() {
  setMotors(HIGH, HIGH);
  setSpeed(leftSpeed, rightSpeed);
}  // void backward

/** 
 *   @brief  Move backward just for ms period
 *  
 *   @param  ms is the time in milliseconds to move backward
 *   @return void
 */ 
void S4ALib::backward(
  int ms
){
  backward();
  delay(ms);
  stop();
}  // void backward

/** 
 *   @brief  Move left.
 *  
 *   @return void
 */ 
void S4ALib::left(){
  setMotors(HIGH, LOW);
  setSpeed(leftSpeed, rightSpeed);
}  // void left

/**
 *   @brief  Move left just for ms period (milliseconds)
 *  
 *   @param  ms is the time in milliseconds to move to the left
 *   @return void
 */ 
void S4ALib::left (
  int ms
){
 left();
 delay(ms);
 stop();
}  // void left

void S4ALib::right () {
  setMotors(LOW, HIGH);
  setSpeed(leftSpeed, rightSpeed);
}  // void right

/**
 *   @brief  Move right just for ms period (milliseconds)
 *  
 *   @param  ms is the time in milliseconds to move to the right
 *   @return void
 */ 
void S4ALib::right(
  int ms
){
  right();
  delay(ms);
  stop();
}  // void right

/**
 *   @brief  Stops boths motors witout changing
 *           speed variables
 *  
 *   @return void
 */ 
void S4ALib::stop(){
  setMotors(LOW, LOW);
  analogWrite(LEFTSPEED , 0);
  analogWrite(RIGHTSPEED, 0);
}  // void stop

/**
 *   @brief  Turns on the built in led
 *  
 *   @return void
 */ 
void S4ALib::ledOn(){
  digitalWrite(LED_BUILTIN, HIGH);  
}  // void ledOn

/**
 *   @brief  Turns off the built in led
 *  
 *   @return void
 */ 
void S4ALib::ledOff(){
  digitalWrite(LED_BUILTIN, LOW);
}  // void ledOff

/**
 *   @brief  Blinks the built in led for ms milliseconds
 *  
 *   @return void
 */ 
void S4ALib::blink(
  int ms
) {
  ledOn();
  delay(ms);
  ledOff();
  delay(ms);  
}  // void blink

/**
 *   @brief  Sets turn direction for both motors
 *  
 *   @return void
 */ 
void S4ALib::setMotors(
  bool leftVal,
  bool rightVal
) {
  digitalWrite(LEFTDIR , leftVal);
  digitalWrite(RIGHTDIR, rightVal);  
}  // void setMotors

/**
 *   @brief  Sets speed for both motors
 *  
 *   @return void
 */ 
void S4ALib::setSpeed(
  int leftVal,
  int rightVal
) {
  // ---- Constrains speed values between 0 and 255
  leftSpeed  = constrain(leftVal, 0, 255);
  rightSpeed = constrain(rightVal, 0, 255);

  analogWrite(LEFTSPEED, leftSpeed);
  analogWrite(RIGHTSPEED, rightSpeed);
}  // void setSpeed

