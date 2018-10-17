/** @file    BluetoothTest.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    23.Mar.2018  
 *  @version 1.0 
 *  
 *  @brief   Simple example for S4ALib usage with Bluetooth
 *           controller (HC-06).
 *
 *  @licence  MIT License
 */
#include <S4ALib.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(1,0);
char   lectura;
String hilera = "";
int    i, v;

S4ALib Robot;
void setup() {
  Robot.begin();
  bt.begin(9600);
  v = 0;
}  // setup

void loop() {
  if (bt.available()) {
    while (bt.available()) {
      lectura = (char)bt.read();
      hilera += lectura;
    }
    if (hilera == "l") {
      Robot.left();
    } else if (hilera == "r") {
      Robot.right();
    } else if (hilera == "u") {
      Robot.forward();
    } else if (hilera == "d") {
      Robot.backward();
    } else if (hilera == "s") {
      Robot.stop();
    } else if (isDigit(hilera[0])) {
      i = hilera.toInt();
      if (i == 0) i = 10;
      v = map(i, 1, 10, 0, 255);
      Robot.setSpeed(v, v);
    }
    hilera = "";
  }
}  // loop
