#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Variabel untuk rotasi
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

// Fungsi untuk menggambar kubus
void drawCube() {
    glBegin(GL_QUADS);
    
    // Sisi depan (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    
    // Sisi belakang (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    
    // Sisi atas (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    
    // Sisi bawah (kuning)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    
    // Sisi kanan (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    
    // Sisi kiri (cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    
    glEnd();
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Posisi kamera
    glTranslatef(0.0f, 0.0f, -7.0f);
    
    // Rotasi kubus
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    
    drawCube();
    
    glutSwapBuffers();
}

// Fungsi untuk update animasi
void update(int value) {
    angleX += 1.0f;
    angleY += 1.5f;
    angleZ += 0.5f;
    
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;
    if (angleZ > 360) angleZ -= 360;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// Fungsi keyboard untuk kontrol manual
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': angleX += 5.0f; break;
        case 's': angleX -= 5.0f; break;
        case 'a': angleY -= 5.0f; break;
        case 'd': angleY += 5.0f; break;
        case 'q': angleZ += 5.0f; break;
        case 'e': angleZ -= 5.0f; break;
        case 27: exit(0); break; // ESC untuk keluar
    }
    glutPostRedisplay();
}

// Fungsi reshape
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi inisialisasi
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    printf("=== Kubus 3D dengan OpenGL ===\n");
    printf("Kontrol:\n");
    printf("W/S - Rotasi sumbu X\n");
    printf("A/D - Rotasi sumbu Y\n");
    printf("Q/E - Rotasi sumbu Z\n");
    printf("ESC - Keluar\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Kubus 3D - Bahasa C");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}