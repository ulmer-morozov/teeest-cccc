#include <stdio.h>
// #include <stdlib.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20

void drawField(int ballPosX, int ballPosY)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int isBall = x == ballPosX && y == ballPosY;

            if (isBall)
            {
                printf("O");
                continue;
            }

            int isFirstOrLastRow = y == 0 || y == SCREEN_HEIGHT - 1;
            int isFirstOrLastColumn = x == 0 || x == SCREEN_WIDTH - 1;

            if (isFirstOrLastRow || isFirstOrLastColumn)
            {
                printf("#");
                continue;
            }

            printf(".");
        }

        printf("\n");
    }
}

void main()
{
    int wantToPlay = 1;

    int ballX = 16;
    int ballY = 8;

    while (wantToPlay == 1)
    {
        scanf("%d", &wantToPlay);

        drawField(ballX, ballY);

        ballX++;
        ballY++;
    }
}
