#include <stdio.h>
#include <math.h>//�Ӽ��˳�����
#include <time.h>//���������
#include <stdlib.h>//������ת�ַ���
#include <graphics.h>// ����EasyX��ͼ��ͷ�ļ�
#include <conio.h>//ʹ��_getch()
#include <string.h>//�����û���
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"Winmm.lib")// ���ؾ�̬��

using namespace std;

//��ť������
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
	btn.y2 = y2;//���ö�������
	if (bcolor == "GREEN")setfillcolor(GREEN);
	else if (bcolor == "BLUE")setfillcolor(BLUE);
	else if (bcolor == "WHITE")setfillcolor(WHITE);
	fillroundrect(btn.x1, btn.y1, btn.x2, btn.y2, 10, 8);//���ư�ť�߿�
	//���ð�ť����:
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	if (tcolor == "WHITE")settextcolor(WHITE);
	else if (tcolor == "BLACK")settextcolor(BLACK);//����������ɫ
	settextstyle(tlength, twidth, _T("Arial BLACK"));//���������ʽ
	outtextxy(x1 + tsetoff1, y1 + tsetoff2, text);//������ʾλ��
}

//���������ť��ɫ������
bool isMouseOver; // ��ʾ����Ƿ��ڰ�ť�Ϸ�
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

// ���������Ƿ��ڰ�ť��
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

//1-10���������:
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
	ShowButton(btn[0], 105, 125, 205, 275, text1, 130, 40, (32 - textwidth(text1) / 2), (26 - textheight(text1) / 2), "WHITE", "BLACK");//δ֪������λ����ʾλ�ò��ܾ���
	ShowButton(btn[1], 255, 125, 355, 275, text2, 130, 40, (50 - textwidth(text2) / 2), (75 - textheight(text2) / 2), "WHITE", "BLACK");
	ShowButton(btn[2], 405, 125, 505, 275, text3, 130, 40, (50 - textwidth(text3) / 2), (75 - textheight(text3) / 2), "WHITE", "BLACK");
	ShowButton(btn[3], 555, 125, 655, 275, text4, 130, 40, (50 - textwidth(text4) / 2), (75 - textheight(text4) / 2), "WHITE", "BLACK");
}

//����ʱ����:
int timesum;
void timecount(int timesum)
{
	int seconds = timesum * 60; //����ת��Ϊ��
	int minutes, seconds_remaining;
	char countdown_str[100];
	char countdown_array[305][100];
	int i = seconds, j = 0;
	while ((checkClick(590, 400, 710, 440) != 1) && (i > 0))
	{
		minutes = i / 60;
		seconds_remaining = i % 60;
		sprintf(countdown_str, "%02d:%02d", minutes, seconds_remaining); // ������ʱ��ʽ��Ϊ�ַ���
		strcpy(countdown_array[j], countdown_str); // ������ʱ�ַ�����ֵ���ַ�������
		settextcolor(WHITE);
		settextstyle(40, 15, _T("Arial BLACK"));
		setbkmode(TRANSPARENT);
		outtextxy(200, 44, countdown_array[j]);
		Sleep(1000); // �ȴ�1�루Sleep�����Ժ���Ϊ��λ��
		setfillcolor(0x3B0000);
		solidroundrect(180, 40, 300, 90, 10, 8);//������ǰ�ĵ���ʱ��ʵ��ˢ��
		i--;
		j++;
	}
}

Button btns1[8] = { 0 }; //��ʼ����ť�ṹ������
char tex11[1000] = _T("Difficulty Setting");
char tex21[1000] = _T("Ranking list");
char tex31[1000] = _T("Game Rule");
char tex41[1000] = _T("Exit Game");
char tex51[1000] = _T("Load Game");
char tex61[1000] = _T("Return");
char tex71[1000] = _T("Submit");
char tex81[1000] = _T("Confirm");

//��������һ�֣�
void clearmore(int o, char round[], char text6[], char equation[])
{
	cleardevice();
	setfillcolor(0x3B0000);
	solidroundrect(650, 48, 673, 80, 10, 8);//���Ǿִ�����ʵ��ˢ��
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(50, 50, _T("Countdown:"));//����ʱ��ʾ��
	itoa(o + 2, round, 10);
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(580, 50, _T("Round:     / 3"));//���ֽ��д���
	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(658, 50, round);

	num();//�������

	settextcolor(WHITE);
	settextstyle(30, 10, _T("Arial BLACK"));
	setbkmode(TRANSPARENT);
	outtextxy(220, 308, _T("Available operator :  +  -  x  /  (  )"));//���÷���
	ShowButton(btns1[3], 50, 400, 170, 440, tex41, 30, 10, 10, 5, "GREEN", "WHITE");//�˳���
	ShowButton(btns1[6], 590, 400, 710, 440, tex71, 30, 10, 25, 5, "GREEN", "WHITE");//�ύ��

	setfillcolor(WHITE);
	fillroundrect(230, 370, 530, 400, 10, 8);//���������

	//��ʽ����򵯴���
	InputBox(equation, 1000, "��ʽ��", NULL, NULL, 250, 100);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(27, 9, _T("Arial BLACK"));
	outtextxy(244, 371, "Equation��");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 12, _T("Arial"));
	outtextxy(350, 373, equation);//��ӡ��ʽ
	timecount(timesum);//����ʱ
}

//��������ҳ�溯��:
void clear()
{
	cleardevice();//�����Ļ

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

//24���жϣ�
// ���������ջ�Ľṹ��
typedef struct {
	double data[100];
	int top;
} Stack;

// ��ʼ��ջ
void initStack(Stack* s) {
	s->top = -1;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Stack* s) {
	return s->top == -1;
}

// ��ջ
void push(Stack* s, double value) {
	s->top++;
	s->data[s->top] = value;
}

// ��ջ
double pop(Stack* s) {
	double value = s->data[s->top];
	s->top--;
	return value;
}

// ��ȡջ��Ԫ��
double peek(Stack* s) {
	return s->data[s->top];
}

// ��������������ʽ��ֵ
double calculate(char* expression) {
	Stack numStack; // ����ջ
	Stack opStack;  // ������ջ
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

// �ж��Ƿ��ܵó�24��
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

// �ж�������
int play_game(char equation[], int nums[])
{
	if (strcmp(equation, "NO") == 0)
	{
		if (calculate_24(nums))
		{
			return 0; // ����ܵõ�24��������NO������Ҳ��÷�
		}
		else
		{
			return 1; // ����޷��õ�24��������NO������ҵ÷�
		}
	}
	else if (strcmp(equation, "") == 0)//����Ϊ��Ҳ���÷�
		return 0;
	else
	{
		int result;
		result = calculate(equation); // ������ı��ʽת��Ϊ����
		if (result == 24 && calculate_24(nums))
		{
			return 1; // �������ı��ʽֵΪ24���ܵõ�24������ҵ÷�
		}
		else
		{
			return 0; // ���򲻵÷�
		}
	}
}

// ���а�: 
typedef struct //�û��������ֽṹ������
{
	char username[50];
	char score[5];
} User;
User  players[1000];
int num_users = 0;
char name[30];
int scoresum = 0;

void add_user(char* n)//���ռ����������Ϣ¼��ṹ������
{
	strcpy(players[num_users].username, n);
	itoa(scoresum, players[num_users].score, 10);
	num_users++;
}

void update_scoreboard(char playername[], char score[])// �����Ϣд��txt��
{
	FILE* fp = fopen("24game usersdata.txt", "a");
	fprintf(fp, "%s %s\n", players[num_users].username, players[num_users].score);
	fclose(fp);
}

void read()// ���´�txt�ж�ȡ�����Ϣ��������
{
	FILE* fp = fopen("24game usersdata.txt", "r");
	int num_players = 0;
	while (fscanf(fp, "%s %s", players[num_players].username, players[num_players].score) == 2)
	{
		num_players++;
	}
	fclose(fp);
}

// �ȽϺ������������򣨰��÷ִӸߵ��ͣ�
int compare_scores(const void* a, const void* b)
{
	return ((User*)b)->score - ((User*)a)->score;
}

//������ʾ���ְ�
void show_scoreboard()
{
	// ���÷�����
	qsort(players, num_users, sizeof(User), compare_scores);

	// ��ʾ��������
	setfillcolor(0x3B0000);
	solidroundrect(250, 150, 600, 400, 10, 8);//������ǰ������
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
	initgraph(760, 500);// ������ͼ���ڣ���С760x500
	setbkcolor(0x3B0000);//���ñ�����ɫ
	cleardevice();//ˢ�±�����ɫ
	HWND b = GetHWnd();//��ȡ���ھ��
	SetWindowText(b, "24��С��Ϸ");//���Ĵ��ڱ���

	int p = 1;//����������Ϸѭ��
	do
	{
		p = 1;
		//��ʼ���棺
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

		int n = 1;//����������ѭ��
		int o = 0;//����һ��������Ϸѭ��
		int difficultychoose = 0;//�����Ѷ�ѡ�����ѭ��
		ExMessage msg; //������Ϣָ��
		while (n)
		{
			if (peekmessage(&msg, EM_MOUSE))
			{
				switch (msg.message)
				{
				case WM_LBUTTONDOWN://��������
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 175 && msg.y <= 220)//�Ѷ�ѡ�����
					{
						cleardevice();//�����Ļ

						settextcolor(WHITE);
						settextstyle(80, 30, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(260, 55, _T("Make 24"));
						settextcolor(WHITE);
						settextstyle(20, 10, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(252, 465, _T("@Copyright NJUPTB230302"));
						n = 0;

						HWND b = GetHWnd();//��ȡ���ھ��
						int m = 1;//�����Ѷ�ѡ�����İ���ѭ��
						while (m)
						{
							if (peekmessage(&msg, EM_MOUSE))
							{
								switch (msg.message)
								{
								case WM_LBUTTONDOWN:
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 160 && msg.y <= 200)
									{
										isok = MessageBox(b, "���ѳɹ�ѡ����Ϸ�Ѷȵȼ���", "��ʾ��", MB_OK);
										difficultychoose = 1;
										timesum = 5;
										clear();//�س�ʼ����
										m = 0;
										n = 1;
										break;
									}
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 260 && msg.y <= 300)
									{
										isok = MessageBox(b, "���ѳɹ�ѡ����Ϸ�Ѷȵȼ���", "��ʾ��", MB_OK);
										difficultychoose = 1;
										timesum = 3;
										clear();//�س�ʼ����
										m = 0;
										n = 1;
										break;
									}
									if (msg.x >= 200 && msg.x <= 560 && msg.y >= 360 && msg.y <= 400)
									{
										isok = MessageBox(b, "���ѳɹ�ѡ����Ϸ�Ѷȵȼ���", "��ʾ��", MB_OK);
										difficultychoose = 1;
										timesum = 1;
										clear();//�س�ʼ����
										m = 0;
										n = 1;
										break;
									}
								case WM_MOUSEMOVE://����ƶ���������ɫ
									Button btns2[3] = { 0 }; //��ʼ����ť�ṹ������
									char tex12[1000] = _T("Easy��5 minutes��5points��");
									char tex22[1000] = _T("Normal��3 minutes��10points��");
									char tex32[1000] = _T("Hard��1 minutes��15points��");
									FlushBatchDraw();//��ֹ������Ƶ�����Ʋ�����˸
									checkMouseOver(msg.x, msg.y, btns2[0], 200, 160, 560, 200, tex12, 33, 10, 55, 4, "BLUE", "WHITE");
									checkMouseOver(msg.x, msg.y, btns2[1], 200, 260, 560, 300, tex22, 33, 10, 35, 4, "BLUE", "WHITE");
									checkMouseOver(msg.x, msg.y, btns2[2], 200, 360, 560, 400, tex32, 33, 10, 52, 4, "BLUE", "WHITE");
								}
							}
						}
						break;
					}
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 265 && msg.y <= 310)//���а����
					{
						cleardevice();//����

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
						outtextxy(170, 150, _T("1��"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 200, _T("2��"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 250, _T("3��"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 300, _T("4��"));
						settextcolor(WHITE);
						settextstyle(40, 13, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(170, 350, _T("5��"));
						settextcolor(WHITE);
						settextstyle(20, 10, _T("Arial BLACK"));
						setbkmode(TRANSPARENT);
						outtextxy(252, 465, _T("@Copyright NJUPTB230302"));

						read();//��ȡ�����Ϣ���ṹ������
						show_scoreboard();//��ʾ�����������
						n = 0;

						int j = 1;//�������а����return��
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
									BeginBatchDraw();//��ֹ������Ƶ�����Ʋ�����˸
									checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return����ɫ
									EndBatchDraw();
								}
							}
						}
						break;
					}
					if (msg.x >= 293 && msg.x <= 467 && msg.y >= 355 && msg.y <= 400)//��Ϸ�������
					{
						cleardevice();//����

						settextcolor(WHITE);
						settextstyle(30, 15, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(40, 30, "��Ϸ����");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 90, "��ʼ��Ϸǰ�������Ҫ��ѡ����Ϸ�Ѷȵȼ�����ʱ�����Ƴ��̣�");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 130, "ÿ����Ϸ��ʼʱ��ϵͳ���������4��������1��10֮�䣩��");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 170, "��������4�����ܵó�24��������üӡ������ˡ������ɼ����ţ����������24��");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 210, "���ʽ������ύ��(ע�⣺ÿ����������һ����ֻ����һ�Σ����漰С������)");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 250, "��������4�������ܵó�24��������NO������ύ��");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 290, "��4�����ܵó�24���ұ��ʽ��ȷ����ش���ȷ��");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 330, "��4�������ܵó�24��������NO��Ҳ�ش���ȷ��");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 370, "��֮��ش���󣬻ش����ʹ��ⳬʱ���÷֣�ֱ��������һ�⡣");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(30, 410, "���ش���ȷ��ϵͳ����������ѡ�Ѷȵȼ���1�η֡�");
						settextcolor(WHITE);
						settextstyle(20, 10, _T("����"));
						setbkmode(TRANSPARENT);
						outtextxy(26, 450, "�����δ��������Ϸ��������ÿ����Ϸ�ۻ��Ʒֽ���������");
						checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return����ɫ
						n = 0;

						int k = 1;//������Ϸ�������return��
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
									checkMouseOver(msg.x, msg.y, btns1[5], 600, 420, 710, 460, tex61, 30, 10, 22, 5, "BLUE", "WHITE");//return����ɫ
									EndBatchDraw();
								}
							}
						}
						break;
					}
					if (msg.x >= 50 && msg.x <= 170 && msg.y >= 400 && msg.y <= 440)//�˳���
					{
						closegraph();// �ر�ͼ�ν���
						return 0;
					}
					if (msg.x >= 590 && msg.x <= 710 && msg.y >= 400 && msg.y <= 440)//������Ϸ����
					{
						if (difficultychoose == 0)//ûѡ���Ѷȵȼ��͵��������Ϸ
						{
							HWND a = GetHWnd();//��ȡ���ھ��
							isok = MessageBox(a, "������ѡ����Ϸ�Ѷȵȼ���", "���ѣ�", MB_OK);//ֻ��ȷ�ϼ�����ʾ����
							break;
						}
						else if (difficultychoose == 1)
						{
							n = 0;
							scoresum = 0;
							// ���ű�������
							mciSendString(_T("open main.mp3"), NULL, 0, NULL);//������
							mciSendString(_T("play main.mp3 repeat"), NULL, 0, NULL);//�������ֲ��ظ�����	
							//�û�������򵯴�
							InputBox(name, 30, "�ǳƣ�������Ϊ�գ�", NULL, NULL, 250, 100);
							char round[5];

							char equation[1000];// �����ַ���������
							clearmore(-1, round, tex71, equation);//��һ����Ϸ����

							int l = 1;//������Ϸ���水��ѭ��
							while (l)
							{
								if (peekmessage(&msg, EM_MOUSE))
								{
									switch (msg.message)
									{
									case WM_LBUTTONDOWN:
										if (msg.x >= 50 && msg.x <= 170 && msg.y >= 400 && msg.y <= 440)
										{
											closegraph();// �ر�ͼ�ν���
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
													isok = MessageBox(c, "�ش���ȷ��+5��", "��ϲ��", MB_OK);
													scoresum += 5;
												}
												else if (timesum == 3)
												{
													HWND c = GetHWnd();
													isok = MessageBox(c, "�ش���ȷ��+10��", "��ϲ��", MB_OK);
													scoresum += 10;
												}
												else if (timesum == 1)
												{
													HWND c = GetHWnd();
													isok = MessageBox(c, "�ش���ȷ��+15��", "��ϲ��", MB_OK);
													scoresum += 15;
												}
												break;
											case 0:
												HWND c = GetHWnd();
												isok = MessageBox(c, "�ش�/�жϴ��󣨻���ⳬʱ��+0��", "��ϧ", MB_OK);
												scoresum += 0;
												break;
											}

											if (o < 2)
											{
												clearmore(o, round, tex71, equation);
											}
											o++;
											if (o == 3)//һ�ֽ�����Ʒֽ���
											{
												n = 0;
												p = 1;
												difficultychoose = 0;
												setbkcolor(0x3B0000);
												cleardevice();

												IMAGE test[2];//�ʹ�ͼ
												loadimage(test + 0, "test1.jpg");
												loadimage(test + 1, "test2.jpg");
												putimage(218, 80, test + 0, SRCAND);
												putimage(218, 80, test + 1, SRCPAINT);

												settextcolor(WHITE);//��ʾ����
												settextstyle(80, 30, _T("Arial BLACK"));
												setbkmode(TRANSPARENT);
												outtextxy(240, 200, _T("Score��"));
												char Scoresum[20];
												itoa(scoresum, Scoresum, 10);
												settextcolor(WHITE);
												settextstyle(80, 30, _T("Arial BLACK"));
												setbkmode(TRANSPARENT);
												outtextxy(440, 200, Scoresum);

												add_user(name);//�ռ���������Ƽ����������ṹ��
												update_scoreboard(players[num_users].username, players[num_users].score);//�ӽṹ��д���ļ�

												mciSendString(_T("close main.mp3"), NULL, 0, NULL);//ֹͣ��������
												// ����ʤ������
												mciSendString(_T("open victory.mp3"), NULL, 0, NULL);//������
												mciSendString(_T("play victory.mp3"), NULL, 0, NULL);//��������	
												o = 0;
												l = 0;

												while (p)//����confirm��ѭ��
												{
													if (peekmessage(&msg, EM_MOUSE))
													{
														switch (msg.message)
														{
														case WM_LBUTTONDOWN:
															if (msg.x >= 310 && msg.x <= 450 && msg.y >= 330 && msg.y <= 380)
															{
																mciSendString(_T("close victory.mp3"), NULL, 0, NULL);//ֹͣ����ʤ������
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
					break;	//����ƶ��������ͣ
				default:break;
				}
			}
		}
	} while (p == 0);

	_getch();//��ֹ����
	closegraph();// �ر�ͼ�ν���
	return 0;
}