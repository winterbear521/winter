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
	//��ʼ�����̵ĺ���
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//����
	while (1)
	{
		
		PlayerMove(board, ROW, COL);
		//�ж���Ӯ
		ret = IsWin(board, ROW, COL);
		//�ж���Ӯ
		if (ret != 'C')
		{
			break;
		}

		DisplayBoard(board, ROW, COL);

		ComputerMove(board, ROW, COL);
		//�ж���Ӯ
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);


	}
	if (ret == '*')
	{
		printf("���Ӯ\n");

	}
	else if (ret == '#')
	{
		printf("����Ӯ\n");

	}
	else
	{
		printf("ƽ��\n");
	}
	DisplayBoard(board, ROW, COL);
}
int main()
{
	srand((unsigned)time(NULL));
	int input = 0;
	do
	{
		menu();//��ӡ�˵�
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ");
			break;
		default:
			printf("ѡ�����\n");
			break;

		}


	} while(input);
	return 0;

}