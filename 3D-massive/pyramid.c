#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 35

float angle = 0;

typedef struct {
    float x, y, z;
} Point3D;

typedef struct {
    int x, y;
} Point2D;

Point2D project(Point3D p) {
    float scale = 200 / (200 + p.z);
    Point2D result;
    result.x = (int)(WIDTH / 2 + p.x * scale);
    result.y = (int)(HEIGHT / 2 - p.y * scale);
    return result;
}

Point3D rotate(Point3D p, float angleX, float angleY) {
    Point3D result;
    
    // Rotate around Y axis
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float x1 = p.x * cosY - p.z * sinY;
    float z1 = p.x * sinY + p.z * cosY;
    
    // Rotate around X axis
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float y1 = p.y * cosX - z1 * sinX;
    float z2 = p.y * sinX + z1 * cosX;
    
    result.x = x1;
    result.y = y1;
    result.z = z2;
    
    return result;
}

void drawLine(char screen[HEIGHT][WIDTH], Point2D p1, Point2D p2, char c) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;
    
    int x = p1.x;
    int y = p1.y;
    
    while (1) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            screen[y][x] = c;
        }
        
        if (x == p2.x && y == p2.y) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

int main() {
    // Define pyramid vertices
    Point3D vertices[5] = {
        {0, 15, 0},    // Top
        {-15, -15, 15},  // Base 1
        {15, -15, 15},   // Base 2
        {15, -15, -15},  // Base 3
        {-15, -15, -15}  // Base 4
    };
    
    printf("\x1b[2J\x1b[?25l"); // Clear and hide cursor
    
    while (1) {
        char screen[HEIGHT][WIDTH];
        
        // Clear screen
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                screen[i][j] = ' ';
            }
        }
        
        // Rotate and project vertices
        Point2D projected[5];
        for (int i = 0; i < 5; i++) {
            Point3D rotated = rotate(vertices[i], angle, angle * 1.5);
            projected[i] = project(rotated);
        }
        
        // Draw edges - base
        drawLine(screen, projected[1], projected[2], '#');
        drawLine(screen, projected[2], projected[3], '#');
        drawLine(screen, projected[3], projected[4], '#');
        drawLine(screen, projected[4], projected[1], '#');
        
        // Draw edges - sides to top
        drawLine(screen, projected[0], projected[1], '*');
        drawLine(screen, projected[0], projected[2], '*');
        drawLine(screen, projected[0], projected[3], '*');
        drawLine(screen, projected[0], projected[4], '*');
        
        // Render
        printf("\x1b[H");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (screen[i][j] == '*') {
                    printf("\x1b[33m%c\x1b[0m", screen[i][j]); // Yellow
                } else if (screen[i][j] == '#') {
                    printf("\x1b[36m%c\x1b[0m", screen[i][j]); // Cyan
                } else {
                    putchar(screen[i][j]);
                }
            }
            putchar('\n');
        }
        
        angle += 0.05;
        usleep(30000);
    }
    
    printf("\x1b[?25h");
    return 0;
}