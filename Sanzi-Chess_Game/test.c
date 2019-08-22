#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

int n = 0;

void menu()
{
	printf("**************************\n");
	printf("***** 1.play  0.exit *****\n");
	printf("**************************\n");
}

void game()
{
	char board[ROW][COL] = { 0 };
	Init_board(board, ROW, COL);
	Display_board(board, ROW, COL);
	Play_game(board, ROW, COL);
}

void test()
{
	srand((unsigned int)time(NULL));
	int input = 0;

	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("������������Ϸ���������嵽n���壩�������ּ��ɣ�>");
			scanf("%d", &n);
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