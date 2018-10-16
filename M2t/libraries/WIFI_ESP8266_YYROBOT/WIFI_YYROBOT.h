#ifndef __WIFI_YYROBOT_H__
#define __WIFI_YYROBOT_H__

#include <Arduino.h>

/*
//未测试UNO，可能会部分函数不好使，因为UNO的RAM太小，程序可能运行中数据溢出，尤其是在接受IP数据包时候
//建议大家使用MEGA2560使用该库函数
#include <SoftwareSerial.h>
SoftwareSerial esp(10, 11); // RX,TX
#define dbg Serial  // USB local debug
*/


//MEGA2560
#define esp Serial3 // 接ESP8266
#define dbg Serial  // debug调试程序流程

#define    TCP     1
#define    tcp     1
#define    UDP     0
#define    udp     0

//该条语句用于使能DEBUG输出信息，屏蔽掉就不会输出debug调试信息
#define DEBUG

#ifdef DEBUG
#define DBG(message)    dbg.print(message)
#define DBGLN(message)    dbg.println(message)
#else
#define DBG(message)
#define DBGLN(message)
#endif

#define YeelinkServer  "api.yeelink.net"   // name address for yeelink 	//YEELINK的TCP地址，无需修改
#define OneNetServer  "api.heclouds.com"   // name address for OneNet	//OneNet的TCP地址，无需修改



class WIFI {
public:
	void begin(String ssid,String pass);
	void postDataToYeelink(String API_VALUE,unsigned long device_id,unsigned long sensor_id,int thisData);
	String getDataFromYeelink(String API_VALUE,unsigned long device_id,unsigned long sensor_id);
	void postDataToOneNet(String API_VALUE,unsigned long device_id,String sensor_id,int thisData);
	void software_Reset();
	
private:
	bool send(String cmd);
	void closeMux(void);
	int getLength(int someValue);
	boolean newMux(byte type, String addr, int port);
	String sendATCommand(String command, const int timeout);
	String sendATCommandUntil(String command,String receiveKeyword,const long timeout);
	int errorNumber;
};

#endif
