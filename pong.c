#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

int movePaddle1(char key, int p1_y);
int movePaddle2(char key, int p2_y);
int ballPaddleCollision(int ball_dx, int ball_x, int ball_y, int p_x, int p_y);
int ballWallCollision(int ball_dy, int ball_y);
int drawField(int sc1, int sc2, int ball_x, int ball_y, int p1_x, int p1_y, int p2_x, int p2_y);

int main() {
    const int WIN_SCORE = 21;
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int ball_dx = 1, ball_dy = 1;
    int p1_y = HEIGHT / 2, p2_y = HEIGHT / 2;
    int p1_x = 2, p2_x = 77;
    int score1 = 0, score2 = 0;
    char key;

    printf("\033[2J\033[25I");  // очистка экрана и скрытие курсора
    fflush(stdout);             // немедленное отправление в консоль
    drawField(score1, score2, ball_x, ball_y, p1_x, p1_y, p2_x, p2_y);

    while (score1 < WIN_SCORE && score2 < WIN_SCORE && key != 'q') {
        key = getchar();
        if (key == 'A' || key == 'a' || key == 'Z' || key == 'z' || key == 'm' || key == 'k' ||
            key == '\x20') {
            p1_y = movePaddle1(key, p1_y);
            p2_y = movePaddle2(key, p2_y);

            ball_x += ball_dx;
            ball_y += ball_dy;

            if (ball_x == 0) {
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                p1_y = HEIGHT / 2;
                p2_y = HEIGHT / 2;
                score2 += 1;
                ball_dx = -ball_dx;
            } else if (ball_x == WIDTH - 1) {
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                p1_y = HEIGHT / 2;
                p2_y = HEIGHT / 2;
                score1 += 1;
                ball_dx = -ball_dx;
            }

            ball_dy = ballWallCollision(ball_dy, ball_y);

            ball_dx = ballPaddleCollision(ball_dx, ball_x, ball_y, p1_x + 1, p1_y);
            ball_dx = ballPaddleCollision(ball_dx, ball_x, ball_y, p2_x - 1, p2_y);

            drawField(score1, score2, ball_x, ball_y, p1_x, p1_y, p2_x, p2_y);
        }
    }

    if (score1 >= WIN_SCORE)
        printf("Игрок 1 победил!\n");
    else if (score2 >= WIN_SCORE)
        printf("Игрок 2 победил!\n");
}

int ballWallCollision(int ball_dy, int ball_y) {
    if (ball_y == 1 || ball_y == HEIGHT - 2) {
        ball_dy = -ball_dy;
    }
    return ball_dy;
}

int ballPaddleCollision(int ball_dx, int ball_x, int ball_y, int p_x, int p_y) {
    if (ball_x == p_x && (ball_y == p_y || ball_y == p_y - 1 || ball_y == p_y + 1)) {
        ball_dx = -ball_dx;
    }
    return ball_dx;
}

int movePaddle1(char key, int p1_y) {
    if ((key == 'A' || key == 'a') && p1_y > 2) {
        p1_y--;
    }
    if ((key == 'Z' || key == 'z') && p1_y < HEIGHT - 2) {
        p1_y++;
    }
    return p1_y;
}

int movePaddle2(char key, int p2_y) {
    if ((key == 'K' || key == 'k') && p2_y > 2) {
        p2_y--;
    }
    if ((key == 'M' || key == 'm') && p2_y < HEIGHT - 3) {
        p2_y++;
    }
    return p2_y;
}

int drawField(int sc1, int sc2, int ball_x, int ball_y, int p1_x, int p1_y, int p2_x, int p2_y) {
    printf("\033[H");  // ресет курсора
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == ball_x && y == ball_y) {
                printf("o");
            } else if (x == 30 && y == 5) {
                printf("%2d", sc1);
                x++;
            } else if (x == 50 && y == 5) {
                printf("%2d", sc2);
                x++;
            } else if (x == p1_x && (y == p1_y || y == p1_y - 1 || y == p1_y + 1)) {
                printf("|");
            } else if (x == p2_x && (y == p2_y || y == p2_y - 1 || y == p2_y + 1)) {
                printf("|");
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("=");
            } else if (x == WIDTH / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    fflush(stdout);
    return 0;
}