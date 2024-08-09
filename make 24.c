#include <stdio.h>
#include <math.h>//加减乘除运算
#include <time.h>//随机数函数
#include <stdlib.h>//整型数转字符串
#include <graphics.h>// 引用EasyX绘图库头文件
#include <conio.h>//使用_getch()
#include <string.h>//复制用户名
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <mmsystem.h>//包含多媒体设备接口头文件
#pragma comment(lib,"Winmm.lib")// 加载静态库

using namespace std;

//按钮函数：
struct Button
{
	int x1;
	int x2;
	int y1;
	int y2;
};
void ShowButton(Button btn, int x1, int y1, int x2, int y2, char text[1000], int tlength, int twidth, int tsetoff1, int tsetoff2, string bcolor, string tcolor)
{
	btn.x1 = x1;
	btn.x2 = x2;
	btn.y1 = y1;
	btn.y2 = y2;//设置顶点坐标
	if (bcolor == "GREEN")setfillcolor(GREEN);
	else if (bcolor == "BLUE")setfillcolor(BLUE);
	else if (bcolor == "WHITE")setfillcolor(WHITE);
	fillroundrect(btn.x1, btn.y1, btn.x2, btn.y2, 10, 8);//绘制按钮边框
	//设置按钮文字:
	setbkmode(TRANSPARENT);//设置字体背景为透明
	if (tcolor == "WHITE")settextcolor(WHITE);
	else if (tcolor == "BLACK")settextcolor(BLACK);//设置字体颜色
	settextstyle(tlength, twidth, _T("Arial BLACK"));//设置字体格式
	outtextxy(x1 + tsetoff1, y1 + tsetoff2, text);//设置显示位置
}

//鼠标悬浮按钮变色函数：
bool isMouseOver; // 表示鼠标是否在按钮上方
void checkMouseOver(int mouseX, int mouseY, Button btn, int x1, int y1, int x2, int y2, char text[1000], int tlength, int twidth, int tsetoff1, int tsetoff2, string bcolor, string tcolor)
{
	btn.x1 = x1;
	btn.x2 = x2;
	btn.y1 = y1;
	btn.y2 = y2;
	isMouseOver = (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2);
	FlushBatchDraw();

	if (isMouseOver)
	{
		ShowButton(btn, x1, y1, x2, y2, text, tlength, twidth, tsetoff1, tsetoff2, "BLUE", "WHITE");
	}
	else
	{
		ShowButton(btn, x1, y1, x2, y2, text, tlength, twidth, tsetoff1, tsetoff2, "GREEN", "WHITE");
	}
}

// 检查鼠标点击是否在按钮内
bool checkClick(int x1, int y1, int x2, int y2)
{
	ExMessage msg0;
	while (1)
	{
		if (peekmessage(&msg0, EM_MOUSE))
		{
			switch (msg0.message)
			{
			case WM_LBUTTONDOWN:
				if (msg0.x >= x1 && msg0.x <= x2 && msg0.y >= y1 && msg0.y <= y2)
				{
					return 1;
				}
				break;
			}
		}
		else
			return 0;
	}
}

//1-10随机数函数:
int nums[4];
void num()
{
	Button btn[4] = { 0 };
	srand(time(NULL));
	char text1[3];
	char text2[3];
	char text3[3];
	char text4[3];
	nums[0] = rand() % 10 + 1;
	nums[1] = rand() % 10 + 1;
	nums[2] = rand() % 10 + 1;
	nums[3] = rand() % 10 + 1;
	itoa(nums[0], text1, 10);
	itoa(nums[1], text2, 10);
	itoa(nums[2], text3, 10);
	itoa(nums[3], text4, 10);
	ShowButton(btn[0], 105, 125, 205, 275, text1, 130, 40, (32 - textwidth(text1) / 2), (26 - textheight(text1) / 2), "WHITE", "BLACK");//未知错误，两位数显示位置不能居中
	ShowButton(btn[1], 255, 125, 355, 275, text2, 130, 40, (50 - textwidth(text2) / 2), (75 - textheight(text2) / 2), "WHITE", "BLACK");
	ShowButton(btn[2], 405, 125, 505, 275, text3, 130, 40, (50 - textwidth(text3) / 2), (75 - textheight(text3) / 2), "WHITE", "BLACK");
	ShowButton(btn[3], 555, 125, 655, 275, text4, 130, 40, (50 - textwidth(text4) / 2), (75 - textheight(text4) / 2), "WHITE", "BLACK");
}

//倒计时函数:
int timesum;
void timecount(int timesum)
{
	int seconds = timesum * 60; //分钟转换为秒
	int minutes, seconds_remaining;
	char countdown_str[100];
	char countdown_array[305][100];
	int i = seconds, j = 0;
	while ((checkClick(590, 400, 710, 440) != 1) && (i > 0))
	{
		minutes = i / 60;
		seconds_remaining = i % 60;
		sprintf(countdown_str, "%02d:%02d", minutes, seconds_remaining); // 将倒计时格式化为字符串
		strcpy(countdown_array[j], countdown_str); // 将倒计时字符串赋值给字符串数组
		settextcolor(WHITE);
		settextstyle(40, 15, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(200, 44, countdown_array[j]);
		Sleep(1000); // 等待1秒（Sleep函数以毫秒为单位）
		setfillcolor(0x3B0000);
		solidroundrect(180, 40, 300, 90, 10, 8);//覆盖先前的倒计时以实现刷新
		i--;
		j++;
	}
}

Button btns1[8] = { 0 }; //初始化按钮结构体数组
char tex11[1000] = _T("Difficulty Setting");
char tex21[1000] = _T("Ranking list");
char tex31[1000] = _T("Game Rule");
char tex41[1000] = _T("Exit Game");
char tex51[1000] = _T("Load Game");
char tex61[1000] = _T("Return");
char tex71[1000] = _T("Submit");
char tex81[1000] = _T("Confirm");

//清屏再来一局：
void clearmore(int o, char round[], char text6[], char equation[])
{
	cleardevice();
	setfillcolor(0x3B0000);
	solidroundrect(650, 48, 673, 80, 10, 8);//覆盖局次数以实现刷新
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(50, 50, _T("Countdown:"));//倒计时提示语
	itoa(o + 2, round, 10);
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(580, 50, _T("Round:     / 3"));//本轮进行次数
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(658, 50, round);

	num();//随机数牌

	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(220, 308, _T("Available operator :  +  -  x  /  (  )"));//可用符号
	ShowButton(btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "GREEN", "WHITE");//退出键
	ShowButton(btns1[6], 590, 400, 710, 440, tex71, 30, 10, 25, 5, "GREEN", "WHITE");//提交键

	setfillcolor(WHITE);
	fillroundrect(230, 370, 530, 400, 10, 8);//绘制输入框

	//算式输入框弹窗：
	InputBox(equation, 1000, "算式：", NULL, NULL, 250, 100);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(27, 9, _T("Arial BLACK"));
	outtextxy(244, 371, "Equation：");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 12, _T("Arial"));
	outtextxy(350, 373, equation);//打印算式
	timecount(timesum);//倒计时
}

//清屏回主页面函数:
void clear()
{
	cleardevice();//清空屏幕

	settextcolor(WHITE);
	settextstyle(80, 30, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(260, 55, _T("Make 24"));
	settextcolor(WHITE);
	settextstyle(20, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(252, 465, _T("@Copyright NJUPTB230302"));
	ShowButton(btns1[0], 293, 175, 467, 220, tex11, 33, 10, 5, 7, "GREEN", "WHITE");
	ShowButton(btns1[1], 293, 265, 467, 310, tex21, 33, 10, 30, 7, "GREEN", "WHITE");
	ShowButton(btns1[2], 293, 355, 467, 400, tex31, 33, 10, 34, 7, "GREEN", "WHITE");
	ShowButton(btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "GREEN", "WHITE");
	ShowButton(btns1[4], 590, 400, 710, 440, tex51, 30, 10, 6, 5, "GREEN", "WHITE");
}

//24点判断：
// 定义操作数栈的结构体
typedef struct {
	double data[100];
	int top;
} Stack;

// 初始化栈
void initStack(Stack* s) {
	s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack* s) {
	return s->top == -1;
}

// 入栈
void push(Stack* s, double value) {
	s->top++;
	s->data[s->top] = value;
}

// 出栈
double pop(Stack* s) {
	double value = s->data[s->top];
	s->top--;
	return value;
}

// 获取栈顶元素
double peek(Stack* s) {
	return s->data[s->top];
}

// 计算四则运算表达式的值
double calculate(char* expression) {
	Stack numStack; // 数字栈
	Stack opStack;  // 操作符栈
	initStack(&numStack);
	initStack(&opStack);

	char* ptr = expression;
	while (*ptr != '\0') {
		if (*ptr >= '0' && *ptr <= '9') {
			double num = strtod(ptr, &ptr);
			push(&numStack, num);
		}
		else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
			while (!isEmpty(&opStack) && ((*ptr == '*' || *ptr == '/') || ((*ptr == '+' || *ptr == '-') && (peek(&opStack) == '*' || peek(&opStack) == '/')))) {
				char op = pop(&opStack);
				double num2 = pop(&numStack);
				double num1 = pop(&numStack);
				switch (op) {
				case '+':
					push(&numStack, num1 + num2);
					break;
				case '-':
					push(&numStack, num1 - num2);
					break;
				case '*':
					push(&numStack, num1 * num2);
					break;
				case '/':
					push(&numStack, num1 / num2);
					break;
				}
			}
			push(&opStack, *ptr);
			ptr++;
		}
		else {
			ptr++;
		}
	}

	while (!isEmpty(&opStack)) {
		char op = pop(&opStack);
		double num2 = pop(&numStack);
		double num1 = pop(&numStack);
		switch (op) {
		case '+':
			push(&numStack, num1 + num2);
			break;
		case '-':
			push(&numStack, num1 - num2);
			break;
		case '*':
			push(&numStack, num1 * num2);
			break;
		case '/':
			push(&numStack, num1 / num2);
			break;
		}
	}

	return pop(&numStack);
}

// 判断是否能得出24：
bool calculate_24_helper(int nums[], int n)
{
	if (n == 1)
	{
		return nums[0] == 24;
	}
	int new_nums[4];
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int m = 0;
			for (int k = 0; k < n; k++)
			{
				if (k != i && k != j)
				{
					new_nums[m++] = nums[k];
				}
			}
			new_nums[m] = nums[i] + nums[j];
			if (calculate_24_helper(new_nums, n - 1)) return true;
			new_nums[m] = nums[i] - nums[j];
			if (calculate_24_helper(new_nums, n - 1)) return true;
			new_nums[m] = nums[j] - nums[i];
			if (calculate_24_helper(new_nums, n - 1)) return true;
			new_nums[m] = nums[i] * nums[j];
			if (calculate_24_helper(new_nums, n - 1)) return true;
			if (nums[j] != 0)
			{
				new_nums[m] = nums[i] / nums[j];
				if (calculate_24_helper(new_nums, n - 1)) return true;
			}
			if (nums[i] != 0)
			{
				new_nums[m] = nums[j] / nums[i];
				if (calculate_24_helper(new_nums, n - 1)) return true;
			}
		}
	}
	return false;
}
bool calculate_24(int nums[])
{
	return calculate_24_helper(nums, 4);
}

// 判断主函数
int play_game(char equation[], int nums[])
{
	if (strcmp(equation, "NO") == 0)
	{
		if (calculate_24(nums))
		{
			return 0; // 如果能得到24且输入了NO，则玩家不得分
		}
		else
		{
			return 1; // 如果无法得到24且输入了NO，则玩家得分
		}
	}
	else if (strcmp(equation, "") == 0)//输入为空也不得分
		return 0;
	else
	{
		int result;
		result = calculate(equation); // 将输入的表达式转换为整数
		if (result == 24 && calculate_24(nums))
		{
			return 1; // 如果输入的表达式值为24且能得到24，则玩家得分
		}
		else
		{
			return 0; // 否则不得分
		}
	}
}

// 排行榜: 
typedef struct //用户名，积分结构体数组
{
	char username[50];
	char score[5];
} User;
User  players[1000];
int num_users = 0;
char name[30];
int scoresum = 0;

void add_user(char* n)//将收集到的玩家信息录入结构体数组
{
	strcpy(players[num_users].username, n);
	itoa(scoresum, players[num_users].score, 10);
	num_users++;
}

void update_scoreboard(char playername[], char score[])// 玩家信息写入txt中
{
	FILE* fp = fopen("24game usersdata.txt", "a");
	fprintf(fp, "%s %s\n", players[num_users].username, players[num_users].score);
	fclose(fp);
}

void read()// 重新从txt中读取玩家信息到数组中
{
	FILE* fp = fopen("24game usersdata.txt", "r");
	int num_players = 0;
	while (fscanf(fp, "%s %s", players[num_players].username, players[num_players].score) == 2)
	{
		num_players++;
	}
	fclose(fp);
}

// 比较函数，用于排序（按得分从高到低）
int compare_scores(const void* a, const void* b)
{
	return ((User*)b)->score - ((User*)a)->score;
}

//排序并显示积分榜：
void show_scoreboard()
{
	// 按得分排序
	qsort(players, num_users, sizeof(User), compare_scores);

	// 显示积分排行
	setfillcolor(0x3B0000);
	solidroundrect(250, 150, 600, 400, 10, 8);//覆盖先前的文字
	for (int i = 0; i < num_users && i < 5; i++)
	{

		settextcolor(WHITE);
		settextstyle(40, 13, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(330, 150 + 50 * i, players[i].username);
		settextcolor(WHITE);
		settextstyle(40, 13, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(530, 150 + 50 * i, players[i].score);
	}
}

int main()
{
	int isok;
	initgraph(760, 500);// 创建绘图窗口，大小760x500
	setbkcolor(0x3B0000);//设置背景颜色
	cleardevice();//刷新背景颜色
	HWND b = GetHWnd();//获取窗口句柄
	SetWindowText(b, "24点小游戏");//更改窗口标题

	int p = 1;//控制整个游戏循环
	do
	{
		p = 1;
		//初始界面：
		settextcolor(WHITE);
		settextstyle(80, 30, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(260, 55, _T("Make 24"));
		settextcolor(WHITE);
		settextstyle(20, 10, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(252, 465, _T("@Copyright NJUPTB230302"));

		ShowButton(btns1[0], 293, 175, 467, 220, tex11, 33, 10, 5, 7, "GREEN", "WHITE");
		ShowButton(btns1[1], 293, 265, 467, 310, tex21, 33, 10, 30, 7, "GREEN", "WHITE");
		ShowButton(btns1[2], 293, 355, 467, 400, tex31, 33, 10, 34, 7, "GREEN", "WHITE");
		ShowButton(btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "GREEN", "WHITE");
		ShowButton(btns1[4], 590, 400, 710, 440, tex51, 30, 10, 6, 5, "GREEN", "WHITE");

		int n = 1;//控制主界面循环
		int o = 0;//控制一轮三次游戏循环
		int difficultychoose = 0;//控制难度选择界面循环
		ExMessage msg; //声明消息指针
		while (n)
		{
			if (peekmessage(&msg, EM_MOUSE))
			{
				switch (msg.message)
				{
				case WM_LBUTTONDOWN://按鼠标左键
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 175 && msg.y <= 220)//难度选择界面
					{
						cleardevice();//清空屏幕

						settextcolor(WHITE);
						settextstyle(80, 30, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(260, 55, _T("Make 24"));
						settextcolor(WHITE);
						settextstyle(20, 10, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(252, 465, _T("@Copyright NJUPTB230302"));
						n = 0;

						HWND b = GetHWnd();//获取窗口句柄
						int m = 1;//控制难度选择界面的按键循环
						while (m)
						{
							if (peekmessage(&msg, EM_MOUSE))
							{
								switch (msg.message)
								{
								case WM_LBUTTONDOWN:
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 160 && msg.y <= 200)
									{
										isok = MessageBox(b, "您已成功选择游戏难度等级！", "提示：", MB_OK);
										difficultychoose = 1;
										timesum = 5;
										clear();//回初始界面
										m = 0;
										n = 1;
										break;
									}
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 260 && msg.y <= 300)
									{
										isok = MessageBox(b, "您已成功选择游戏难度等级！", "提示：", MB_OK);
										difficultychoose = 1;
										timesum = 3;
										clear();//回初始界面
										m = 0;
										n = 1;
										break;
									}
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 360 && msg.y <= 400)
									{
										isok = MessageBox(b, "您已成功选择游戏难度等级！", "提示：", MB_OK);
										difficultychoose = 1;
										timesum = 1;
										clear();//回初始界面
										m = 0;
										n = 1;
										break;
									}
								case WM_MOUSEMOVE://鼠标移动，按键变色
									Button btns2[3] = { 0 }; //初始化按钮结构体数组
									char tex12[1000] = _T("Easy：5 minutes（5points）");
									char tex22[1000] = _T("Normal：3 minutes（10points）");
									char tex32[1000] = _T("Hard：1 minutes（15points）");
									FlushBatchDraw();//防止文字因频繁绘制产生闪烁
									checkMouseOver(msg.x, msg.y, btns2[0], 200, 160, 560, 200, tex12, 33, 10, 55, 4, "BLUE", "WHITE");
									checkMouseOver(msg.x, msg.y, btns2[1], 200, 260, 560, 300, tex22, 33, 10, 35, 4, "BLUE", "WHITE");
									checkMouseOver(msg.x, msg.y, btns2[2], 200, 360, 560, 400, tex32, 33, 10, 52, 4, "BLUE", "WHITE");
								}
							}
						}
						break;
					}
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 265 && msg.y <= 310)//排行榜界面
					{
						cleardevice();//清屏

						settextcolor(WHITE);
						settextstyle(70, 25, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(160, 30, _T("Top five masters:"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(147, 105, _T("Rank:             Name:             Score:"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 150, _T("1、"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 200, _T("2、"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 250, _T("3、"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 300, _T("4、"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 350, _T("5、"));
						settextcolor(WHITE);
						settextstyle(20, 10, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(252, 465, _T("@Copyright NJUPTB230302"));

						read();//读取玩家信息至结构体数组
						show_scoreboard();//显示具体排行情况
						n = 0;

						int j = 1;//控制排行榜界面return键
						while (j)
						{
							if (peekmessage(&msg, EM_MOUSE))
							{
								switch (msg.message)
								{
								case WM_LBUTTONDOWN:
									if (msg.x >= 600 && msg.x <= 710 && msg.y >= 420 && msg.y <= 460)
									{
										clear();
										j = 0;
										n = 1;
										break;
									}
								case WM_MOUSEMOVE:
									BeginBatchDraw();//防止文字因频繁绘制产生闪烁
									checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return键变色
									EndBatchDraw();
								}
							}
						}
						break;
					}
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 355 && msg.y <= 400)//游戏规则界面
					{
						cleardevice();//清屏

						settextcolor(WHITE);
						settextstyle(30, 15, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(40, 30, "游戏规则：");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 90, "开始游戏前，玩家需要先选择游戏难度等级，即时间限制长短；");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 130, "每次游戏开始时，系统会随机给出4个整数（1到10之间）：");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 170, "若给出的4个数能得出24，玩家需用加、减、乘、除（可加括号）输入能算出24的");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 210, "表达式，点击提交。(注意：每个数必须用一次且只能用一次，不涉及小数运算)");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 250, "若给出的4个数不能得出24，则输入NO，点击提交。");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 290, "若4个数能得出24，且表达式正确，则回答正确；");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 330, "若4个数不能得出24，且输入NO，也回答正确。");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 370, "反之则回答错误，回答错误和答题超时不得分，直接跳入下一题。");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 410, "若回答正确，系统会根据玩家所选难度等级计1次分。");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("宋体"));
						setbkmode(TRANSPARENT);
						outtextxy(26, 450, "（三次答题后本轮游戏结束，对每轮游戏累积计分进行排名）");
						checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return键变色
						n = 0;

						int k = 1;//控制游戏规则界面return键
						while (k)
						{
							if (peekmessage(&msg, EM_MOUSE))
							{
								switch (msg.message)
								{
								case WM_LBUTTONDOWN:
									if (msg.x >= 600 && msg.x <= 710 && msg.y >= 420 && msg.y <= 460)
									{
										clear();
										k = 0;
										n = 1;
										break;
									}
								case WM_MOUSEMOVE:
									BeginBatchDraw();
									checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return键变色
									EndBatchDraw();
								}
							}
						}
						break;
					}
					if (msg.x >= 50 && msg.x <= 170 && msg.y >= 400 && msg.y <= 440)//退出键
					{
						closegraph();// 关闭图形界面
						return 0;
					}
					if (msg.x >= 590 && msg.x <= 710 && msg.y >= 400 && msg.y <= 440)//进入游戏界面
					{
						if (difficultychoose == 0)//没选择难度等级就点击进入游戏
						{
							HWND a = GetHWnd();//获取窗口句柄
							isok = MessageBox(a, "请您先选择游戏难度等级！", "提醒：", MB_OK);//只带确认键的提示弹窗
							break;
						}
						else if (difficultychoose == 1)
						{
							n = 0;
							scoresum = 0;
							// 播放背景音乐
							mciSendString(_T("open main.mp3"), NULL, 0, NULL);//打开音乐
							mciSendString(_T("play main.mp3 repeat"), NULL, 0, NULL);//播放音乐并重复播放	
							//用户名输入框弹窗
							InputBox(name, 30, "昵称：（不能为空）", NULL, NULL, 250, 100);
							char round[5];

							char equation[1000];// 定义字符串缓冲区
							clearmore(-1, round, tex71, equation);//第一局游戏界面

							int l = 1;//控制游戏界面按键循环
							while (l)
							{
								if (peekmessage(&msg, EM_MOUSE))
								{
									switch (msg.message)
									{
									case WM_LBUTTONDOWN:
										if (msg.x >= 50 && msg.x <= 170 && msg.y >= 400 && msg.y <= 440)
										{
											closegraph();// 关闭图形界面
											return 0;
										}
										if (msg.x >= 590 && msg.x <= 710 && msg.y >= 400 && msg.y <= 440)
										{
											switch (play_game(equation, nums))
											{
											case 1:
												if (timesum == 5)
												{
													HWND c = GetHWnd();
													isok = MessageBox(c, "回答正确！+5分", "恭喜！", MB_OK);
													scoresum += 5;
												}
												else if (timesum == 3)
												{
													HWND c = GetHWnd();
													isok = MessageBox(c, "回答正确！+10分", "恭喜！", MB_OK);
													scoresum += 10;
												}
												else if (timesum == 1)
												{
													HWND c = GetHWnd();
													isok = MessageBox(c, "回答正确！+15分", "恭喜！", MB_OK);
													scoresum += 15;
												}
												break;
											case 0:
												HWND c = GetHWnd();
												isok = MessageBox(c, "回答/判断错误（或答题超时）+0分", "可惜", MB_OK);
												scoresum += 0;
												break;
											}

											if (o < 2)
											{
												clearmore(o, round, tex71, equation);
											}
											o++;
											if (o == 3)//一轮结束后计分界面
											{
												n = 0;
												p = 1;
												difficultychoose = 0;
												setbkcolor(0x3B0000);
												cleardevice();

												IMAGE test[2];//皇冠图
												loadimage(test + 0, "test1.jpg");
												loadimage(test + 1, "test2.jpg");
												putimage(218, 80, test + 0, SRCAND);
												putimage(218, 80, test + 1, SRCPAINT);

												settextcolor(WHITE);//显示分数
												settextstyle(80, 30, _T("Arial BLACK"));
												setbkmode(TRANSPARENT);
												outtextxy(240, 200, _T("Score："));
												char Scoresum[20];
												itoa(scoresum, Scoresum, 10);
												settextcolor(WHITE);
												settextstyle(80, 30, _T("Arial BLACK"));
												setbkmode(TRANSPARENT);
												outtextxy(440, 200, Scoresum);

												add_user(name);//收集的玩家名称及分数存至结构体
												update_scoreboard(players[num_users].username, players[num_users].score);//从结构体写入文件

												mciSendString(_T("close main.mp3"), NULL, 0, NULL);//停止播放音乐
												// 播放胜利音乐
												mciSendString(_T("open victory.mp3"), NULL, 0, NULL);//打开音乐
												mciSendString(_T("play victory.mp3"), NULL, 0, NULL);//播放音乐	
												o = 0;
												l = 0;

												while (p)//控制confirm键循环
												{
													if (peekmessage(&msg, EM_MOUSE))
													{
														switch (msg.message)
														{
														case WM_LBUTTONDOWN:
															if (msg.x >= 310 && msg.x <= 450 && msg.y >= 330 && msg.y <= 380)
															{
																mciSendString(_T("close victory.mp3"), NULL, 0, NULL);//停止播放胜利音乐
																cleardevice();
																p = 0;
																n = 1;
																clear();
																break;
															}
														case WM_MOUSEMOVE:
															BeginBatchDraw();
															checkMouseOver(msg.x, msg.y, btns1[7], 310, 330, 450, 380, tex81, 34, 15, 13, 7, "BLUE", "WHITE");
															EndBatchDraw();
															break;
														}
													}
												}
											}
										}
									case WM_MOUSEMOVE:
										FlushBatchDraw();
										checkMouseOver(msg.x, msg.y, btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "BLUE", "WHITE");
										checkMouseOver(msg.x, msg.y, btns1[6], 590, 400, 710, 440, tex71, 30, 10, 25, 5, "BLUE", "WHITE");
										break;
									}
								}
							}
						}
					}
				case WM_MOUSEMOVE:
					FlushBatchDraw();
					checkMouseOver(msg.x, msg.y, btns1[0], 293, 175, 467, 220, tex11, 33, 10, 5, 7, "BLUE", "WHITE");
					checkMouseOver(msg.x, msg.y, btns1[1], 293, 265, 467, 310, tex21, 33, 10, 30, 7, "BLUE", "WHITE");
					checkMouseOver(msg.x, msg.y, btns1[2], 293, 355, 467, 400, tex31, 33, 10, 34, 7, "BLUE", "WHITE");
					checkMouseOver(msg.x, msg.y, btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "BLUE", "WHITE");
					checkMouseOver(msg.x, msg.y, btns1[4], 590, 400, 710, 440, tex51, 30, 10, 6, 5, "BLUE", "WHITE");
					break;	//鼠标移动和鼠标悬停
				default:break;
				}
			}
		}
	} while (p == 0);

	_getch();//防止闪退
	closegraph();// 关闭图形界面
	return 0;
}