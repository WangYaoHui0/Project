#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu_1()
{
	printf("******************************\n");
	printf("****    1.play   0.exit   ****\n");
	printf("******************************\n");
}

void menu_2()
{
	printf("******************************\n");
	printf("****** 1. easy(%d个雷) *******\n", EASY_COUNT);
	printf("****** 2. hard(%d个雷) *******\n", HARD_COUNT);
	printf("******************************\n");
}

void game()
{
	int choice = 0;
	int count = 0;   //雷数
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	menu_2();
	printf("请选择游戏难度：>");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		count = EASY_COUNT;
		SetMine(mine, ROW, COL, count);
		DisplayBoard(show, ROW, COL);
		FindMine(mine, show, ROW, COL, count);
		break;
	case 2:
		count = HARD_COUNT;
		SetMine(mine, ROW, COL, count);
		DisplayBoard(show, ROW, COL);
		FindMine(mine, show, ROW, COL, count);
		break;
	default:
		printf("选择错误，请重新开始游戏！\n");
		break;
	}
}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu_1();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出成功！\n");
			break;
		default:
			printf("选择错误！\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	system("pause");
	return 0;
}