#include <Arduino.h>
#include "WIFI_YYROBOT.h"

/**************************************************************************
功能：post数据到OneNet服务器
输入参量：
	String API_VALUE：用户的API值
	unsigned long device_id：设备ID
	String sensor_id:传感器ID
	int thisData:要发送的数据值
返回：
	无
**************************************************************************/
void WIFI::postDataToOneNet(String API_VALUE,unsigned long device_id,String sensor_id,int thisData) {
	if(newMux(TCP,OneNetServer,80)) {
		DBGLN("connecting...");
		// send the HTTP PUT request:
		String cmd;
		cmd = "POST http://api.heclouds.com/devices/";
		cmd += String(device_id);
		cmd += "/datapoints HTTP/1.1\r\n";
		cmd += "Host: ";
		cmd += OneNetServer;
		cmd += "\r\n";
		cmd += "api-key: ";
		cmd += API_VALUE;
		cmd += "\r\n";
		cmd += "Connection: close";
		cmd += "\r\n";
		cmd += "Content-Length: ";
		
		int length = 53 + sensor_id.length() + getLength(thisData);
		
		cmd += String(length);
		cmd += "\r\n\r\n";
		
		cmd += "{\"datastreams\":[{\"id\":\"";
		cmd += sensor_id;
		cmd += "\",\"datapoints\":[{\"value\":";
		cmd += String(thisData);
		cmd += "}]}]}";
		
		cmd += "\r\n\r\n\r\n\r\n";
		
		// DBGLN(cmd);
		// DBG("length:");
		// DBGLN(cmd.length());

		send(cmd);

		bool found = false;
		String data = "";
		unsigned long start;
		DBGLN("ESP send data ok");
		start = millis();
		char a;
		esp.flush();	//清除缓冲区等待获取新内容
		while (millis()-start<30000) {
			if(esp.available()>0) {
				a = esp.read();
				data += a;
				DBG(a);
			}
			if (data.indexOf("CLOSED\r\n")!=-1) {
				found = true;
				break;
			}
			else if(data.indexOf("Gateway")!=-1) {
				found = false;
				DBGLN("RECEIVE Bad Gateway");
				break;
			}
		}


		if(found)
			DBGLN("RECEIVE \"CLOSED\"");
		else {
			DBGLN("NOT RECEIVE \"CLOSED\"!");
			software_Reset();
		}

	} else {
		DBGLN("---------------------");
		DBG("tcp connect false!");
		DBGLN("---------------------");
		errorNumber++;
		if(errorNumber == 5)
		{
			errorNumber = 0;
			software_Reset();
		}
		DBG("errorNumber:");
		DBGLN(errorNumber);
	}

}


/**************************************************************************
功能：通过get指令从Yeelink获取数据
输入参量：
	String API_VALUE：用户的API值
	unsigned long device_id：设备ID
	unsigned long sensor_id:传感器ID
返回：
	String：返回获取到的数据
**************************************************************************/
String WIFI::getDataFromYeelink(String API_VALUE,unsigned long device_id,unsigned long sensor_id) {
	// if there's a successful connection:
	if (newMux(TCP,YeelinkServer,80)) {
		DBGLN("connecting...");
		// send the HTTP PUT request:
		String cmd;
		cmd = "GET /v1.0/device/";
		cmd += String(device_id);
		cmd += "/sensor/";
		cmd += String(sensor_id);
		cmd += "/datapoints";
		cmd += " HTTP/1.1\r\n";
		cmd += "Host: api.yeelink.net\r\n";
		cmd += "Accept: *";
		cmd += "/";
		cmd += "*\r\n";
		cmd += "U-ApiKey:";
		cmd += API_VALUE;
		cmd += "\r\n";
		cmd += "Connection: close\r\n";
		cmd += "\r\n";

		DBGLN(cmd);
		DBG("length:");
		DBGLN(cmd.length());
		DBGLN("");
		
		if(send(cmd)) {
			bool found = false;
			String data = "";
			unsigned long start;
			
			start = millis();
			char a;
			esp.flush();	//清除缓冲区等待获取新内容
			while (millis()-start<30000) {	//30s没响应退出流程
	//		while(1) {
				if(esp.available()>0) {
					a = esp.read();
					data += a;
					DBG(a);
				}
				if (data.indexOf("}")!=-1&&data.indexOf("CLOSED\r\n")!=-1) {
					found = true;
					break;
				}
				if (data.indexOf("Gateway")!=-1&&data.indexOf("CLOSED\r\n")!=-1) {
					found = false;
					DBGLN("RECEIVE Bad Gateway");
					break;
				}
			}
			

			// DBGLN("**********************2");
			// if (esp.overflow())
			// DBGLN("SoftwareSerial overflow!");
			// DBGLN("***********************");
			// DBGLN("*******DEBUG DATA********");
			// DBGLN(data);
			// DBGLN("***********************");
			// DBGLN(data.length());
			// DBGLN("***********************");
			
			if(found)
			{
				DBGLN("RECEIVE \"}\"");
				int startIndex = data.indexOf("value");
				int endIndex = data.indexOf("}");
				String value = data.substring(startIndex+7, endIndex);
				
				DBG("VALUE=");
				DBGLN(value);
				
				if(value == "0")
					return "0";				
				else if(value == "1")
					return "1";
			}
			else {
				DBGLN("found = false");
				software_Reset();
				//closeMux();
				return "";
			}
			
			
		}
		else
		{
			DBGLN("send return fail");
			software_Reset();

		}
	} else {
		// if you couldn't make a connection:
		DBGLN("connection failed");
		DBGLN("disconnecting.");
		errorNumber++;
		if(errorNumber == 5)
		{
			errorNumber = 0;
			software_Reset();
		}
		DBG("errorNumber:");
		DBGLN(errorNumber);
		return "";
	}
}

/**************************************************************************
功能：wifi模块发送数据
输入参量：
	String cmd：发送的数据
返回：
	bool：是否接收到send ok返回值
**************************************************************************/
bool WIFI::send(String cmd) {
	esp.print("AT+CIPSEND=");
	//    esp.print("\"");
	esp.println(cmd.length());

	//    esp.println("\"");
	unsigned long start;
	start = millis();
	bool found = false;
	String data = "";

	while (millis()-start<5000) {
		if(esp.available()>0) {
			char a =esp.read();
			if(a == '>') {
				DBGLN("receive >");
				found = true;
				break;
			}
		}
	}

	

	if(found) {
		found = false;
		DBGLN("ESP send data!");
		esp.flush();	//清除缓冲区等待获取新内容
		esp.print(cmd);
		start = millis();
		data = "";
		while (millis()-start<20000) {
			if(esp.available()>0) {
				char a =esp.read();
				data += a;
			}
			if(data.indexOf("SEND OK") != -1) {
				DBGLN("RECEIVE SEND OK");
				return true;
			}
			if(data.indexOf("SEND FAIL") != -1) {
				DBGLN("RECEIVE SEND FAIL");
				return false;
			}
		}
		if(found == false)
		{
			DBGLN("RECEIVE NULL");
			software_Reset();
			return false;
		}
	} else {
		return false;
	}	
}


/**************************************************************************
功能：wifi模块初始化
输入参量：
	String ssid：要连接的路由器无线名称
	String pass：无线密码
返回：
	无
**************************************************************************/
void WIFI::begin(String ssid,String pass) {
#ifdef DEBUG
	dbg.begin(9600);	//设置debug串口的波特率
#endif
	DBGLN("DEBUG: Running Setup");

	esp.begin(115200);	//设置和ESP芯片通讯的串口波特率

	//连接路由器必备的流程
	sendATCommandUntil("AT+RST\r\n","ready", 5000);
	sendATCommandUntil("AT\r\n", "OK\r\n", 5000);
	sendATCommandUntil("AT+CWMODE=1\r\n","OK\r\n", 5000);
	sendATCommandUntil("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n","OK\r\n", 30000);
	sendATCommandUntil("AT+CIPMUX=0\r\n","OK\r\n", 5000);
//	sendATCommandUntil("AT+CIFSR\r\n","OK\r\n", 30000);

	
	DBGLN("DEBUG: Setup complete\n\n");
	
	errorNumber = 0;
}





/**************************************************************************
功能：post数据到Yeelink服务器
输入参量：
	String API_VALUE：用户的API值
	unsigned long device_id：设备ID
	unsigned long sensor_id:传感器ID
	int thisData:要发送的数据值
返回：
	无
**************************************************************************/
void WIFI::postDataToYeelink(String API_VALUE,unsigned long device_id,unsigned long sensor_id,int thisData) {
	if(newMux(TCP,YeelinkServer,80)) {
		DBGLN("connecting...");
		// send the HTTP PUT request:
		String cmd;
		cmd = "POST /v1.0/device/";
		cmd += String(device_id);
		cmd += "/sensor/";
		cmd += String(sensor_id);
		cmd += "/datapoints";
		cmd += " HTTP/1.1\r\n";
		cmd += "Host: api.yeelink.net\r\n";
		cmd += "Accept: *";
		cmd += "/";
		cmd += "*\r\n";
		cmd += "U-ApiKey:";
		cmd += API_VALUE;
		cmd += "\r\n";
		cmd += "Content-Length: ";
		int thisLength = 10 + getLength(thisData);
		cmd += String(thisLength);
		cmd += "\r\n";
		cmd += "Content-Type: application/x-www-form-urlencoded\r\n";
		cmd += "Connection: close\r\n";
		cmd += "\r\n";
		cmd += "{\"value\":";
		cmd += String(thisData);
		cmd += "}\r\n\r\n";


		// DBGLN(cmd);
		// DBG("length:");
		// DBGLN(cmd.length());

		send(cmd);

		bool found = false;
		String data = "";
		unsigned long start;
		DBGLN("ESP send data ok");
		start = millis();
		char a;
		esp.flush();	//清除接收缓冲区
		while (millis()-start<20000) {
			while(esp.available()>0) {
				a = esp.read();
				data += a;
				DBG(a);
			}		
			if (data.indexOf("Gateway")!=-1) {
				DBGLN("RECEIVE Bad Gateway");
				found = false;
				delay(1000);
				break;
			}
			else if (data.indexOf("Gateway")==-1 && data.indexOf("CLOSED\r\n")!=-1) {
				found = true;
				break;
			}
		}



		if(found)
			DBGLN("found = ture");
		else {
			DBGLN("found = false");
			software_Reset();
		}

	} else {
		DBGLN("---------------------");
		DBG("tcp connect false!");
		DBGLN("---------------------");
		
		errorNumber++;
		if(errorNumber == 5)
		{
			errorNumber = 0;
			software_Reset();
		}
		DBG("errorNumber:");
		DBGLN(errorNumber);
	}

}

/**************************************************************************
功能：关闭TCP/UDP
输入参量：
	无
返回：
	无
**************************************************************************/
void WIFI::closeMux(void) {
	esp.println("AT+CIPCLOSE");

	String data;
	unsigned long start;
	start = millis();
	while (millis()-start<3000) {
		if(esp.available()>0) {
			char a =esp.read();
			data=data+a;
		}
		if (data.indexOf("Linked")!=-1 || data.indexOf("ERROR")!=-1 || data.indexOf("we must restart")!=-1) {
			DBGLN("********closeMux*******");
			DBGLN(data);
			DBGLN("***********************");
			break;
		}
	}
	DBGLN("********closeMux*******");
	DBGLN(data);
	DBGLN("***********************");
}

/**************************************************************************
功能：获取数据长度
输入参量：
	int someValue：输入数据
返回：
	int ：返回数据长度
**************************************************************************/
int WIFI::getLength(int someValue) {
	// there's at least one byte:
	int digits = 1;
	// continually divide the value by ten,
	// adding one to the digit count for each
	// time you divide, until you're at 0:
	int dividend = someValue /10;
	while (dividend > 0) {
		dividend = dividend /10;
		digits++;
	}
	// return the number of digits:
	return digits;
}

/**************************************************************************
功能：连接TCP/UDP
输入参量：
	byte type：选择TCP还是UDP
	String addr:连接的地址
	int port：端口号
返回：
	boolean ：是否成功
**************************************************************************/
boolean WIFI::newMux(byte type, String addr, int port) {
	String data;
	esp.print("AT+CIPSTART=");
	if(type>0) {
		esp.print("\"TCP\"");
	} else {
		esp.print("\"UDP\"");
	}
	esp.print(",");
	esp.print("\"");
	esp.print(addr);
	esp.print("\"");
	esp.print(",");
//    esp.print("\"");
	esp.println(String(port));
//    esp.println("\"");
	unsigned long start;
	start = millis();
	while (millis()-start<5000) {
		if(esp.available()>0) {
			char a =esp.read();
			data=data+a;
		}
		if (data.indexOf("OK")!=-1 || data.indexOf("ALREAY CONNECT")!=-1) {
			return true;
		}
	}
	return false;
}


/**************************************************************************
功能：用于发送AT指令，返回接收到的返回信息
输入参量：
	String command：AT指令
	const int timeout：定义等待接收最长时间
返回：
	String：返回接收到的AT返回信息
**************************************************************************/
String WIFI::sendATCommand(String command, const int timeout) {
	String response = "";
	esp.print(command); // send the read character to the esp8266
	long int time = millis();
	while ( (time + timeout) > millis()) {
		while (esp.available()) {
			// The esp has data so display its output to the serial window
			char c = esp.read(); // read the next character.
			response += c;
		}

	}
	esp.flush();	//清除接收缓冲区


	DBG(response);


	return response;
}

/**************************************************************************
功能：用于发送AT指令，返回接收到的返回信息
输入参量：
	String command：AT指令
	String receiveKeyword：等待接收到的关键字
	const int timeout：定义多长时间没接收到关键字退出该函数
返回：
	String：返回接收到的AT返回信息
**************************************************************************/
String WIFI::sendATCommandUntil(String command,String receiveKeyword,const long timeout) {
	String response = "";
	esp.print(command); // send the read character to the esp8266

	DBGLN("----------------");
	DBG("send:");
	DBGLN(command);
	DBGLN("----------------");

	long int time = millis();
	bool found = false;
	while ( (time + timeout) > millis()) {
		while (esp.available()) {
			// The esp has data so display its output to the serial window
			char c = esp.read(); // read the next character.
			response += c;
		}
		esp.flush();	//清除接收缓冲区
		if(response.indexOf(receiveKeyword)!=-1) {
			DBGLN("--------------------------------");

			DBG("debug message receive Keyword:");
			DBGLN(receiveKeyword);
			DBGLN("--------------------------------");
			found = true;
			break;
		}
	}

	if(found == true)
	{
		DBGLN("-----------receive message------");
		DBG(response);
		DBGLN("--------------------------------");
	}
	else
	{
		DBGLN("-----------not receive Keyword------");
		software_Reset();
	}


	return response;
}


void WIFI::software_Reset() // 软启动系统，但不 复位寄存器和变量
{
        asm volatile ("  jmp setup");
}  

