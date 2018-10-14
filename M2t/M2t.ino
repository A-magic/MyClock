
#include <AnalogMultiButton.h>
#include <U8glib.h> //声明库
#include <dht11.h>//温湿度传感器
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <stdlib.h>
#include "Def_Para.h"
#include <Thread.h>
#include <ThreadController.h>

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread
Thread myThread = Thread();


//创建RTC对象
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

//创建DHT11对象
dht11 DHT11;

edp_pkt *pkt;

bool stat;

// 定义LCD背光显示计时变量，无按键操作超时就关闭背光
unsigned long starttime;

//获取运行时间
unsigned long endtime = millis();

// 定义菜单的操作按键（上、下、进入和返回）状态变量
bool old_up_stat, old_down_stat, old_enter_stat, old_exit_stat;

void setup() {
  //设置LCD背光引脚为输出
  pinMode(LIGHT_PIN, OUTPUT);

  //设置蜂鸣器不响
  pinMode(beepPin, OUTPUT);
  digitalWrite(beepPin, LOW);

  //设置震动传感器
  pinMode(SHOCK_PIN, INPUT);

  //设置继电器关
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  //背光开
  backlight("ON");
  stat = false;

  //设置波特率
  Serial.begin(9600);
  Serial3.begin(115200);

  //初始化RTC
  rtc.write_protect(false);
  rtc.halt(false);

  //  //设置震动传感器中断
  //  pinMode( 2, INPUT);
  //  attachInterrupt( digitalPinToInterrupt(2), shock_test, LOW);

  //  //初始化LCD12864,显示开欢迎画面
  //  //设置字体
  //  u8g.setFont(u8g_font_6x13);
  //
  //  //显示smart_clock欢迎界面1s
  //  u8g.firstPage();
  //  do {
  //    u8g.drawBitmapP(0, 0, 16, 64, init_first);
  //  } while (u8g.nextPage());


  /**
     菜单的进一步设置
     在这里将每一个菜单的关联设置好
     对照每一个初始设置仔细填写它们之间的关系
  */
  //第一级（main_menu）的第三项指向了下一级菜单（light_menu)
  main_menu[2].next = light_menu;

  main_menu[1].action = mainPage;
  main_menu[2].action = ledtest;

  //第二级（light_menu）的上一级（main_menu）
  light_menu[0].prev = main_menu;

  //第二级（light_menu）的第二项指向了下一级菜单（test_level3_menu）
  light_menu[1].next = test_level3_menu;

  //第三级（test_level3_menu）的上一级（light_menu）
  test_level3_menu[0].prev = light_menu;

  //第三级（test_level3_menu）的第五项定义了个逻辑动作
  test_level3_menu[4].action = ledtest;



  /**
     初始化当前菜单为第一级（main_menu）
  */
  cur_item = main_menu;
  /**
     上一级菜单为空
  */
  prev_item = NULL;
  /**
     当前选择了第一项
  */
  item_index = 0;
  /**
     从第一项开始显示菜单
  */
  start_index = 0;

  //建立esp8266连接
  edpInit();

  //所有初始化完成，清屏并关闭LCD背光
  u8g.firstPage();
  do {
    //display
  } while (u8g.nextPage());


  starttime = millis();

  // Configure myThread
  myThread.onRun(edpConn);
  myThread.setInterval(1000);
  controll.add(&myThread);
  
  //Time t(2018, 6, 15, 22, 05, 00, 6);//设置时间函数
  //  rtc.time(t);
}


void loop() {
  //开始edp后台线程传送
  controll.run();

  //  if (millis() - SHOCK_TIME > 300)
  //    interrupts();

  //获取运行时间
  endtime = millis();
  //计算无按键时间，决定是否关闭LCD背光
  if (endtime - starttime > 100000) {
    backlight("OFF");
  }

  buttons.update();

  if (buttons.onRelease(BUTTON_ENTER))
  {
    starttime = endtime;
    Current_mode = 1;
  }
  Serial.println(Current_mode);
  switch (Current_mode)
  {
    case 0:
      mainPage("1");
      break;
    case 1:
      choosMenu();
      break;
    default:
      break;
  }
}




