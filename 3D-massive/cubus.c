
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#define SLEEP(x) Sleep(x)
#else
#include <unistd.h>
#define CLEAR "clear"
#define SLEEP(x) usleep(x * 1000)
#endif

#define WIDTH 80
#define HEIGHT 40
#define CUBE_SIZE 7

typedef struct {
    float x, y, z;
} Point3D;

typedef struct {
    float x, y;
} Point2D;

char screen[HEIGHT][WIDTH];
float zbuffer[HEIGHT][WIDTH];

void clearScreen() {
    memset(screen, ' ', sizeof(screen));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            zbuffer[i][j] = -9999;
        }
    }
}

Point3D rotateX(Point3D p, float angle) {
    Point3D r;
    r.x = p.x;
    r.y = p.y * cos(angle) - p.z * sin(angle);
    r.z = p.y * sin(angle) + p.z * cos(angle);
    return r;
}

Point3D rotateY(Point3D p, float angle) {
    Point3D r;
    r.x = p.x * cos(angle) + p.z * sin(angle);
    r.y = p.y;
    r.z = -p.x * sin(angle) + p.z * cos(angle);
    return r;
}

Point3D rotateZ(Point3D p, float angle) {
    Point3D r;
    r.x = p.x * cos(angle) - p.y * sin(angle);
    r.y = p.x * sin(angle) + p.y * cos(angle);
    r.z = p.z;
    return r;
}

Point2D project(Point3D p) {
    Point2D proj;
    float distance = 30;
    float factor = distance / (distance + p.z);
    proj.x = p.x * factor + WIDTH / 2;
    proj.y = p.y * factor + HEIGHT / 2;
    return proj;
}

void drawLine(Point2D p1, Point2D p2, float z, char ch) {
    int x0 = (int)p1.x, y0 = (int)p1.y;
    int x1 = (int)p2.x, y1 = (int)p2.y;
    
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    
    while (1) {
        if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
            if (z > zbuffer[y0][x0]) {
                screen[y0][x0] = ch;
                zbuffer[y0][x0] = z;
            }
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void drawCube(float angleX, float angleY, float angleZ) {
    Point3D vertices[8] = {
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        {CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        {CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},
        {CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},
        {CUBE_SIZE, CUBE_SIZE, CUBE_SIZE},
        {-CUBE_SIZE, CUBE_SIZE, CUBE_SIZE}
    };
    
    Point2D projected[8];
    
    for (int i = 0; i < 8; i++) {
        Point3D p = vertices[i];
        p = rotateX(p, angleX);
        p = rotateY(p, angleY);
        p = rotateZ(p, angleZ);
        projected[i] = project(p);
    }
    
    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };
    
    char chars[] = {'#', '@', '*', '+', '=', '-', '.'};
    
    for (int i = 0; i < 12; i++) {
        int idx = i % 7;
        drawLine(projected[edges[i][0]], projected[edges[i][1]], 
                 i * 0.1, chars[idx]);
    }
}

void render() {
    system(CLEAR);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
    printf("\n3D ASCII CUBE - Tekan Ctrl+C untuk keluar\n");
}

int main() {
    float angleX = 0, angleY = 0, angleZ = 0;
    
    printf("Memulai animasi 3D ASCII Art...\n");
    SLEEP(1000);
    
    while (1) {
        clearScreen();
        drawCube(angleX, angleY, angleZ);
        render();
        
        angleX += 0.08;
        angleY += 0.03;
        angleZ += 0.02;
        
        SLEEP(30);
    }
    
    return 0;
}
