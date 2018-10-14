
void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();

  /* Name the day of the week */
  memset(day, 0, sizeof(day));  /* clear day buffer */
  switch (t.day) {
    case 1:
      strcpy(day, "Sunday");
      break;
    case 2:
      strcpy(day, "Monday");
      break;
    case 3:
      strcpy(day, "Tuesday");
      break;
    case 4:
      strcpy(day, "Wednesday");
      break;
    case 5:
      strcpy(day, "Thursday");
      break;
    case 6:
      strcpy(day, "Friday");
      break;
    case 7:
      strcpy(day, "Saturday");
      break;
  }

  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day,
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
  snprintf(current_time, sizeof(current_time), "%02d:%02d:%02d",  t.hr, t.min, t.sec);
  snprintf(current_day, sizeof(current_day), "%04d-%02d-%02d  %s",  t.yr, t.mon, t.date, day);
  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
}

////设置时间
//  /* Make a new time object to set the date and time */
//  /*   Tuesday, May 19, 2009 at 21:16:37.            */
//  Time t(2018, 6, 15, 22, 03, 00, 3);
//
//  /* Set the time and date on the chip */
//  rtc.time(t);

//打印时间
/* Loop and print the time every second */
//void loop()
//{
//  print_time();
//  delay(1000);
//}
