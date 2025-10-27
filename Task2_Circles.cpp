#include <GL/glut.h>
#include <cmath>

struct Color { float r, g, b; };

void setPixel(int x, int y, Color col) {
    glColor3f(col.r, col.g, col.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void midpointCircle(int xc, int yc, int r, Color col) {
    int x = 0, y = r;
    int d = 1 - r;

    while (x <= y) {
        setPixel(xc + x, yc + y, col);
        setPixel(xc - x, yc + y, col);
        setPixel(xc + x, yc - y, col);
        setPixel(xc - x, yc - y, col);
        setPixel(xc + y, yc + x, col);
        setPixel(xc - y, yc + x, col);
        setPixel(xc + y, yc - x, col);
        setPixel(xc - y, yc - x, col);
        x++;
        if (d < 0)
            d += 2 * x + 1;
        else {
            y--;
            d += 2 * (x - y) + 1;
        }
    }
}

Color lerpColor(Color a, Color b, float t) {
    return {a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t};
}

void drawThickCircle(int xc, int yc, int r, int thickness, Color col) {
    int half = thickness / 2;
    for (int i = -half; i <= half; ++i)
        midpointCircle(xc, yc, r + i, col);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Color inner = {1, 0, 0};
    Color outer = {0, 0, 1};

    int xc = 300, yc = 300;
    int num = 10, base_r = 20;

    for (int i = 0; i < num; i++) {
        float t = (float)i / (num - 1);
        Color c = lerpColor(inner, outer, t);
        int r = base_r + i * 15;
        int thickness = 2 + i / 2;
        drawThickCircle(xc, yc, r, thickness, c);
    }

    glFlush();
}

void init() {
    gluOrtho2D(0, 600, 0, 600);
    glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Concentric Circles with Gradient");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
