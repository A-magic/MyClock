//控制小车方向

//电机驱动
void Go_run()
{
  digitalWrite(inL0, HIGH);
  digitalWrite(inL1, LOW);
  digitalWrite(inR0, HIGH);
  digitalWrite(inR1, LOW);
  analogWrite(inLpwm, value_L);
  analogWrite(inRpwm, value_R);
}

//右转弯掉头
void Diaotou_right()
{
  value_L = 250 ;
  value_R = 0 ;
  Serial.println("diao-right");
  Go_run();
  delay(1700);
}

//左转弯掉头
void Diaotou_left()
{
  value_L = 0 ;
  value_R = 250 ;
  Serial.println("diao-left");
  Go_run();
  delay(1700);
}

//右转弯
void right()
{
  value_L = L_run ;
  value_R = 0 ;
  Serial.println("right");
  Go_run();
  delay(550);
}

//左转弯
void left()
{
  value_L = 0 ;
  value_R = R_run ;
  Serial.println("left");
  Go_run();

  delay(550);
}

//大左转
void Da_left()
{
  value_L = L_run ;
  value_R = R_run ;
  Go_run(); Go_run();
  delay(100);
}

//大右转
void Da_right()
{
  value_L = L_run ;
  value_R = R_run ;
   Go_run();
  delay(100);
}
//===========  电机动作  ===============//
//高速前进
void Gogo()
{
  value_L = L_run ;    //将电机运行值赋予驱动变量
  value_R = R_run ;    //同上
  Go_run();   //运行电机驱动函数
}

//低速前进
void Go()
{
  value_L = L_run ;
  value_R = R_run ;
  Go_run();
}

//高速后退
void GoGo_back()
{
  value_L = L_run ;
  value_R = R_run ;

  digitalWrite(inL0, LOW);
  digitalWrite(inL1, HIGH);
  digitalWrite(inR0, LOW);
  digitalWrite(inR1, HIGH);
  analogWrite(inLpwm, value_L);
  analogWrite(inRpwm, value_R);
  delay(80);                      //驱动延时：即为高速后退运行时间
}

//停止
void stop()
{
  value_L = 0 ;
  value_R = 0 ;
  analogWrite(inLpwm,value_L);      //PWM调速
  analogWrite(inRpwm,value_R);
  Serial.println("stop");         //此为串口输出stop字符，专为调试时使用，运行该函数即输出stop字符，可帮助判断运行情况
}



//void _mRun(int L_run, int  R_run) //电机正转，电机到底是右转还是左转取决于电机端的接线和控制脚的顺序
//{
//  digitalWrite(inL0, HIGH);
//  digitalWrite(inL1, LOW);
//  digitalWrite(inR0, HIGH);
//  digitalWrite(inR1, LOW);
//  analogWrite(inLpwm, L_run);
//  analogWrite(inRpwm, R_run);
//}
//void _mBack(int L_run, int  R_run) //同上
//{
//  digitalWrite(inL0, LOW);
//  digitalWrite(inL1, HIGH);
//  digitalWrite(inR0, LOW);
//  digitalWrite(inR1, HIGH);
//  analogWrite(inLpwm, L_run);
//  analogWrite(inRpwm, R_run);
//}
//void _mLeft(int L_run, int  R_run) //同上
//{
//  digitalWrite(inL0, HIGH);
//  digitalWrite(inL1, LOW);
//  digitalWrite(inR0, LOW);
//  digitalWrite(inR1, HIGH);
//  analogWrite(inLpwm, L_run);
//  analogWrite(inRpwm, R_run);
//}
//
//void _mRight(int L_run, int  R_run) //同上
//{
//  digitalWrite(inL0, LOW);
//  digitalWrite(inL1, HIGH);
//  digitalWrite(inR0, HIGH);
//  digitalWrite(inR1, LOW);
//  analogWrite(inLpwm, L_run);
//  analogWrite(inRpwm, R_run);
//}
//void _mStop() //紧急制动，实际就是将电机两个端短接了
//{
//  digitalWrite(inL0, HIGH);
//  digitalWrite(inL1, HIGH);
//  digitalWrite(inR0, HIGH);
//  digitalWrite(inR1, HIGH);
//}


void UART_Send_END(void) //HMI的结束符，上传屏幕参数后
{
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}



