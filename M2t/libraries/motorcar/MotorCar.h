/********************************************
	文件名：MotorCar.h
履带车控制类库
    
	created 2011
	by Nille 
	Email：chenille@126.com
 
This example code is in the public domain.
*********************************************/
#ifndef MotorCar_h 
#define MotorCar_h

class MotorCar
{
 private:			//定义为私有
		int	_speedLeftPin;	//定义控制左轮速度的引脚
		int	_speedRightPin;	//定义控制右轮速度的引脚
		int	_dirLeftPin;	//定义控制左轮方向的引脚
		int	_dirRightPin;	//定义控制右轮方向的引脚

	public:				//定义为公有
    	MotorCar (int _slpin,int _dlpin,int _srpin,int _drpin);	//构造函数
	void forward(int _speed);				//前进函数
		void back(int _speed);				//后退函数
		void turnLeft(int _speed);				//左转函数
		void turnRight(int _speed);				//右转函数
		void turnLeftOrigin(int _speed);				//原地左转函数
		void turnRightOrigin(int _speed);			//原地右转函数
		void stop();					//停止函数
};

#endif

