#pragma once
#include <stdio.h>
#define ROW 3
#define COL 3
#include<stdlib.h>
#include<time.h>
//��ʼ������
void InitBoard(char board[ROW][COL],int row,int col);
//��ӡ����
void DisplayBoard(char board[ROW][COL], int row, int col);
//�������
void playerMove(char board[ROW][COL], int row, int col);
//��������
//��û��������������
void CoputerMove(char board[ROW][COL], int row, int col);
//���Ӯ-'*'
//����-��#��
//ƽ��-��Q��
//����-��c��
char IsWin(char board[ROW][COL],int row,int col);