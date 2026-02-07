
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_LENGTH 800

typedef enum { STOP = 0, LEFT, RIGHT, UP, DOWN } Direction;

typedef struct {
    int x[MAX_LENGTH];
    int y[MAX_LENGTH];
    int length;
    Direction dir;
} Snake;

typedef struct {
    int x, y;
} Food;

typedef struct {
    Snake snake;
    Food food;
    int score;
    int gameOver;
    int speed;
} Game;


struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\033[?25h"); // Show cursor
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?25l"); // Hide cursor
}

int kbhit() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void setColor(int color) {
    printf("\033[%dm", color);
}

void initGame(Game *game) {
    game->snake.length = 3;
    game->snake.dir = RIGHT;

    for (int i = 0; i < game->snake.length; i++) {
        game->snake.x[i] = WIDTH / 2 - i;
        game->snake.y[i] = HEIGHT / 2;
    }

    srand(time(NULL));
    game->food.x = rand() % (WIDTH - 2) + 1;
    game->food.y = rand() % (HEIGHT - 2) + 1;
    
    game->score = 0;
    game->gameOver = 0;
    game->speed = 100;
}

void drawBorder() {
    setColor(36); // Cyan
    for (int i = 0; i < WIDTH; i++) {
        gotoxy(i, 0);
        printf("═");
        gotoxy(i, HEIGHT - 1);
        printf("═");
    }
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(0, i);
        printf("║");
        gotoxy(WIDTH - 1, i);
        printf("║");
    }
    gotoxy(0, 0); printf("╔");
    gotoxy(WIDTH - 1, 0); printf("╗");
    gotoxy(0, HEIGHT - 1); printf("╚");
    gotoxy(WIDTH - 1, HEIGHT - 1); printf("╝");
}

void clearScreen() {
    printf("\033[2J");
    printf("\033[H");
}
