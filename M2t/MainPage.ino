
//设置主页显示内容
void mainPage(const char *stat)
{
  u8g.firstPage( );
  do
  {
    print_time();
	
    u8g.setFont(u8g_font_6x13);
    u8g.setPrintPos( 10, 10);
    u8g.print(current_day);


    u8g.setFont(u8g_font_osr21r);
    u8g.setPrintPos( 5, 38);
    u8g.print(current_time);

	readDht();

	u8g.setFont(u8g_font_6x13);
	u8g.setPrintPos(5, 64);
	u8g.print(DHT11.temperature);
	u8g.setPrintPos(20, 64);
	u8g.print("C");
	
	u8g.setPrintPos(64, 64);
	u8g.print(DHT11.humidity);
	u8g.setPrintPos(80, 64);
	u8g.print('%');

  }
  while ( u8g.nextPage( ));
}

