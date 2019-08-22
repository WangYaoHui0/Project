#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define EASY_COUNT 10
#define HARD_COUNT 30

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
void SetMine(char board[ROWS][COLS], int row, int col, int count);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int count);

#endif //__GAME_H__ 