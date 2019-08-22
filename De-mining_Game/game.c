#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	//��ʼ������
	memset(board, set, rows * cols * sizeof(board[0][0]));
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	//��ӡ����
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
	//������
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
	//��ȡ��λ����Χ�׵ĸ���
	return (mine[i - 1][j - 1] + mine[i - 1][j] + mine[i - 1][j + 1] +
		    mine[i][j - 1] + mine[i][j + 1] +
		    mine[i + 1][j - 1] + mine[i + 1][j] + mine[i + 1][j + 1]) - 8 * '0';
}

void SpreadBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j)
{
	//��������չ������Χ������Ϊ�ո���Χ������ʾ�׵ĸ���
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

		printf("������Ҫ�Ų�����꣺>");
		scanf("%d%d", &i, &j);
		if (i >= 1 && i <= row && j >= 1 && j <= col)
		{
			if (show[i][j] == '*')
			{
				if (tmp == 0 && mine[i][j] == '1')//��֤��һ�β���ը��
				{
					mine[i][j] = '0';
					SetMine(mine, ROW, COL, 1);
					tmp = 1;
				}
				else if (tmp != 0 && mine[i][j] == '1')
				{
					printf("���ź���ɨ��ʧ�ܣ�\n");
					printf("����ֲ����£�>\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else
				{
					tmp = 1;
				}
				SpreadBoard(mine, show, i, j);
				system("cls");//����
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("���λ���Ѿ��Ų���ˣ�\n");
			}
		}
		else
		{
			printf("�������\n");
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
			printf("��ϲ����ɨ�׳ɹ���\n");
			break;
		}
	}
}