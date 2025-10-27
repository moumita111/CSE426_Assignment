#include <GL/glut.h>
#include <cmath>

struct Color { float r, g, b; };
struct Point { float x, y; };

float xmin = 150, ymin = 150, xmax = 450, ymax = 450;

void setPixel(int x, int y, Color c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(Point a, Point b, Color c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}

bool liangBarsky(float x0, float y0, float x1, float y1,
                 float &nx0, float &ny0, float &nx1, float &ny1) {
    float p[4], q[4];
    p[0] = -(x1 - x0); q[0] = x0 - xmin;
    p[1] =  (x1 - x0); q[1] = xmax - x0;
    p[2] = -(y1 - y0); q[2] = y0 - ymin;
    p[3] =  (y1 - y0); q[3] = ymax - y0;

    float u1 = 0.0, u2 = 1.0;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) return false;
        float t = q[i] / p[i];
        if (p[i] < 0) u1 = fmax(u1, t);
        else if (p[i] > 0) u2 = fmin(u2, t);
    }

    if (u1 > u2) return false;

    nx0 = x0 + (x1 - x0) * u1;
    ny0 = y0 + (y1 - y0) * u1;
    nx1 = x0 + (x1 - x0) * u2;
    ny1 = y0 + (y1 - y0) * u2;
    return true;
}

void drawWindow() {
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawWindow();

    Point lines[][2] = {
        {{100, 100}, {500, 400}},
        {{200, 500}, {400, 100}},
        {{50, 300},  {550, 300}},
        {{250, 250}, {350, 350}}
    };

    for (auto &L : lines) {
        Point a = L[0], b = L[1];
        drawLine(a, b, {0.7, 0.7, 0.7}); // original line (gray)
        float nx0, ny0, nx1, ny1;
        if (liangBarsky(a.x, a.y, b.x, b.y, nx0, ny0, nx1, ny1)) {
            drawLine({nx0, ny0}, {nx1, ny1}, {1, 0, 0}); // clipped part (red)
        }
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
    glutCreateWindow("Task 3 - Liang-Barsky Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
