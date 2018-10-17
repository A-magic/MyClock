/** @file    SimpleTest.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    23.Mar.2018  
 *  @version 1.0 
 *  
 *  @brief   Simple example for S4ALib usage.
 *
 *  @licence  MIT License
 */
#include <S4ALib.h>

S4ALib Robot;

void setup() {
  Robot.begin();
}  // setup

void loop() {
  Robot.ledOn();

  Robot.setSpeed(150, 150);
  Robot.forward(500);

  Robot.setSpeed(150, 150);
  Robot.backward(500);
  
  Robot.setSpeed(150, 150);
  Robot.left(500);

  Robot.setSpeed(150, 150);
  Robot.right(500);

  Robot.ledOff();

  for (int i = 0 ; i < 5 ; i++)
    Robot.blink(200);
}  // loop
