
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
