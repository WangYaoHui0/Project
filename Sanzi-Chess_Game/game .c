#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

extern int n;

//��ʼ������
void Init_board(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	memset(board, ' ', row * col * sizeof(board[0][0]));
}

//��ӡ��ǰ����
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

//�ж���Ӯ
char Iswin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	char tmp = 0;
	int num = 0;
	int m = 0;

	//�ж���
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
	//�ж���
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

	//�ж��°벿��\�Խ���
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
	//�ж��ϰ벿��\�Խ���
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

	//�ж��°벿��/�Խ���
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

	//�ж��ϰ벿��/�Խ���
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
			printf("���1�£�>(1-%d)", n);
			scanf("%d%d", &r1, &c1);
			if (r1 > n || c1 > n || board[r1 - 1][c1 - 1] != ' ')
			{
				printf("�������\n");
				continue;
			}
			if (board[r1 - 1][c1 - 1] == ' ')
			{
				board[r1 - 1][c1 - 1] = 'X';
			}
		}
		else
		{
			printf("���1��:>(1-%d)", row);
			scanf("%d%d", &r1, &c1);
			if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
			{
				printf("�������\n");
				continue;
			}
			if (board[r1 - 1][c1 - 1] == ' ')
			{
				board[r1 - 1][c1 - 1] = 'X';
			}
		}
		//printf("�����:>(1-%d)", row);
		//scanf("%d%d", &r1, &c1);
		//if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
		//{
		//	printf("�������\n");
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
			printf("���1Ӯ��\n");
			break;
		}

		if (count == ((row * col + 1) / 2))
		{
			printf("ƽ�֣�\n");
			break;
		}

		if (n == 3)
		{
			I:
			printf("���2�£�>(1-%d)", n);
			scanf("%d%d", &r2, &c2);
			if (r2 > n || c2 > n || board[r2 - 1][c2 - 1] != ' ')
			{
				printf("�������\n");
				goto I;
			}
			if (board[r2 - 1][c2 - 1] == ' ')
			{
				board[r2 - 1][c2 - 1] = 'O';
			}
		}
		else
		{
			printf("���2��:>(1-%d)", row);
			scanf("%d%d", &r2, &c2);
			if (r2 > row || c2 > col || board[r2 - 1][c2 - 1] != ' ')
			{
				printf("�������\n");
				continue;
			}
			if (board[r2 - 1][c2 - 1] == ' ')
			{
				board[r2 - 1][c2 - 1] = 'O';
			}
		}
		//printf("�����:>(1-%d)", row);
		//scanf("%d%d", &r1, &c1);
		//if (r1 > row || c1 > col || board[r1 - 1][c1 - 1] != ' ')
		//{
		//	printf("�������\n");
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
			printf("���2Ӯ��\n");
			break;
		}


		//if (n == 3)
		//{
		//	printf("������:>");
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
		//	printf("������:>");
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
		////printf("������:>");
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
		//	printf("����Ӯ��\n");
		//	break;
		//}
	}
}