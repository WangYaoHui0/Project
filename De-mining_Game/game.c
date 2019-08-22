#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	//初始化棋盘
	memset(board, set, rows * cols * sizeof(board[0][0]));
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	//打印棋盘
	int i = 0;
	int j = 0;
	for (i = 0; i <= row; i++)
	{
		printf(" %d ", i);
		if (i != row)
		{
			printf("|");
		}
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		for (j = 0; j <= col; j++)
		{
			if (j != col)
			{
				printf("---|");
			}
			else
			{
				printf("---\n");
			}
		}
		printf(" %d |", i);
		for (j = 1; j <= col; j++)
		{
			if (j != col)
			{
				printf(" %c |", board[i][j]);
			}
			else
			{
				printf(" %c ", board[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void SetMine(char board[ROWS][COLS], int row, int col, int count)
{
	//布置雷
	int i = 0;
	int j = 0;
	while (count)
	{
		i = rand() % row + 1;
		j = rand() % col + 1;
		if (board[i][j] == '0')
		{
			board[i][j] = '1';
			count--;
		}
	}
}

int GetMineCount(char mine[ROWS][COLS], int i, int j)
{
	//获取该位置周围雷的个数
	return (mine[i - 1][j - 1] + mine[i - 1][j] + mine[i - 1][j + 1] +
		    mine[i][j - 1] + mine[i][j + 1] +
		    mine[i + 1][j - 1] + mine[i + 1][j] + mine[i + 1][j + 1]) - 8 * '0';
}

void SpreadBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j)
{
	//将棋盘拓展开，周围无雷置为空格，周围有雷显示雷的个数
	if (GetMineCount(mine, i, j) == 0)
	{
		show[i][j] = ' ';
		if ((i - 1) > 0 && (j - 1) > 0 && show[i - 1][j - 1] == '*')
		{
			SpreadBoard(mine, show, i - 1, j - 1);
		}
		if ((i - 1) > 0 && show[i - 1][j] == '*')
		{
			SpreadBoard(mine, show, i - 1, j);
		}
		if ((i - 1) > 0 && (j + 1) <= COL && show[i - 1][j + 1] == '*')
		{
			SpreadBoard(mine, show, i - 1, j + 1);
		}
		if ((j - 1) > 0 && show[i][j - 1] == '*')
		{
			SpreadBoard(mine, show, i, j - 1);
		}
		if ((j + 1) <= COL && show[i][j + 1] == '*')
		{
			SpreadBoard(mine, show, i, j + 1);
		}
		if ((i + 1) <= ROW && (j - 1) > 0 && show[i + 1][j - 1] == '*')
		{
			SpreadBoard(mine, show, i + 1, j - 1);
		}
		if ((i + 1) <= ROW && show[i + 1][j] == '*')
		{
			SpreadBoard(mine, show, i + 1, j);
		}
		if ((i + 1) <= ROW && (j + 1) <= COL && show[i + 1][j + 1] == '*')
		{
			SpreadBoard(mine, show, i + 1, j + 1);
		}
	}
	else
	{
		show[i][j] = GetMineCount(mine, i, j) + '0';
	}
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int count)
{
	int tmp = 0;

	while (1)
	{
		int i = 0;
		int j = 0;
		int num = 0;

		printf("请输入要排查的坐标：>");
		scanf("%d%d", &i, &j);
		if (i >= 1 && i <= row && j >= 1 && j <= col)
		{
			if (show[i][j] == '*')
			{
				if (tmp == 0 && mine[i][j] == '1')//保证第一次不被炸死
				{
					mine[i][j] = '0';
					SetMine(mine, ROW, COL, 1);
					tmp = 1;
				}
				else if (tmp != 0 && mine[i][j] == '1')
				{
					printf("很遗憾，扫雷失败！\n");
					printf("雷阵分布如下：>\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else
				{
					tmp = 1;
				}
				SpreadBoard(mine, show, i, j);
				system("cls");//清屏
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("这个位置已经排查过了！\n");
			}
		}
		else
		{
			printf("输入错误！\n");
		}
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (show[i][j] == '*')
				{
					num++;
				}
			}
		}
		if (num == count)
		{
			printf("恭喜您，扫雷成功！\n");
			break;
		}
	}
}