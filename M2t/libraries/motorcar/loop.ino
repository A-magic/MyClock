void loop()
{
readaction();
//  switch (control_mode) {
//    case 1:  //自动巡逻模式
      if (digitalRead(Sensor_L) && digitalRead(Sensor_R))    //前方无障碍
      {
        CJ();             //超声波测距
        JL_Panduan();     //距离判断并动作
        L_R();
      }
      else
      {
        stop();
        GoGo_back();  //后退
        delay(300);
        stop();
        LR_panduan(); //左右判断
        L_R();        //左右选择转向
      }
//      break;

    //  switch (control_mode) {
    //    case 1:  //自动巡逻模式
    //
    //

    //      ////向串口以及HMI屏发送距离参数
    //      //  dL = get_distance(echopinL, trigpinL);
    //      //  Serial.print("t0.txt=\"left    " + (String)dL + "cm\"");
    //      //  Serial1.print("t0.txt=\"left    " + (String)dL + "cm\"");
    //      //  UART_Send_END();
    //      //
    //      //  dM = get_distance(echopinM, trigpinM);
    //      //  Serial.print("t1.txt=\"right    " + (String)dM + "cm\"");
    //      //  Serial1.print("t1.txt=\"right    " + (String)dM + "cm\"");
    //      //  UART_Send_END();
    //      //
    //      //  dR = get_distance(echopinR, trigpinR);
    //      //  Serial.println("t2.txt=\"front    " + (String)dR + "cm\"");
    //      //
    //      //  Serial1.print("t2.txt=\"front    " + (String)dR + "cm\"");
    //      //  UART_Send_END();
    //
//    case 2://PS2手柄控制模式
//      if(ps2x.ButtonPressed(GREEN_FRET))
//      Serial.println("Green Fret Pressed");
//    if(ps2x.ButtonPressed(RED_FRET))
//      Serial.println("Red Fret Pressed");
//      break;
//
//    default:
//    stop();
//      break;
  }



