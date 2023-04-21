#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct
{
	int x;
	int y;
}Tbullet;

typedef struct //структура для ракеты 
{
	int x;
	int y;
	int l;
	int w;
}Trocket;


#define height 26
#define width 65
#define left 1
#define right 0
#define stop 2
char map[height][width+1];
Trocket rocket;
Tbullet bul;
int l = stop;

void initRocket() //составляющие ракеты, инициализация 
{
	rocket.l = 1;
	rocket.w = 1;
	rocket.x = (width - rocket.l) / 2;
	rocket.y = height - 1;
}

void moveBul()
{
	if (map[bul.y - 1][bul.x] == '#' || map[bul.y - 1][bul.x] == '@')
	{
		bul.y = height;
		
	}
	else
	{
		bul.y--;
	}
}

void putBul()
{	
	map[bul.y][bul.x] = '*';
}

void initBul(int x, int y)
{
	bul.x = x;
	bul.y = y;
}

void putRocket()  //размещение ракеты 
{
	for (int j = rocket.y; j < rocket.y + rocket.l; j++)
		map[j][rocket.x] = 207;
}

void setcur(int x, int y) //перемещение курсора в начало (0,0)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void init() //инициализация поля 
{
	for (int i = 0; i < width; i++)
		map[0][i] = '#';
	map[0][width] = '\0';
	
	strncpy(map[1], map[0], width + 1);
	for (int i = 1; i < width - 1; i++)
		map[1][i] = ' ';

	for (int i = 2; i < height; i++)
	{
		strncpy(map[i], map[1], width+1);
	}
	for (int i = 5; i < 40; i++)
		map[10][i] = '@';
}

void moveRocket(int l)
{
	if(l == right)
		rocket.x += 1;
	if(l == left)
		rocket.x -= 1;
	if (l == stop)
		rocket.x = rocket.x;
	if (rocket.x < 1)
		rocket.x = 1;
	if (rocket.x + rocket.w >= width)
		rocket.x = width - 1 - rocket.w;
}


void show()  //функция отображения 
{
	for (int i = 0; i < height; i++)
	{
		printf("%s\n", map[i]);
	}
}

int main(void)
{
	system("mode con cols=90 lines=27");
	boolean run = 0;
	initRocket();
	do
	{
		l = stop;
		setcur(0, 0);

		if (run)
		{
			initBul(bul.x, bul.y);
			moveBul();
		}
		if (bul.y >= height)
			run = 0;
		

		show();
		init();
		putRocket();
		putBul();
		if (GetKeyState('A') < 0) { l = left; }
		if (GetKeyState('D') < 0) { l = right; }
		moveRocket(l);
		if (GetKeyState('W') < 0) { run = 1; bul.x = rocket.x; bul.y = rocket.y; }
		Sleep(50);
	} while (GetKeyState(VK_ESCAPE) >= 0);

	return 0;
}

