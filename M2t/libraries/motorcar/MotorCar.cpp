/********************************************
	�ļ�����MotorCar.cpp
	ֱ�����������
    
	created 2011
  	by Nille 
  	Email��chenille@126.com
 
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
MotorCar�๹�캯��
�������ܣ��������ڿ���ֱ�����������
��ڲ�����	_slpin����ʾ���������ٶȵ�����
		_dlpin����ʾ�������ַ��������
		_srpin����ʾ���������ٶȵ�����
		_drpin����ʾ�������ַ��������
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
forward�Ӻ�������ǰ���Ӻ���
�������ܣ������Ĵ���ǰ��
��ڲ�����_speed����ǰ���ٶȣ���Χ0��255
**********************************************/
void MotorCar::forward(int _speed)
{
		//����_dirRightPin����ߵ�ƽ,����ǰ��
  	digitalWrite(_dirRightPin, HIGH);
		
		//����_dirLeftPin����ߵ�ƽ������ǰ��
  	digitalWrite(_dirLeftPin, HIGH);

		//����_speedRightPin���PWM��PWMֵ��_speed����
		analogWrite(_speedRightPin,_speed);

		//����_speedLeftPin���PWM��PWMֵ��_speed����
		analogWrite(_speedLeftPin,_speed);
}


/**********************************************
back�Ӻ������������Ӻ���
�������ܣ������Ĵ�������
��ڲ�����_speed���������ٶȣ���Χ0��255
**********************************************/
void MotorCar::back(int _speed)
{
		//����_dirRightPin����ߵ�ƽ,���ֺ���
  	digitalWrite(_dirRightPin, LOW);
		
		//����_dirLeftPin����ߵ�ƽ�����ֺ���
  	digitalWrite(_dirLeftPin, LOW);

		//����_speedRightPin���PWM��PWMֵ��_speed����
		analogWrite(_speedRightPin,_speed);

		//����_speedLeftPin���PWM��PWMֵ��_speed����
		analogWrite(_speedLeftPin,_speed);
}


/**********************************************
turnLeft�Ӻ���������ת�Ӻ���
�������ܣ������Ĵ�����ת
��ڲ�����_speed�����ٶȣ���Χ0��255
**********************************************/
void MotorCar::turnLeft (int _speed)
{
		//����_dirRightPin����ߵ�ƽ,����ǰ��
  	digitalWrite(_dirRightPin, HIGH);
		
		//����_speedRightPin���PWM��PWMֵ��_speed����
		analogWrite(_speedRightPin,_speed);

		//����_speedLeftPin���PWM��PWMֵΪ0����ʾ���־�ֹ��ת
		analogWrite(_speedLeftPin,0);
}

/**********************************************
turnRight�Ӻ���������ת�Ӻ���
�������ܣ������Ĵ�����ת
��ڲ�����_speed�����ٶȣ���Χ0��255
**********************************************/
void MotorCar::turnRight (int _speed)
{
		//����_dirLeftPin����ߵ�ƽ,����ǰ��
  	digitalWrite(_dirLeftPin, HIGH);
		
		//����_speedRightPin���PWM��PWMֵΪ0����ʾ���־�ֹ��ת
		analogWrite(_speedRightPin,0);

		//����_speedLeftPin���PWM��PWMֵ��_speed����
		analogWrite(_speedLeftPin, _speed);
}

/**********************************************
turnLeftOrigin�Ӻ�������ԭ����ת�Ӻ���
�������ܣ������Ĵ���ԭ����ת
��ڲ�����_speed�����ٶȣ���Χ0��255
**********************************************/
void MotorCar::turnLeftOrigin (int _speed)
{
		//����_dirRightPin����ߵ�ƽ,����ǰ��
  	digitalWrite(_dirRightPin, HIGH);

		//����_dirLeftPin����ߵ�ƽ,���ֺ���
  	digitalWrite(_dirLeftPin, LOW);
		
		//����_speedRightPin���PWM��PWMֵ��_speed����
		analogWrite(_speedRightPin,_speed);

		//����_speedLeftPin���PWM��PWMֵ��_speed����
		analogWrite(_speedLeftPin, _speed);
}


/**********************************************
turnRightOrigin�Ӻ�������ԭ����ת�Ӻ���
�������ܣ������Ĵ���ԭ����ת
��ڲ�����_speed�����ٶȣ���Χ0��255
**********************************************/
void MotorCar::turnRightOrigin (int _speed)
{
		//����_dirLeftPin����ߵ�ƽ,����ǰ��
  	digitalWrite(_dirLeftPin, HIGH);

		//����_dirRightPin����͵�ƽ,���ֺ���
  	digitalWrite(_dirRightPin, LOW);
		
		//����_speedRightPin���PWM��PWMֵ��_speed����
		analogWrite(_speedRightPin, _speed);

		//����_speedLeftPin���PWM��PWMֵ��_speed����
		analogWrite(_speedLeftPin, _speed);
}

/**********************************************
stop�Ӻ�������ֹͣ�Ӻ���
�������ܣ������Ĵ���ֹͣ
��ڲ�������
**********************************************/
void MotorCar::stop()
{
		//����_speedRightPin�����
		analogWrite(_speedRightPin, 0);

		//����_speedLeftPin�����
		analogWrite(_speedLeftPin,0);
}
