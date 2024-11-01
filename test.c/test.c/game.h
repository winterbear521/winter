#pragma once
#include <stdio.h>
#define ROW 3
#define COL 3
#include<stdlib.h>
#include<time.h>
//初始化棋盘
void InitBoard(char board[ROW][COL],int row,int col);
//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);
//玩家下棋
void playerMove(char board[ROW][COL], int row, int col);
//电脑下棋
//找没有下棋的随机下棋
void CoputerMove(char board[ROW][COL], int row, int col);
//玩家赢-'*'
//电脑-’#’
//平局-’Q’
//继续-’c’
char IsWin(char board[ROW][COL],int row,int col);