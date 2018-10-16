/********************************************
	�ļ�����MotorCar.h
�Ĵ����������
    
	created 2011
	by Nille 
	Email��chenille@126.com
 
This example code is in the public domain.
*********************************************/
#ifndef MotorCar_h 
#define MotorCar_h

class MotorCar
{
 private:			//����Ϊ˽��
		int	_speedLeftPin;	//������������ٶȵ�����
		int	_speedRightPin;	//������������ٶȵ�����
		int	_dirLeftPin;	//����������ַ��������
		int	_dirRightPin;	//����������ַ��������

	public:				//����Ϊ����
    	MotorCar (int _slpin,int _dlpin,int _srpin,int _drpin);	//���캯��
	void forward(int _speed);				//ǰ������
		void back(int _speed);				//���˺���
		void turnLeft(int _speed);				//��ת����
		void turnRight(int _speed);				//��ת����
		void turnLeftOrigin(int _speed);				//ԭ����ת����
		void turnRightOrigin(int _speed);			//ԭ����ת����
		void stop();					//ֹͣ����
};

#endif

