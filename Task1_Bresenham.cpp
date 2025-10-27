#include <GL/glut.h>
#include <cmath>

struct Color { float r, g, b; };

void setPixel(int x, int y, Color col) {
    glColor3f(col.r, col.g, col.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


void bresenhamLine(int x1, int y1, int x2, int y2, Color col) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        setPixel(x1, y1, col);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}


void bresenhamThick(int x1, int y1, int x2, int y2, int thickness, Color col) {
    float dx = x2 - x1, dy = y2 - y1;
    float len = sqrt(dx * dx + dy * dy);
    float nx = -dy / len, ny = dx / len;
    int half = thickness / 2;

    for (int i = -half; i <= half; ++i) {
        int offsetX = round(nx * i);
        int offsetY = round(ny * i);
        bresenhamLine(x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY, col);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    bresenhamLine(50, 50, 300, 150, {0, 0, 1});
    bresenhamLine(50, 50, 150, 300, {1, 0, 0});
    bresenhamLine(300, 300, 100, 300, {0, 0.6, 0});


    bresenhamThick(350, 50, 550, 200, 7, {0.9, 0.4, 0.1});
    bresenhamThick(350, 250, 550, 350, 10, {0.1, 0.8, 0.3});

    glFlush();
}

void init() {
    gluOrtho2D(0, 600, 0, 400);
    glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Bresenham Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
