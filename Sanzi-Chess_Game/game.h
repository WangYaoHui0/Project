#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROW 10
#define COL 10

void Init_board(char board[ROW][COL], int row, int col);
void Display_board(char board[ROW][COL], int row, int col);
void Play_game(char board[ROW][COL], int row, int col);
char Iswin(char board[ROW][COL], int row, int col);

#endif //__GAME_H__