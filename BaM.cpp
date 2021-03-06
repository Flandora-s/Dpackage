// BaM.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>


#define WINDOW_WIDTH 874
#define WINDOW_HEIGHT 591
#define SIZE 20
#define BANANA_DROP 4
#define MONKEY_SPEED 15


IMAGE background, banana, banana_mask, monkey_left_1, monkey_mask_left, monkey_right_1, monkey_mask_right, monkey_left_2, monkey_right_2;

int memory[2][SIZE] = { -1 };
int direction1 = 1;
int direction2 = 0;
int monkey_x_1 = 173;
int monkey_x_2 = 700;
int a1, a2;
int t = 120;



void Begin()
{
	putimage(0, 0, &background);
	settextcolor(RGB(0, 255, 0));
	setbkmode(TRANSPARENT);
	settextstyle(56, 0, _T("Ink Free"));
	outtextxy(150, 240, _T("z:The Game Begin"));
	settextstyle(56, 0, _T("Ink Free"));
	outtextxy(150, 310, _T("c:The Game Sign Out"));
	char sm = _getch();
	switch (sm)
	{
	case 'z':
		break;
	case 'c':
		Sleep(100);
		exit(-1);
	}
}


void StartUp() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&background, _T("background.jpg"));
	loadimage(&banana, _T("banana.jpg"));
	loadimage(&banana_mask, _T("banana_mask.jpg"));
	loadimage(&monkey_left_1, _T("monkey_left_1.bmp"));
	loadimage(&monkey_mask_left, _T("monkey_mask_left.bmp"));
	loadimage(&monkey_right_1, _T("monkey_right_1.bmp"));
	loadimage(&monkey_mask_right, _T("monkey_mask_right.bmp"));
	loadimage(&monkey_left_2, _T("monkey_left_2.bmp"));
	loadimage(&monkey_right_2, _T("monkey_right_2.bmp"));
	Begin();
	BeginBatchDraw();
}

/*
int Random() {
srand(time(NULL));
return rand() % 50;
}
*/

int Random() {
	int m = 50;
	int n = 90;
	int temp = rand() / (n - m + 1) + m;
	return temp;
}

void BananaPosition() {
	for (int i = 0; i < SIZE; i++) {
		if (memory[1][i] >= WINDOW_HEIGHT) {
			memory[1][i] = -1;
			memory[0][i] = -1;
		}
		else if (memory[0][i] == -1) {
			continue;
		}
		else {
			memory[1][i] += BANANA_DROP;
		}

	}
}

void UpdateWithoutInput() {
	BananaPosition();
}

void UpdateWithInput() {
	char temp;
	if (_kbhit()) {
		temp = _getch();
		if (temp == 'a') {
			monkey_x_1 -= MONKEY_SPEED;
			direction1 = 1;
		}
		if (temp == 'd') {
			monkey_x_1 += MONKEY_SPEED;
			direction1 = 0;
		}
		if (temp == 'j') {
			monkey_x_2 -= MONKEY_SPEED;
			direction2 = 1;
		}
		if (temp == 'l') {
			monkey_x_2 += MONKEY_SPEED;
			direction2 = 0;
		}
	}
}

void SoManyBananas() {
	for (int i = 0; i < SIZE; i++) {
		if (memory[0][i] == -1) {
			continue;
		}
		else
		{
			int temp_x = memory[0][i];
			int temp_y = memory[1][i];
			int a, b, c, d;
			a = (monkey_x_1 - temp_x)*(monkey_x_1 - temp_x);
			b = (WINDOW_HEIGHT - 50 - temp_y)*(WINDOW_HEIGHT - 50 - temp_y);
			c = (monkey_x_2 - temp_x)*(monkey_x_2 - temp_x);
			d = (WINDOW_HEIGHT - 50 - temp_y)*(WINDOW_HEIGHT - 50 - temp_y);
			if (a + b <= 1600)
			{
				settextstyle(56, 0, _T("Ink Free"));
				outtextxy(140, 90, _T("+1"));
				memory[0][i] = -1;
				a1 += 1;
			}
			else if (c + d <= 1600)
			{
				settextstyle(56, 0, _T("Ink Free"));
				outtextxy(650, 90, _T("+1"));
				memory[0][i] = -1;
				a2 += 1;
			}
			else
			{
				putimage(temp_x, temp_y, &banana_mask, NOTSRCERASE);
				putimage(temp_x, temp_y, &banana, SRCINVERT);
			}

		}
	}
}



void MonkeySetPlayer() {
	int monkey_x1 = monkey_x_1;
	int monkey_x2 = monkey_x_2;
	int monkey_y = WINDOW_HEIGHT - 100;
	if (direction1 == 1) {
		putimage(monkey_x1, monkey_y, &monkey_mask_left, NOTSRCERASE);
		putimage(monkey_x1, monkey_y, &monkey_left_1, SRCERASE);
	}
	else if (direction1 == 0) {
		putimage(monkey_x1, monkey_y, &monkey_mask_right, NOTSRCERASE);
		putimage(monkey_x1, monkey_y, &monkey_right_1, SRCERASE);
	}
	else {
		putimage(monkey_x1, monkey_y, &monkey_mask_right, NOTSRCERASE);
		putimage(monkey_x1, monkey_y, &monkey_right_1, SRCERASE);
	}


	if (direction2 == 1) {
		putimage(monkey_x2, monkey_y, &monkey_mask_left, NOTSRCERASE);
		putimage(monkey_x2, monkey_y, &monkey_left_2, SRCERASE);
	}
	else if (direction2 == 0) {
		putimage(monkey_x2, monkey_y, &monkey_mask_right, NOTSRCERASE);
		putimage(monkey_x2, monkey_y, &monkey_right_2, SRCERASE);
	}
	else {
		putimage(monkey_x2, monkey_y, &monkey_mask_right, NOTSRCERASE);
		putimage(monkey_x2, monkey_y, &monkey_right_2, SRCERASE);
	}
}

void Show(int u)
{

	putimage(0, 0, &background);
	int a = t - u;
	TCHAR r[5];
	settextcolor(RGB(255, 153, 0));
	setbkmode(TRANSPARENT);
	settextstyle(66, 0, _T("Ink Free"));
	_stprintf_s(r, _T("%d"), a);
	outtextxy(400, 40, r);
	TCHAR s[5];
	settextcolor(RGB(255, 153, 238));
	setbkmode(TRANSPARENT);
	settextstyle(56, 0, _T("Ink Free"));
	_stprintf_s(s, _T("%d"), a1);
	outtextxy(85, 80, s);
	TCHAR s1[5];
	settextcolor(RGB(255, 153, 238));
	setbkmode(TRANSPARENT);
	settextstyle(56, 0, _T("Ink Free"));
	_stprintf_s(s1, _T("%d"), a2);
	outtextxy(760, 80, s1);
	SoManyBananas();
	MonkeySetPlayer();
	FlushBatchDraw();
	Sleep(50);
}



void GameOver() {
	if (a1 > a2)
	{
		settextcolor(RGB(255, 153, 238));
		setbkmode(TRANSPARENT);
		settextstyle(56, 0, _T("Ink Free"));
		outtextxy(300, 260, _T("红猴子赢"));
	}
	if (a1 < a2)
	{
		settextcolor(RGB(255, 153, 238));
		setbkmode(TRANSPARENT);
		settextstyle(56, 0, _T("Ink Free"));
		outtextxy(300, 260, _T("蓝猴子赢 "));
	}
	if (a1 == a2)
	{
		settextcolor(RGB(255, 153, 238));
		setbkmode(TRANSPARENT);
		settextstyle(56, 0, _T("Ink Free"));
		outtextxy(300, 260, _T("平局"));
	}
	EndBatchDraw();
}


int main() {
	int number = 0;
	int temp = 1;
	int u = 0;

	StartUp();
	time_t start, end;
	start = time(NULL);
	while (1) {
		Show(u);
		temp++;
		if (temp % 10 == 0) {
			memory[1][number] = 0;
			memory[0][number] = Random();
			number++;
		}
		UpdateWithoutInput();
		if (number >= SIZE) {
			number = 0;
		}
		UpdateWithInput();
		end = time(NULL);
		u = (int)difftime(end, start);
		//		Time_BAN(u);
		if (u >= 60)
			break;
	}
	GameOver();
	Sleep(500);
	_getch();
	return 0;
}




/*
int main() {
while (1) {
printf("%d\n", Random());
Sleep(600);
}
return 0;
}
*/