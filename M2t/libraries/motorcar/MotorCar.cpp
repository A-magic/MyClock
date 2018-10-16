/********************************************
	文件名：MotorCar.cpp
	直流电机驱动库
    
	created 2011
  	by Nille 
  	Email：chenille@126.com
 
  This example code is in the public domain.
 *********************************************/

#include <WProgram.h> 
#include <MotorCar.h>
#include "string.h"
#include <stdio.h>
//#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

/**********************************************
MotorCar类构造函数
函数功能：定义用于控制直流电机的引脚
入口参数：	_slpin，表示控制左轮速度的引脚
		_dlpin，表示控制左轮方向的引脚
		_srpin，表示控制右轮速度的引脚
		_drpin，表示控制右轮方向的引脚
**********************************************/
MotorCar::MotorCar (int _slpin,int _dlpin,int _srpin,int _drpin)
{
	_speedLeftPin = _slpin;
	_speedRightPin = _srpin;
	_dirLeftPin = _dlpin;
	_dirRightPin = _drpin;
	pinMode(_speedLeftPin, OUTPUT);
	pinMode(_speedRightPin,OUTPUT);
	pinMode(_dirLeftPin,OUTPUT);
	pinMode(_dirRightPin,OUTPUT);

}

/**********************************************
forward子函数——前进子函数
函数功能：控制履带车前进
入口参数：_speed——前进速度，范围0至255
**********************************************/
void MotorCar::forward(int _speed)
{
		//引脚_dirRightPin输出高电平,右轮前进
  	digitalWrite(_dirRightPin, HIGH);
		
		//引脚_dirLeftPin输出高电平，左轮前进
  	digitalWrite(_dirLeftPin, HIGH);

		//引脚_speedRightPin输出PWM，PWM值由_speed决定
		analogWrite(_speedRightPin,_speed);

		//引脚_speedLeftPin输出PWM，PWM值由_speed决定
		analogWrite(_speedLeftPin,_speed);
}


/**********************************************
back子函数——后退子函数
函数功能：控制履带车后退
入口参数：_speed——后退速度，范围0至255
**********************************************/
void MotorCar::back(int _speed)
{
		//引脚_dirRightPin输出高电平,右轮后退
  	digitalWrite(_dirRightPin, LOW);
		
		//引脚_dirLeftPin输出高电平，左轮后退
  	digitalWrite(_dirLeftPin, LOW);

		//引脚_speedRightPin输出PWM，PWM值由_speed决定
		analogWrite(_speedRightPin,_speed);

		//引脚_speedLeftPin输出PWM，PWM值由_speed决定
		analogWrite(_speedLeftPin,_speed);
}


/**********************************************
turnLeft子函数——左转子函数
函数功能：控制履带车左转
入口参数：_speed——速度，范围0至255
**********************************************/
void MotorCar::turnLeft (int _speed)
{
		//引脚_dirRightPin输出高电平,右轮前进
  	digitalWrite(_dirRightPin, HIGH);
		
		//引脚_speedRightPin输出PWM，PWM值由_speed决定
		analogWrite(_speedRightPin,_speed);

		//引脚_speedLeftPin输出PWM，PWM值为0，表示左轮静止不转
		analogWrite(_speedLeftPin,0);
}

/**********************************************
turnRight子函数——右转子函数
函数功能：控制履带车右转
入口参数：_speed——速度，范围0至255
**********************************************/
void MotorCar::turnRight (int _speed)
{
		//引脚_dirLeftPin输出高电平,左轮前进
  	digitalWrite(_dirLeftPin, HIGH);
		
		//引脚_speedRightPin输出PWM，PWM值为0，表示右轮静止不转
		analogWrite(_speedRightPin,0);

		//引脚_speedLeftPin输出PWM，PWM值由_speed决定
		analogWrite(_speedLeftPin, _speed);
}

/**********************************************
turnLeftOrigin子函数——原地左转子函数
函数功能：控制履带车原地左转
入口参数：_speed——速度，范围0至255
**********************************************/
void MotorCar::turnLeftOrigin (int _speed)
{
		//引脚_dirRightPin输出高电平,右轮前进
  	digitalWrite(_dirRightPin, HIGH);

		//引脚_dirLeftPin输出高电平,左轮后退
  	digitalWrite(_dirLeftPin, LOW);
		
		//引脚_speedRightPin输出PWM，PWM值由_speed决定
		analogWrite(_speedRightPin,_speed);

		//引脚_speedLeftPin输出PWM，PWM值由_speed决定
		analogWrite(_speedLeftPin, _speed);
}


/**********************************************
turnRightOrigin子函数——原地右转子函数
函数功能：控制履带车原地右转
入口参数：_speed——速度，范围0至255
**********************************************/
void MotorCar::turnRightOrigin (int _speed)
{
		//引脚_dirLeftPin输出高电平,左轮前进
  	digitalWrite(_dirLeftPin, HIGH);

		//引脚_dirRightPin输出低电平,右轮后退
  	digitalWrite(_dirRightPin, LOW);
		
		//引脚_speedRightPin输出PWM，PWM值由_speed决定
		analogWrite(_speedRightPin, _speed);

		//引脚_speedLeftPin输出PWM，PWM值由_speed决定
		analogWrite(_speedLeftPin, _speed);
}

/**********************************************
stop子函数——停止子函数
函数功能：控制履带车停止
入口参数：无
**********************************************/
void MotorCar::stop()
{
		//引脚_speedRightPin输出低
		analogWrite(_speedRightPin, 0);

		//引脚_speedLeftPin输出低
		analogWrite(_speedLeftPin,0);
}
