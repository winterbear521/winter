#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void game()
{
    int guess = 0;
    int ret = rand() % 100 + 1;
    while (1)
    {
        printf("�������: ");
        scanf("%d", &guess);
        if (guess < ret)
        {
            printf("��С��\n");
        }
        else if (guess > ret)
        {
            printf("�´���\n");
        }
        else
        {
            printf("��ϲ�㣬�¶���\n");
            break; // �˳�ѭ��
        }
    }
}

void menu()
{
    printf("************************\n");
    printf("******* 1.play *********\n");
    printf("******* 0.exit *********\n");
    printf("************************\n");
}

int main()
{

    srand((unsigned int)time(NULL));
    int input = 0;
    do
    {
        menu();
        printf("��ѡ��");
        scanf("%d", &input);
        switch (input)
        {
        case 1: // ��ӿո�
            game();
            break;
        case 0: // ��ӿո�
            printf("�˳���Ϸ\n");
            break;
        default:
            printf("ѡ�����,������ѡ��\n");
            break;
        }
    } while (input != 0); // ѭ��ֱ���û�ѡ���˳�
    return 0;
}
