
#define LIGHT_PIN 9//定义LCD12864背光引脚

//#define LED_PIN 14
const int LED_PIN = A0;
         String d = "";
#define RELAY_PIN 8

#define DHT11PIN 53//定义DHT11接口

// GY-30
// BH1750FVI 光照传感器
// in ADDR 'L' mode 7bit addr
#define ADDR 0b0100011

//烟感MQ5
const int sensorPin = A2;  //声明MQ5输入引脚
int sensorValue = 0;   // MQ-5 模拟值0-1023

//蜂鸣器
const int beepPin = 4;  //声明BEEP输入引脚
int beepState = LOW;

//震动传感器
const int SHOCK_PIN = A5;
int SHOCK_NUM=0;//定义震动次数计数
int SHOCK_VALUE=0;//震动模拟量
int SHOCK_TIME=0;

//模拟按键初始化参数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 定义模拟按键引脚
const int BUTTONS_PIN = A4;

// 设置总共几个按键
const int BUTTONS_TOTAL = 6;

//模拟键盘通过读取模拟值获取相应按键
//经测量1为744/743，2为508，3为331,4为144/145,5为0，默认1023
const int BUTTONS_VALUES[BUTTONS_TOTAL] = { 0, 147, 331, 508, 744, 1023 };

//创建模拟按键对象（接口引脚，总按键数，按键值数组）
AnalogMultiButton buttons(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);

//定义模拟按键的值
const int BUTTON_RIGHT = 0;
const int BUTTON_DOWN = 1;
const int BUTTON_UP = 2;
const int BUTTON_LEFT = 3;
const int BUTTON_ENTER = 4;
const int BUTTON_DEFALT = 5;

//按键状态
String key_status = "初始";
//模拟按键初始化参数
//---------------------------------------------------------------------------------------模拟按键初始化参数---------------------------------------------------------------------------------------------------------------------


//edp esp8266初始化参数
//---------------------------------------------------------------------------------------edp esp8266初始化参数------------------------------------------------------------------------------------------------------------------

#define CONNREQ             0x10
#define CONNRESP            0x20
#define PUSHDATA            0x30
#define SAVEDATA            0x80
#define SAVEACK             0x90
#define CMDREQ              0xA0
#define CMDRESP             0xB0
#define PINGREQ             0xC0
#define PINGRESP            0xD0
#define ENCRYPTREQ          0xE0
#define ENCRYPTRESP         0xF0

#define MAX_LEN        200
#define PROTOCOL_NAME       "EDP"
#define PROTOCOL_VERSION    1

typedef unsigned char   uint8;
typedef char            int8;
typedef unsigned int    uint16;
typedef int             int16;
typedef unsigned long   uint32;
typedef long            int32;

typedef struct
{
  uint8 data[MAX_LEN];
  int16 len;
  int16 read_p;
} edp_pkt;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//菜单初始化参数
//---------------------------------------------------------------------------------------菜单初始化参数------------------------------------------------------------------------------------------------------------------

/**
   以下定义菜单项类型
*/
// 菜单最大显示行数
#define MENU_MAX_ROW 4

// 具有子菜单的菜单项
#define MENU_SUBMENU 0
// 参数项（用于执行参数设置）
#define MENU_PARAM 1
// 无动作的菜单项
#define MENU_ACTION_NONE 101
// 执行逻辑参数设置的菜单项（开/关、真/假等设置）
#define MENU_ACTION_LOGIC 102
// 执行数值调整设置的菜单项（时间、音量等设置）
#define MENU_ACTION_NUMBER 103
// 执行字符串设置的菜单项（欢迎语、LED显示文字等设置）
#define MENU_ACTION_STRING 104
//设置逻辑页面
int Current_mode = 0;//0--首页，1--菜单选择




/**
   菜单结构
   一个数组既代表一级菜单，数组中的一个元素就是一个菜单项，就是一个单独的结构体，
   数组中的第一个元素中的num值很重要，表示本级菜单具有多少个菜单项。

   @var int num 本级菜单数量，必须在第一项中设置正确的菜单项数量
   @var char* label 菜单文本
   @var int type 此项类型，参考宏定义
   @var void (*action)(const char *) 指向动作的函数指针，此项要执行的具体动作函数
   @var mymenu* next 下一级菜单，只需在菜单的第一项设置，其他项置空（NULL）即可
   @var mymenu* prev 上一级菜单，同上
*/
struct mymenu {
  int num;
  char *label; //display label
  int type; //0:item, 1:submenu, 2:param
  void(*action)(const char *);
  mymenu * next;
  mymenu * prev;
};

/**
   逻辑参数设置菜单
   逻辑菜单表示菜单项中的action函数要执行逻辑设置动作，即设置某个参数的逻辑值
   逻辑菜单只需两个菜单项代表true和false
   需要遵守的规则为：菜单中的文本需要设置为“ON”和“OFF”，
   在执行动作函数的时候，可以将正确的参数传递过去，
   动作函数的规则参照函数说明
*/

mymenu logic_menu[2] = {
  {2, "ON", MENU_PARAM, NULL, NULL, NULL},
  {2, "OFF", MENU_PARAM, NULL, NULL, NULL}
};

/**
   下面定义了三级菜单说明了菜单应该如何个定义
*/
// 第二级菜单
mymenu light_menu[2] = {
  //第一项什么也不做，所以设置了类型为MENU_ACTION_NONE
  {2, "light 1", MENU_ACTION_NONE, NULL, NULL, NULL},
  //第二项指向了下级菜单，所以设置了类型为MENU_SUBMENU
  {2, "light submenu", MENU_SUBMENU, NULL, NULL, NULL}
};
// 第三级菜单
mymenu test_level3_menu[7] = {
  {7, "mainPage", MENU_ACTION_NONE, NULL, NULL, NULL},
  {7, "level3menu-2", MENU_ACTION_NONE, NULL, NULL, NULL},
  {7, "level3menu-3", MENU_ACTION_NONE, NULL, NULL, NULL},
  {7, "level3menu-4", MENU_ACTION_NONE, NULL, NULL, NULL},
  //定义了一个逻辑动作，这里是控制PIN13脚的LED
  {7, "LED TEST", MENU_ACTION_LOGIC, NULL, NULL, NULL},
  {7, "level3menu-6", MENU_ACTION_NONE, NULL, NULL, NULL},
  {7, "level3menu-7", MENU_ACTION_NONE, NULL, NULL, NULL}
};
// 第一级菜单
mymenu main_menu[4] = {
  {4, "首页", MENU_ACTION_LOGIC, NULL, NULL, NULL},
  {4, "mainPage", MENU_ACTION_NUMBER, NULL, NULL, NULL},
  //指向下一级菜单
  {4, "item 2.1", MENU_SUBMENU, NULL, NULL, NULL},
  {4, "item 3", MENU_ACTION_NONE, NULL, NULL, NULL}
};


// 定义菜单操作需要的全局变量
// 分别为当前菜单、上一级菜单、当前菜单项索引和开始显示的菜单项索引
mymenu *cur_item, *prev_item;
int item_index, start_index;


//菜单初始化参数
//---------------------------------------------------------------------------------------菜单初始化参数------------------------------------------------------------------------------------------------------------------

//定义U8G引脚
U8GLIB_ST7920_128X64_4X u8g(10, 11, 12);




//RTC初始化参数
//---------------------------------------------------------------------------------------RTC初始化参数------------------------------------------------------------------------------------------------------------------
//定义RTC引脚
uint8_t CE_PIN = 5;
uint8_t IO_PIN = 6;
uint8_t SCLK_PIN = 7;

//设置RTC缓存
char buf[50];
char day[10];
char current_time[50];
char current_day[50];
//RTC初始化参数
//---------------------------------------------------------------------------------------RTC初始化参数------------------------------------------------------------------------------------------------------------------

//开机画面
const uint8_t init_first[] PROGMEM = { //欢迎使用Smart Clock
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x60, 0x00, 0x06, 0x18, 0x00,
  0x00, 0xC3, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x60, 0x00, 0x03, 0x77, 0xC0,
  0x00, 0xFF, 0xF8, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x7F, 0x00, 0x03, 0x66, 0xC0,
  0x01, 0x83, 0x00, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xC3, 0x00, 0x00, 0x66, 0xC0,
  0x01, 0x83, 0x00, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x36, 0xC6, 0x00, 0x00, 0x66, 0xC0,
  0x03, 0xBF, 0xF0, 0x00, 0x7F, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0xB0, 0x00, 0x1F, 0x66, 0xC0,
  0x03, 0xB3, 0x30, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0x30, 0x00, 0x03, 0x66, 0xC0,
  0x07, 0xB3, 0x30, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x0C, 0x30, 0x00, 0x03, 0x66, 0xC0,
  0x01, 0xBF, 0xF0, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x1E, 0x78, 0x00, 0x03, 0x7F, 0xC0,
  0x01, 0x83, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x1B, 0x78, 0x00, 0x03, 0x77, 0x80,
  0x01, 0x9B, 0x00, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x33, 0xCC, 0x00, 0x03, 0x66, 0x00,
  0x01, 0x8F, 0x00, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x60, 0xCC, 0x00, 0x03, 0x06, 0x00,
  0x01, 0x86, 0x00, 0x00, 0x63, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x86, 0x00, 0x07, 0x86, 0x00,
  0x01, 0x8F, 0x00, 0x00, 0xC3, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x03, 0x00, 0x0C, 0xFF, 0xE0,
  0x01, 0x99, 0xC0, 0x00, 0xC3, 0x78, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x01, 0x80, 0x00, 0x00, 0x00,
  0x01, 0xF0, 0x78, 0x01, 0x80, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xC0, 0xC3, 0x0F, 0xE3, 0xFE,
  0x1F, 0x9E, 0x01, 0xF0, 0x7E, 0x7B, 0xC0, 0x00,
  0x00, 0x01, 0xFE, 0xE1, 0xC3, 0x0F, 0xFB, 0xFE,
  0x3F, 0xDE, 0x03, 0xFC, 0xFF, 0x7F, 0xC0, 0x00,
  0x00, 0x03, 0xDE, 0xF3, 0xC7, 0x8F, 0x78, 0x78,
  0x7F, 0xDE, 0x07, 0xBD, 0xFF, 0x7F, 0x80, 0x00,
  0x00, 0x03, 0xC0, 0xF3, 0xCF, 0xCF, 0x78, 0x78,
  0x79, 0xFE, 0x07, 0xBD, 0xE7, 0xFF, 0x00, 0x00,
  0x00, 0x03, 0xE0, 0xFF, 0xCF, 0xCF, 0x78, 0x78,
  0x78, 0x1E, 0x07, 0xBF, 0xE0, 0x7E, 0x00, 0x00,
  0x00, 0x01, 0xF8, 0xDE, 0xCC, 0xCF, 0xF8, 0x78,
  0x78, 0x1E, 0x07, 0xBF, 0xE0, 0x7E, 0x00, 0x00,
  0x00, 0x00, 0x7E, 0xDE, 0xDF, 0xEF, 0xE0, 0x78,
  0x78, 0x1E, 0x07, 0xBF, 0xE0, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0x1E, 0xDE, 0xDF, 0xEF, 0xF0, 0x78,
  0x79, 0xFE, 0x07, 0xBF, 0xE7, 0xFF, 0x80, 0x00,
  0x00, 0x03, 0xDE, 0xCC, 0xDC, 0xEF, 0xF0, 0x78,
  0x79, 0xFE, 0x07, 0xBD, 0xE7, 0xFF, 0x80, 0x00,
  0x00, 0x03, 0xDE, 0xCC, 0xDC, 0xEF, 0x78, 0x78,
  0x7F, 0xDE, 0x07, 0xBD, 0xFF, 0x7F, 0xC0, 0x00,
  0x00, 0x03, 0xFE, 0xCC, 0xDC, 0xEF, 0x78, 0x78,
  0x3F, 0xDF, 0xF3, 0xFC, 0xFF, 0x7B, 0xC0, 0x00,
  0x00, 0x00, 0xFC, 0xCC, 0xDC, 0xEF, 0x3C, 0x78,
  0x1F, 0x9F, 0xF1, 0xF0, 0x7E, 0x79, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
  0x00, 0x00, 0xE0, 0x00, 0x00, 0x0E, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
  0x00, 0x00, 0xF0, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E,
  0x00, 0x01, 0xB3, 0x37, 0x8F, 0xC0, 0x3C, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x6D, 0xF9, 0xBB, 0xF6, 0xCD, 0x8E, 0x7F, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77,
  0x6C, 0x01, 0xFB, 0xF6, 0xCD, 0x8E, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77,
  0x7C, 0x03, 0xFA, 0xD4, 0xEF, 0x8E, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x7C, 0x03, 0xBA, 0xD7, 0xEC, 0x0E, 0x7F, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E,
  0x38, 0x03, 0xBA, 0xD3, 0x6F, 0xCE, 0x3E, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF8, 0x00, 0x00, 0x00, 0x1D, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF0, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


static const uint8_t wifi1[] = {  // --  wifi 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0x03, 0x00,
  0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00
  /* (31 X 26 )*/
};

static const uint8_t wifi2[] = {  // --  wifi 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0x00,
  0x00, 0xFC, 0x1F, 0x00, 0x00, 0x1E, 0x3C, 0x00, 0x00, 0x0F, 0x78, 0x00, 0x00, 0x06, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0x03, 0x00,
  0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00
  /* (31 X 26 )*/
};

static const uint8_t wifi3[] = {  // --  wifi 3
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0x00,
  0xC0, 0xFF, 0xFF, 0x01, 0xE0, 0x07, 0xF0, 0x03, 0xF0, 0x00, 0x80, 0x07, 0x60, 0xF0, 0x07, 0x03,
  0x00, 0xFC, 0x1F, 0x00, 0x00, 0x1E, 0x3C, 0x00, 0x00, 0x0F, 0x78, 0x00, 0x00, 0x06, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0x03, 0x00,
  0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00
  /* (31 X 26 )*/
};

static const uint8_t wifi4[] = {  // --  wifi 4
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFE, 0x3F, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0xF0, 0xFF, 0xFF, 0x07, 0xF8, 0x03, 0xE0, 0x0F,
  0x7C, 0x00, 0x00, 0x1F, 0x1E, 0x00, 0x00, 0x3C, 0x0F, 0xFC, 0x1F, 0x78, 0x86, 0xFF, 0xFF, 0x30,
  0xC0, 0xFF, 0xFF, 0x01, 0xE0, 0x07, 0xF0, 0x03, 0xF0, 0x00, 0x80, 0x07, 0x60, 0xF0, 0x07, 0x03,
  0x00, 0xFC, 0x1F, 0x00, 0x00, 0x1E, 0x3C, 0x00, 0x00, 0x0F, 0x78, 0x00, 0x00, 0x06, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0x03, 0x00,
  0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00
  /* (31 X 26 )*/
};

static const uint8_t wifi_no[] = {  // --  no wifi
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0xF0, 0x07, 0x00,
  0x00, 0xF0, 0x07, 0x00, 0xC0, 0xF1, 0xC7, 0x01, 0xF0, 0xF1, 0xC7, 0x07, 0xF8, 0xE1, 0xC3, 0x0F,
  0x7C, 0xE0, 0x03, 0x1F, 0x1E, 0xE0, 0x03, 0x3C, 0x0F, 0xE0, 0x03, 0x78, 0x86, 0xE3, 0xE3, 0x30,
  0xC0, 0xE3, 0xE3, 0x01, 0xE0, 0xE3, 0xE3, 0x03, 0xF0, 0xE0, 0x83, 0x07, 0x60, 0xC0, 0x01, 0x03,
  0x00, 0xCC, 0x19, 0x00, 0x00, 0xCE, 0x39, 0x00, 0x00, 0xCF, 0x79, 0x00, 0x00, 0x86, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0x03, 0x00,
  0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00
  /* (31 X 26 )*/
};
