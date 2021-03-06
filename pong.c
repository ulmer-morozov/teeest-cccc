// Copyright 2022 Gastropub Gabriel

#include <stdio.h>

// размеры экрана
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// высота ракетки
#define RACKET_HEIGHT 3

// нужный счет для победы
#define SCORE_COUNT_FOR_WIN 21

// глобальные переменные

int gameOver = 0;

// нажатая клавиша
char pressedKey;

// счёт игроков
int scoreLeft = 0;
int scoreRight = 0;

// координаты мяча
int ballX;
int ballY;

// скорость мяча
int ballSpeedX;
int ballSpeedY;

// позиции ракеток
int racketLeftY;
int racketRightY;

void draw_field() {
  // строчки
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    // заполняем строку символами слева направо
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      int isBall = x == ballX && y == ballY;

      if (isBall) {
        printf("O");
        continue;
      }

      int isLeftRacket =
          x == 0 && y >= racketLeftY && y < racketLeftY + RACKET_HEIGHT;

      int isRightRacket = x == SCREEN_WIDTH - 1 && y >= racketRightY &&
                          y < racketRightY + RACKET_HEIGHT;

      if (isLeftRacket || isRightRacket) {
        printf("@");
        continue;
      }

      int isFirstOrLastRow = y == 0 || y == SCREEN_HEIGHT - 1;

      if (isFirstOrLastRow) {
        printf("#");
        continue;
      }

      int isFirstOrLastColumn = x == 0 || x == SCREEN_WIDTH - 1;

      if (isFirstOrLastColumn) {
        printf("|");
        continue;
      }

      printf(" ");
    }

    printf("\n");
  }

  // информация о счёте и кнопках
  printf("score left: %d    score right: %d               %c\n", scoreLeft,
         scoreRight, pressedKey);
  printf(
      "------------------------------------------------------------------------"
      "--------\n");
  printf("q – exit    a/z – left player   k/m – right player\n");
}

void move_ball() {
  ballX = ballX + ballSpeedX;
  ballY = ballY + ballSpeedY;
}

void move_rackets() {
  // чтобы левая ракетка не убегала вверх
  if (pressedKey == 'a' && racketLeftY > 1) {
    racketLeftY--;
  }

  // чтобы правая ракетка не убегала вниз
  if (pressedKey == 'z' && racketLeftY < SCREEN_HEIGHT - RACKET_HEIGHT - 1) {
    racketLeftY++;
  }

  // чтобы правая ракетка не убегала вверх
  if (pressedKey == 'k' && racketRightY > 1) {
    racketRightY--;
  }

  // чтобы правая ракетка не убегала вниз
  if (pressedKey == 'm' && racketRightY < SCREEN_HEIGHT - RACKET_HEIGHT - 1) {
    racketRightY++;
  }
}

void ricochet_top_bottom() {
  int ballBelowBottom = ballY >= SCREEN_HEIGHT - 2;

  if (ballBelowBottom) {
    ballSpeedY = -1;
  }

  int ballAboveTop = ballY <= 1;

  if (ballAboveTop) {
    ballSpeedY = +1;
  }
}

void ricochet_racket() {
  int isRightRacket = ballX == SCREEN_WIDTH - 2 && ballY >= racketRightY &&
                      ballY < racketRightY + RACKET_HEIGHT;

  if (isRightRacket) {
    ballSpeedX = -1;
  }

  int isLeftRacket =
      ballX == 1 && ballY >= racketLeftY && ballY < racketLeftY + RACKET_HEIGHT;

  if (isLeftRacket) {
    ballSpeedX = +1;
  }
}

void end_game() { gameOver = 1; }

void nextRound() {
  if (scoreLeft >= SCORE_COUNT_FOR_WIN) {
    draw_field();

    printf("Congratulations LEFT (!!!)\n");

    end_game();
  } else if (scoreRight >= SCORE_COUNT_FOR_WIN) {
    draw_field();

    printf("Congratulations RIGHT (!!!)\n");

    end_game();
  } else {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;

    ballSpeedX = 1;
    ballSpeedY = 1;

    racketLeftY = SCREEN_HEIGHT / 2 - 1;
    racketRightY = SCREEN_HEIGHT / 2 - 1;
  }
}

void check_win() {
  int leftPlayerWin = ballX == SCREEN_WIDTH - 1;

  if (leftPlayerWin) {
    scoreLeft++;

    nextRound();
  }

  int rightPlayerWin = ballX == 0;

  if (rightPlayerWin) {
    scoreRight++;

    nextRound();
  }
}

int main() {
  nextRound();

  // первая отрисовка экрана
  draw_field();

  while (gameOver == 0) {
    scanf("%c", &pressedKey);

    if (pressedKey == 'q') {
      break;
    }

    // enter просто игнорируем
    if (pressedKey == '\n') {
      continue;
    }

    int keyIsValid = pressedKey == 'a' || pressedKey == 'z' ||
                     pressedKey == 'm' || pressedKey == 'k' ||
                     pressedKey == ' ';

    if (!keyIsValid) {
      printf("Enter q or a or z or m or k or SPACE\n");
      continue;
    }

    move_ball();
    move_rackets();

    ricochet_top_bottom();
    ricochet_racket();

    check_win();

    if (!gameOver) {
      draw_field();
    }
  }

  printf("Выход из программы\nПока!\n");
  return 0;
}
