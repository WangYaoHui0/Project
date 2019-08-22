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
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("您想玩哪种游戏？（三子棋到n字棋）输入数字即可：>");
			scanf("%d", &n);
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