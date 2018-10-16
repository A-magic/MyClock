void setup(){
  Serial.begin(9600);

  pinMode(echopinL, INPUT); //设定echo为输入模式
  pinMode(trigpinL, OUTPUT); //设定trig为输出模式
  pinMode(echopinR, INPUT);
  pinMode(trigpinR, OUTPUT);
  pinMode(echopinM, INPUT);
  pinMode(trigpinM, OUTPUT);


  //  myservo2.attach(2);  // 声明舵机引脚，2-7为手臂，8-9为头部
  //  myservo3.attach(3);
  //  myservo4.attach(4);
  //  myservo5.attach(5);
  ////  myservo6.attach(6);
  //  myservo7.attach(7);
  //
  //  myservo8.attach(8);
  //  myservo9.attach(9);

  myservo.attach(2);
  csb(100);

  pinMode(inL0, OUTPUT);//声明直流电机引脚
  pinMode(inL1, OUTPUT);
  pinMode(inR0, OUTPUT);
  pinMode(inR1, OUTPUT);


  //下面程序开始时让控制端都为高电平，电机保持不动。
  digitalWrite(inL0, HIGH);
  digitalWrite(inL1, HIGH);
  digitalWrite(inR0, HIGH);
  digitalWrite(inR1, HIGH);



  pinMode(A0, INPUT);   //红外壁障器1
  pinMode(A5, INPUT);   //红外壁障器2

  //手柄初始化
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
  //手柄初始化

//定义0~6脚是输出PWM控制舵机
for(int i = 0; i < 6; i++) pinMode(PWMPin[i], OUTPUT);

  
}

