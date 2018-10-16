
#include <Servo.h>

int control_mode = 1; //控制模式，1-自动巡逻，2-ps2手柄，3-语音控制

#include <PS2X_lib.h>  //for v1.6

/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   true
//#define rumble      true
#define rumble      true

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;


Servo myservo2;  // 声明舵机手臂
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;

Servo myservo8;  // 声明舵机头部
Servo myservo9;

Servo myservo;  // 前部超声波舵机变量


int Sensor_L = A0; //前左红外避障器
int Sensor_R = A5; //前右红外避障器

int inL0 = 4;//定义了板上的4个控制端，左轮10、11一组，右轮12、13一组
int inL1 = 5;
int inLpwm = 6;
int inR0 = 8;
int inR1 = 9;
int inRpwm = 10;
int L_run,  R_run;    //小车电机驱动运行值pwm

int value_L, value_R;//++++++++小车运行变量定义

//定义3超声波测距的引脚
const int echopinM = 40;
const int trigpinM = 41; // 前方超声波测距器

const int echopinL = 44; // echo接50端口
const int trigpinL = 45; // trig接51端口  左侧超声波测距器

const int echopinR = 42;
const int trigpinR = 43; // 右侧超声波测距器





