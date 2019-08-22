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
	printf("****** 1. easy(%d����) *******\n", EASY_COUNT);
	printf("****** 2. hard(%d����) *******\n", HARD_COUNT);
	printf("******************************\n");
}

void game()
{
	int choice = 0;
	int count = 0;   //����
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	menu_2();
	printf("��ѡ����Ϸ�Ѷȣ�>");
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
		printf("ѡ����������¿�ʼ��Ϸ��\n");
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
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳��ɹ���\n");
			break;
		default:
			printf("ѡ�����\n");
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