/**
   绘制单个菜单项

   @var struct mymenu item 要绘制的项目
   @var int row 绘制坐标（LCD5110绘制文字时只需一个行坐标即可，可根据实际显示设备调整）
   @var bool rev 是否反相绘制，默认为不反相绘制（用于当前选中项绘制，可根据实际显示设备调整）
*/
void renderItem(struct mymenu item, int row, bool rev = false)
{
	uint8_t i, h;
	u8g_uint_t w, d;
	i = 1;
	h = u8g.getFontAscent() - u8g.getFontDescent();
	w = u8g.getWidth();

	char label[15];
	//规范显示项目文字（左对齐，补空格）
	sprintf(label, "%-14s", item.label);
	u8g.setDefaultForegroundColor();
	if (rev) {
		//u8g的方向颜色绘制
		u8g.drawBox(0, row, w, h);
		u8g.setDefaultBackgroundColor();
	}
	u8g.drawStr(10, row, label);

	if (rev) {
		//u8g的方向颜色绘制
		//    u8g.setColorIndex(0);
	}
}

/**
   绘制某一级菜单

   @var struct mymenu* items 需要绘制的菜单
   @var int menu_num 菜单项目数量
*/
void renderMenu(struct mymenu * items, int menu_num)
{
	//绘制数量不能超过每一屏的最大绘制数量
	int num = menu_num > MENU_MAX_ROW ? MENU_MAX_ROW : menu_num;

	u8g.setFont(u8g_font_6x13);
	u8g.setFontRefHeightText();
	u8g.setFontPosTop();

	u8g.firstPage();
	do {
		for (int i = 0; i < num; i++) {
			//绘制每个菜单项
			renderItem(items[i + start_index], i * 16, i == item_index ? true : false);
		}
	} while (u8g.nextPage());

}


void choosMenu()
{
	//获取运行时间
	endtime = millis();
	//获取当前菜单的项目数量
	int menu_num = cur_item[0].num;
	//定义一个临时变量
	int idx;

	//绘制菜单
	renderMenu(&cur_item[0], menu_num > MENU_MAX_ROW ? MENU_MAX_ROW : menu_num);

	//读取模拟按键的值
	buttons.update();

	//有键按下，打开LCD背光，计时清零
	if (buttons.onRelease(BUTTON_ENTER) || buttons.onRelease(BUTTON_LEFT) || buttons.onRelease(BUTTON_RIGHT) || buttons.onRelease(BUTTON_UP) || buttons.onRelease(BUTTON_DOWN)) {
		backlight("ON");
		starttime = endtime;

	}
	//按键动作
	if (buttons.onRelease(BUTTON_DEFALT))
	{
		key_status = "默认";
	}
	else if (buttons.onRelease(BUTTON_ENTER))
	{
		key_status = "回车";
		//计算此时的菜单项索引值
		idx = start_index + item_index;
		if (cur_item[idx].next != NULL && cur_item[idx].type == MENU_SUBMENU) {
			//条件成立说明此菜单项指向了下一级菜单
			//此级菜单变成了上一级菜单
			prev_item = cur_item;
			//将指向的下一级菜单设置为当前菜单
			cur_item = cur_item[idx].next;
			//重置菜单项索引和绘制索引
			item_index = 0;
			start_index = 0;
			//清屏
			u8g.firstPage();
			do {
				//display
			} while (u8g.nextPage());
		}
		else if (cur_item[idx].action != NULL && cur_item[idx].type != MENU_PARAM) {
			//条件成立说明此项菜单是动作
			//此级菜单变成上一级菜单
			prev_item = cur_item;
			//根据动作类型调用相应的下一级菜单
			switch (cur_item[idx].type) {
			case MENU_ACTION_LOGIC:
				//将动作函数传递给逻辑菜单，使逻辑菜单能够正确执行动作
				logic_menu[0].action = cur_item[idx].action;
				//设置当前菜单为逻辑菜单
				cur_item = logic_menu;
				//重置菜单项索引和绘制索引
				item_index = 0;
				start_index = 0;
				break;
			case MENU_ACTION_NUMBER:
				Current_mode = 0;
				break;
			case MENU_ACTION_STRING:
				break;
			default:
				break;
			}
			//清屏
			u8g.firstPage();
			do {
				//display
			} while (u8g.nextPage());
		}
		else if (cur_item[idx].type == MENU_PARAM) {
			//条件成立说明正在执行动作
			//调用相应的动作函数，并传递参数（这里只举例逻辑设置）
			cur_item[0].action((const char *)cur_item[idx].label);
		}
	}
	else if (buttons.onRelease(BUTTON_LEFT))
	{
		key_status = "左";
		//返回上一级菜单的操作
		if (prev_item != NULL) {
			//设置上一级菜单为当前菜单
			cur_item = prev_item;
			//设置当前菜单的上一级菜单
			prev_item = cur_item[0].prev;
			//重置菜单项索引和绘制索引
			item_index = 0;
			start_index = 0;
			//清屏
			u8g.firstPage();
			do {
				//display
			} while (u8g.nextPage());
		}
	}
	else if (buttons.onRelease(BUTTON_RIGHT))
	{
		key_status = "右";

	}
	else if (buttons.onRelease(BUTTON_UP))
	{
		key_status = "上";
		item_index--;
		Serial.print("item_indexshang=");
		Serial.println(item_index);
	}
	else if (buttons.onRelease(BUTTON_DOWN))
	{
		key_status = "下";
		item_index++;
		Serial.print("item_indexxia=");
		Serial.println(item_index);
	}
	else
	{
		key_status = "其他";
	}

	Serial.print("key_status=");
	Serial.println(key_status);
	Serial.print("item_index=");
	Serial.println(item_index);
	/**
	   菜单项上下选择是否越界
	*/
	if (item_index < 0) {
		item_index = 0;
		start_index--;
		if (start_index < 0) start_index = 0;
	}
	if (item_index >= MENU_MAX_ROW || item_index >= menu_num) {
		if (item_index >= menu_num) item_index = menu_num - 1;
		if (item_index >= MENU_MAX_ROW) item_index = MENU_MAX_ROW - 1;
		if (start_index + MENU_MAX_ROW < menu_num) start_index++;
	}
	//renderClock(0, 0);
}


