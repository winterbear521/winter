#define _CRT_SECURE_NO_WARNINGS

#include"game.h"
void menu()
{
	printf("*****************************\n");
	printf("******   1.play  0.exit******\n");
	printf("*****************************\n");
}
void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	//³õÊ¼»¯ÆåÅÌµÄº¯Êı
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//ÏÂÆå
	while (1)
	{
		
		PlayerMove(board, ROW, COL);
		//ÅĞ¶ÏÊäÓ®
		ret = IsWin(board, ROW, COL);
		//ÅĞ¶ÏÊäÓ®
		if (ret != 'C')
		{
			break;
		}

		DisplayBoard(board, ROW, COL);

		ComputerMove(board, ROW, COL);
		//ÅĞ¶ÏÊäÓ®
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);


	}
	if (ret == '*')
	{
		printf("Íæ¼ÒÓ®\n");

	}
	else if (ret == '#')
	{
		printf("µçÄÔÓ®\n");

	}
	else
	{
		printf("Æ½¾Ö\n");
	}
	DisplayBoard(board, ROW, COL);
}
int main()
{
	srand((unsigned)time(NULL));
	int input = 0;
	do
	{
		menu();//´òÓ¡²Ëµ¥
		printf("ÇëÑ¡Ôñ:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("ÍË³öÓÎÏ·");
			break;
		default:
			printf("Ñ¡Ôñ´íÎó\n");
			break;

		}


	} while(input);
	return 0;

}