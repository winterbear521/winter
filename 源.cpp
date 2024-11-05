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
        printf("请猜数字: ");
        scanf("%d", &guess);
        if (guess < ret)
        {
            printf("猜小了\n");
        }
        else if (guess > ret)
        {
            printf("猜大了\n");
        }
        else
        {
            printf("恭喜你，猜对了\n");
            break; // 退出循环
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
        printf("请选择：");
        scanf("%d", &input);
        switch (input)
        {
        case 1: // 添加空格
            game();
            break;
        case 0: // 添加空格
            printf("退出游戏\n");
            break;
        default:
            printf("选择错误,请重新选择\n");
            break;
        }
    } while (input != 0); // 循环直到用户选择退出
    return 0;
}
