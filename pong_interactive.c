#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

int movePaddle1(char key, int p1_y);
int movePaddle2(char key, int p2_y);
int ballWallCollision(int ball_dy, int ball_y);
int ballPaddleCollision(int ball_dx, int ball_x, int ball_y, int p_x, int p_y);
void drawField(int score1, int score2, int ball_x, int ball_y, int p1_x, int p1_y, int p2_x,
               int p2_y);

void initGameTerminal() {
    initscr();
    cbreak();  // Передача символов сразу, минуя буфер строки
    noecho();  // Не отображать нажимаемые пользователем клавиши
    curs_set(0);
    timeout(150);
}

void closeGameTerminal() { endwin(); }

int main() {
    const int WIN_SCORE = 21;
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int ball_dx = 1, ball_dy = 1;
    int p1_y = HEIGHT / 2, p2_y = HEIGHT / 2;
    int p1_x = 2, p2_x = 77;
    int score1 = 0, score2 = 0;
    int key = 0;

    initGameTerminal();

    while (score1 < WIN_SCORE && score2 < WIN_SCORE && key != 'q' && key != 'Q') {
        drawField(score1, score2, ball_x, ball_y, p1_x, p1_y, p2_x, p2_y);

        ball_x += ball_dx;
        ball_y += ball_dy;

        if (ball_x <= 0) {
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            p1_y = HEIGHT / 2;
            p2_y = HEIGHT / 2;
            score2 += 1;
            ball_dx = -ball_dx;
        } else if (ball_x >= WIDTH - 1) {
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

        key = getch();

        p1_y = movePaddle1(key, p1_y);
        p2_y = movePaddle2(key, p2_y);
    }

    closeGameTerminal();

    if (score1 >= WIN_SCORE)
        printf("Игрок 1 победил!\n");
    else if (score2 >= WIN_SCORE)
        printf("Игрок 2 победил!\n");

    return 0;
}

int ballPaddleCollision(int ball_dx, int ball_x, int ball_y, int p_x, int p_y) {
    if (ball_x == p_x && (ball_y == p_y || ball_y == p_y - 1 || ball_y == p_y + 1)) {
        ball_dx = -ball_dx;
    }
    return ball_dx;
}

int movePaddle1(char key, int p1_y) {
    if ((key == 'A' || key == 'a') && p1_y > 2) {
        return p1_y - 1;
    }
    if ((key == 'Z' || key == 'z') && p1_y < HEIGHT - 2) {
        return p1_y + 1;
    }
    return p1_y;
}

int movePaddle2(char key, int p2_y) {
    if ((key == 'K' || key == 'k') && p2_y > 2) {
        return p2_y - 1;
    }
    if ((key == 'M' || key == 'm') && p2_y < HEIGHT - 3) {
        return p2_y + 1;
    }
    return p2_y;
}

int ballWallCollision(int ball_dy, int ball_y) {
    if (ball_y == 1 || ball_y == HEIGHT - 2) {
        ball_dy = -ball_dy;
    }
    return ball_dy;
}

void drawField(int score1, int score2, int ball_x, int ball_y, int p1_x, int p1_y, int p2_x,
               int p2_y) {
    erase();

    for (int x = 0; x < WIDTH; x++) {
        mvaddch(0, x, '=');
        mvaddch(HEIGHT - 1, x, '=');
    }
    for (int y = 1; y < HEIGHT - 1; y++) {
        mvaddch(y, WIDTH / 2, '|');
    }

    mvprintw(5, 30, "%d", score1);
    mvprintw(5, 50, "%d", score2);

    for (int i = -1; i <= 1; i++) {
        mvaddch(p1_y + i, p1_x, '|');
        mvaddch(p2_y + i, p2_x, '|');
    }

    mvaddch(ball_y, ball_x, 'o');

    refresh();
}