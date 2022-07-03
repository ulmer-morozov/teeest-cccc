#include <stdio.h>
// #include <stdlib.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20

// глобальные переменные

// координаты мяча
int ballX = 5;
int ballY = 10;

// скорость мяча
int ballSpeedX = 1;
int ballSpeedY = 1;

void draw_field()
{
    // строчки
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        // заполняем строку символами слева направо
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int isBall = x == ballX && y == ballY;

            if (isBall)
            {
                printf("O");
                continue;
            }

            int isFirstOrLastRow = y == 0 || y == SCREEN_HEIGHT - 1;

            if (isFirstOrLastRow)
            {
                printf("#");
                continue;
            }

            int isFirstOrLastColumn = x == 0 || x == SCREEN_WIDTH - 1;

            if (isFirstOrLastColumn)
            {
                printf("|");
                continue;
            }

            printf(".");
        }

        printf("\n");
    }
}

void top_bottom_ricochet()
{
    int ballBelowBottom = ballY >= SCREEN_HEIGHT - 1;

    if (ballBelowBottom)
    {
        ballSpeedY = -1;
    }

    int ballAboveTop = ballY <= 0;

    if (ballAboveTop)
    {
        ballSpeedY = +1;
    }
}

void main()
{
    char pressedKey;

    while (pressedKey != 'q')
    {
        draw_field();

        pressedKey = getchar();

        ballX = ballX + ballSpeedX;
        ballY = ballY + ballSpeedY;

        top_bottom_ricochet();
    }

    printf("Выход из программы\nПока!\n");
}