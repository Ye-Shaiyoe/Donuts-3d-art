
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main() {
    float A = 0, B = 0;
    float i, j;
    int k;

    float z[1760];
    char b[1760];
    int color[1760];

    const char *shade = ".,-~:;=!*#$@";
    const char *colors[] = {
        "\x1b[34m", 
        "\x1b[36m", 
        "\x1b[32m", 
        "\x1b[92m", 
        "\x1b[93m", 
        "\x1b[91m", 
        "\x1b[95m", 
        "\x1b[97m"  
    };

    printf("\x1b[2J");

    for (;;) {
        memset(b, ' ', sizeof(b));
        memset(z, 0, sizeof(z));
        memset(color, 0, sizeof(color));

        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {

                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;

                int N = (int)(8 * ((f * e - c * d * g) * m
                         - c * d * e - f * g - l * d * n));

                if (y > 0 && y < 22 && x > 0 && x < 80 && o >= 0 && o < 1760) {
                    if (D > z[o]) {
                        z[o] = D;
                        if (N < 0) N = 0;
                        if (N > 11) N = 11;
                        b[o] = shade[N];
                        color[o] = N % 8;
                    }
                }
            }
        }

        printf("\x1b[H");
        for (k = 0; k < 1760; k++) {
            if (k % 80)
                printf("%s%c", colors[color[k]], b[k]);
            else
                putchar('\n');
        }

        printf("\x1b[0m");
        A += 0.04;
        B += 0.02;
        usleep(30000);
    }

    return 0;
}

