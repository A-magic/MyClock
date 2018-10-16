#include "WIFI_YYROBOT.h"
#include "DHT11_YYROBOT.h"


DHT11 myDHT11(8);		//DHT11接在D8引脚

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

WIFI wifi;

void setup() {

	wifi.begin(ssid,pass);		//设置wifi连接

}


void loop() {
	//读取温湿度传感器值，经过这个函数后，myDHT11.TEM_Buffer_Int和myDHT11.HUMI_Buffer_Int被分别填充上了温度和湿度值
	myDHT11.DHT11_Read();

	//将数据上传到Yeelink对应的设备和传感器
	wifi.postDataToYeelink(APIKEY,DEVICEID0,SENSORID0,myDHT11.TEM_Buffer_Int);
	delay(1000);
	wifi.postDataToYeelink(APIKEY,DEVICEID0,SENSORID1,myDHT11.HUMI_Buffer_Int);
	delay(1000);

}