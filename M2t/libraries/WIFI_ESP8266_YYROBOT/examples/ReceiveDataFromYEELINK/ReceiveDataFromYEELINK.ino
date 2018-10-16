#include "WIFI_YYROBOT.h"
#include "DHT11_YYROBOT.h"


DHT11 myDHT11(8);		//DHT11接在D8引脚
int relay = 4;		//继电器接在D4引脚
//模块上的继电器采用PNP三极管，所以低电平吸合导通
#define RELAY_ON LOW
#define RELAY_OFF HIGH
bool relayBuffer;

String ssid = "PUSHPULL";		//需要连接的自己路由器的无线名称
String pass = "888666888";		//无线密码

// for yeelink api
#define APIKEY         "e2485c9c18a40c5bc261a5a5e029b177" // 替换自己的yeelink的api
//自己的APIKEY，在yeelink的设置界面得到


//replace the device ID and sensor ID for temperature sensor.
#define DEVICEID0       22085 // replace your device ID		//替换为自己的设备ID

#define SENSORID0       38905 // replace your sensor ID		//替换为自己的传感器ID
#define SENSORID1       38906 // replace your sensor ID		//替换为自己的传感器ID
#define SENSOR_SWITCH	39009	//按键ID

unsigned long startPost,startGet;
bool flagFirstPost = true;	//第一次发送数据
bool flagFirstGet = true;	//第一次获取数据
WIFI wifi;



void setup() {
	pinMode(relay,OUTPUT);	//设置继电器控制IO为输出引脚
	digitalWrite(relay,relayBuffer);	//初始化关闭继电器

	wifi.begin(ssid,pass);//设置wifi连接
}


void loop() {
	//将数据上传到Yeelink对应的设备和传感器
	//发送一次数据时间Yeelink不能低于10s，所以10s发送一次就行了		
	if (millis()-startPost>10000 || flagFirstPost) {
		//读取温湿度传感器值，经过这个函数后，myDHT11.TEM_Buffer_Int和myDHT11.HUMI_Buffer_Int被分别填充上了温度和湿度值
		myDHT11.DHT11_Read();
		wifi.postDataToYeelink(APIKEY,DEVICEID0,SENSORID0,myDHT11.TEM_Buffer_Int);
		wifi.postDataToYeelink(APIKEY,DEVICEID0,SENSORID1,myDHT11.HUMI_Buffer_Int);
		startPost = millis();
		flagFirstPost = false;
	}
	
	//采集按键信息的时间也不能过快，建议1s以上
	if (millis()-startGet>1000 || flagFirstGet) {
		String str = wifi.getDataFromYeelink(APIKEY,DEVICEID0,SENSOR_SWITCH);
		if(str == "1") {
			relayBuffer = RELAY_ON;
			digitalWrite(relay,relayBuffer);
		} else if(str == "0") {
			relayBuffer = RELAY_OFF;
			digitalWrite(relay,relayBuffer);
		} else {
			//NULL
		}
		
		startGet = millis();
		flagFirstGet = false;
	}
}