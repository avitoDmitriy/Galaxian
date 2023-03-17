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


#define height 25
#define width 65
char map[height][width+1];
Trocket rocket;
Tbullet bul;

void moveBul(int x, int y)
{
	bul.x = x;
	bul.y = y;
}

void initBul()
{
	moveBul(2,2);
}

void putBul()
{
	map[bul.x][bul.y] = '*';
}

void initRocket() //составляющие ракеты, инициализация 
{
	rocket.l = 1;
	rocket.w = 1;
	rocket.x = (width - rocket.l) / 2;
	rocket.y = height - 1;
}

void putRocket()  //размещение ракеты 
{
	for (int j = rocket.y; j < rocket.y + rocket.l; j++)
		map[j][rocket.x] = char(207);
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
		map[0][i] = char(178);
	map[0][width] = '\0';
	
	strncpy(map[1], map[0], width + 1);
	for (int i = 1; i < width - 1; i++)
		map[1][i] = ' ';

	for (int i = 2; i < height; i++)
	{
		strncpy(map[i], map[1], width+1);
	}
}

void moveRocket(int x)//ДВИЖЕНИЕ РАКЕТЫ
{
	rocket.x = x;
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
	system("mode con cols=90 lines=26");
	initRocket();
	initBul();

	do
	{
		setcur(0, 0);

		init();
		putRocket();
		putBul();
		show();
		if (GetKeyState('A') < 0) moveRocket(rocket.x - 1);
		if (GetKeyState('D') < 0) moveRocket(rocket.x + 1);
		//moveBul(rocket.x, rocket.y - 1);
		Sleep(30);
	} while (GetKeyState(VK_ESCAPE) >= 0);


	return 0;
}