#include <stdio.h>
#include <stdlib.h> // чтобы не надо было нажимать enter

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20
#define RACKET_HEIGHT 3

// глобальные переменные

// нажатая клавиша
char pressedKey;

// координаты мяча
int ballX = 30;
int ballY = 10;

// скорость мяча
int ballSpeedX = -1;
int ballSpeedY = 1;

// позиции ракеток
int racketLeftY = SCREEN_HEIGHT / 2 + 1;
int racketRightY = SCREEN_HEIGHT / 2 - 2 + 2;

void write_help()
{
    printf("q – exit    a/z – left player   k/m – right player\n");
}

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

            int isLeftRacket = x == 0 && y >= racketLeftY && y < racketLeftY + RACKET_HEIGHT;

            int isRightRacket = x == SCREEN_WIDTH - 1 && y >= racketRightY && y < racketRightY + RACKET_HEIGHT;

            if (isLeftRacket || isRightRacket)
            {
                printf("@");
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

void move_ball()
{
    ballX = ballX + ballSpeedX;
    ballY = ballY + ballSpeedY;
}

void move_rackets()
{
    // чтобы левая ракетка не убегала вверх
    if (pressedKey == 'a' && racketLeftY > 1)
    {
        racketLeftY--;
    }

    // чтобы правая ракетка не убегала вниз
    if (pressedKey == 'z' && racketLeftY < SCREEN_HEIGHT - RACKET_HEIGHT - 1)
    {
        racketLeftY++;
    }

    // чтобы правая ракетка не убегала вверх
    if (pressedKey == 'k' && racketRightY > 1)
    {
        racketRightY--;
    }

    // чтобы правая ракетка не убегала вниз
    if (pressedKey == 'm' && racketRightY < SCREEN_HEIGHT - RACKET_HEIGHT - 1)
    {
        racketRightY++;
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

void racket_ricochet()
{
    int isRightRacket = ballX == SCREEN_WIDTH - 2 && ballY >= racketRightY && ballY < racketRightY + RACKET_HEIGHT;

    if (isRightRacket)
    {
        ballSpeedX = -1;
    }

    int isLeftRacket = ballX == 1 && ballY >= racketLeftY && ballY < racketLeftY + RACKET_HEIGHT;

    if (isLeftRacket)
    {
        ballSpeedX = +1;
    }
}

void main()
{
    while (pressedKey != 'q')
    {
        write_help();
        draw_field();

        system("stty raw"); // отменяет enter
        pressedKey = getchar();
        system("stty cooked"); // возвращает enter

        move_ball();

        move_rackets();

        top_bottom_ricochet();

        racket_ricochet();
    }

    printf("Выход из программы\nПока!\n");
}
