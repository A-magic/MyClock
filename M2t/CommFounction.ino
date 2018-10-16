//控制蜂鸣器
void beepGo()
{
  digitalWrite(beepPin, HIGH);
  delay(20);
  digitalWrite(beepPin, LOW);
}
/**
   关闭LCD背光
   此函数符合菜单动作定义规则，即无返回值、一个字符串参数

   @var const char* stat 值为“ON"打开背光，为“OFF”关闭背光
*/
void backlight(const char *stat)
{
  //这里定义了一个逻辑动作
  //根据参数决定LCD背光的开关
  digitalWrite(LIGHT_PIN, strcmp(stat, "ON") ? LOW : HIGH);
}

/**
   逻辑动作测试函数
   @var const char* stat 根据此参数来执行动作，这里测试PIN13的LED
*/
void ledtest(const char *stat)
{
  //根据参数决定LED开关
  digitalWrite(LED_PIN, strcmp(stat, "ON") ? LOW : HIGH);
}

void shock_test() //震动开关测试
{
  noInterrupts(); //先关闭中断，待会再打开
  SHOCK_VALUE = analogRead(SHOCK_PIN);

  if (SHOCK_VALUE == 0)
  {
    SHOCK_NUM++;
    Serial.print("SHOCK_NUM:");
    Serial.println(SHOCK_NUM);
  }
  SHOCK_TIME = millis();
}
