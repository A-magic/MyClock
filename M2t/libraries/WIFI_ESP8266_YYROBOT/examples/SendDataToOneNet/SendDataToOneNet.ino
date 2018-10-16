#include "WIFI_YYROBOT.h"
#include "DHT11_YYROBOT.h"


DHT11 myDHT11(8);		//DHT11接在D8引脚

String ssid = "PUSHPULL";		//需要连接的自己路由器的无线名称
String pass = "888666888";		//无线密码

#define OneNetAPIKEY "pmWLtnkDBSreKfvg7GsClUXdXa4A"
#define OneNetDeviceID 79146
#define OneNetSensorID0 "TEMP"
#define OneNetSensorID1 "HUMI"


WIFI wifi;

void setup() {

	wifi.begin(ssid,pass);		//设置wifi连接

}


void loop() {
	//读取温湿度传感器值，经过这个函数后，myDHT11.TEM_Buffer_Int和myDHT11.HUMI_Buffer_Int被分别填充上了温度和湿度值
	myDHT11.DHT11_Read();

	//将数据上传到Yeelink对应的设备和传感器
	wifi.postDataToOneNet(OneNetAPIKEY,OneNetDeviceID,OneNetSensorID0,myDHT11.TEM_Buffer_Int);
	delay(1000);
	wifi.postDataToOneNet(OneNetAPIKEY,OneNetDeviceID,OneNetSensorID1,myDHT11.HUMI_Buffer_Int);
	delay(1000);

}