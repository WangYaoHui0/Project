#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

extern int n;

//初始化棋盘
void Init_board(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	memset(board, ' ', row * col * sizeof(board[0][0]));
}

//打印当前棋盘
void Display_board(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (j < col - 1)
			{
				printf(" %c |", board[i][j]);
			}
			else
			{
				printf(" %c \n", board[i][j]);
			}
		}
		if (i < row - 1) 
		{
			for (j = 0; j < col; j++)
			{
				if (j < col - 1)
				{
					printf("---|");
				}
				else
				{
					printf("---\n");
				}
			}
		}
	}
}

//判断输赢
char Iswin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	char tmp = 0;
	int num = 0;
	int m = 0;

	//判断行
	for (i = 0; i < row; i++)
	{
		num = 1;
		tmp = board[i][0];
		for (j = 1; j < col; j++)
		{
			if (tmp == board[i][j] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[i][j];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
	}
	//判断列
	for (j = 0; j < col; j++)
	{
		num = 1;
		tmp = board[0][j];
		for (i = 1; i < row; i++)
		{
			if (tmp == board[i][j] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[i][j];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
	}

	//判断下半部分\对角线
	m = 0;
	while (m <= row - n)
	{
		tmp = board[m][0];
		num = 1;
		for (i = m + 1; i < row; i++)
		{
			if (tmp == board[i][i - m] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[i][i - m];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
		m++;
	}
	//判断上半部分\对角线
	m = 1;
	while (m <= col - n)
	{
		tmp = board[0][m];
		num = 1;
		for (j = m + 1; j < col; j++)
		{
			if (tmp == board[j - m][j] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[j - m][j];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
		m++;
	}

	//判断下半部分/对角线
	m = 0;
	while (m <= row - n)
	{
		tmp = board[m][row - 1];
		num = 1;
		for (i = m + 1; i < row; i++)
		{
			if (tmp == board[i][col - 1 - i + m] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[i][col - 1 - i + m];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
		m++;
	}

	//判断上半部分/对角线
	m = col - 2;
	while (m >= n - 1)
	{
		tmp = board[0][m];
		num = 1;
		for (j = m - 1; j >= 0; j--)
		{
			if (tmp == board[m - j][j] && tmp != ' ')
			{
				num++;
			}
			else
			{
				tmp = board[m - j][j];
				num = 1;
			}
			if (num == n)
			{
				return tmp;
			}
		}
		m--;
	}

	return -1;
}

void Play_game(char board[ROW][COL], int row, int col)
{
	int r1 = 0;
	int c1 = 0;
	int r2 = 0;
	int c2 = 0;
	int count = 0;
	char ret = 0;

	while (1)
	{
		if (n == 3)
		{
			printf("玩家1下：>(1-%d)", n);
			scanf("%d%d", &r1, &c1);
			if (r1 > n || c1 > n || board[r1 - 1][c1 - 1] != ' ')
			{
				printf("输入错误！\n");
				continue;
			}
			if (board[r1 - 1][c1 - 1] == ' ')
			{
				board[r1 - 1][c1 - 1] = 'X';
			}
		}
		else
		{
			printf("玩家1下:>(1-%d)", row);
			scanf("%d%d", &r1, &c1);
			if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
			{
				printf("输入错误！\n");
				continue;
			}
			if (board[r1 - 1][c1 - 1] == ' ')
			{
				board[r1 - 1][c1 - 1] = 'X';
			}
		}
		//printf("玩家下:>(1-%d)", row);
		//scanf("%d%d", &r1, &c1);
		//if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
		//{
		//	printf("输入错误！\n");
		//	continue;
		//}
		//if (board[r1 - 1][c1 - 1] == ' ')
		//{
		//	board[r1 - 1][c1 - 1] = 'X';
		//}
		Display_board(board, ROW, COL);
		count++;
		ret = Iswin(board, ROW, COL);
		if (ret == 'X')
		{
			printf("玩家1赢！\n");
			break;
		}

		if (count == ((row * col + 1) / 2))
		{
			printf("平局！\n");
			break;
		}

		if (n == 3)
		{
			I:
			printf("玩家2下：>(1-%d)", n);
			scanf("%d%d", &r2, &c2);
			if (r2 > n || c2 > n || board[r2 - 1][c2 - 1] != ' ')
			{
				printf("输入错误！\n");
				goto I;
			}
			if (board[r2 - 1][c2 - 1] == ' ')
			{
				board[r2 - 1][c2 - 1] = 'O';
			}
		}
		else
		{
			printf("玩家2下:>(1-%d)", row);
			scanf("%d%d", &r2, &c2);
			if (r2 > row || c2 > col || board[r2 - 1][c2 - 1] != ' ')
			{
				printf("输入错误！\n");
				continue;
			}
			if (board[r2 - 1][c2 - 1] == ' ')
			{
				board[r2 - 1][c2 - 1] = 'O';
			}
		}
		//printf("玩家下:>(1-%d)", row);
		//scanf("%d%d", &r1, &c1);
		//if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
		//{
		//	printf("输入错误！\n");
		//	continue;
		//}
		//if (board[r1 - 1][c1 - 1] == ' ')
		//{
		//	board[r1 - 1][c1 - 1] = 'X';
		//}
		Display_board(board, ROW, COL);
		//count++;
		ret = Iswin(board, ROW, COL);
		if (ret == 'O')
		{
			printf("玩家2赢！\n");
			break;
		}


		//if (n == 3)
		//{
		//	printf("电脑下:>");
		//T:
		//	r2 = rand() % n + 1;
		//	c2 = rand() % n + 1;
		//	if (board[r2 - 1][c2 - 1] == ' ' && r2 != 0 && c2 != 0)
		//	{
		//		board[r2 - 1][c2 - 1] = 'O';
		//	}
		//	else
		//	{
		//		goto T;
		//	}
		//}
		//else
		//{
		//	printf("电脑下:>");
		//Y:
		//	r2 = rand() % (row + 1);
		//	c2 = rand() % (col + 1);
		//	if (board[r2 - 1][c2 - 1] == ' ' && r2 != 0 && c2 != 0)
		//	{
		//		board[r2 - 1][c2 - 1] = 'O';
		//	}
		//	else
		//	{
		//		goto Y;
		//	}
		//}
		////printf("电脑下:>");
		////T:
		////r2 = rand() % (row + 1);
		////c2 = rand() % (col + 1);
		////if (board[r2 - 1][c2 - 1] == ' ' && r2 != 0 && c2 != 0)
		////{
		////	board[r2 - 1][c2 - 1] = 'O';
		////}
		////else
		////{
		////	goto T;
		////}
		//printf("%d %d \n", r2, c2);
		//Display_board(board, ROW, COL);
		//ret = Iswin(board, ROW, COL);
		//if (ret == 'O')
		//{
		//	printf("电脑赢！\n");
		//	break;
		//}
	}
}