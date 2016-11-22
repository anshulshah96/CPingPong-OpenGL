#include <stdio.h>
#include <GL/glut.h>

const int SCREEN_WIDTH = 1000;

void edgedetect(int x, int y, int xC, int yC, int* le, int* re)
{
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;

    x1 = x + xC;
    y1 = y + yC;
    x2 = y + xC;
    y2 = x + yC;
    x3 = x + xC;
    y3 = -y + yC;
    x4 = y + xC;
    y4 = -x + yC;
    x5 = -x + xC;
    y5 = y + yC;
    x6 = -y + xC;
    y6 = x + yC;
    x7 = -x + xC;
    y7 = -y + yC;
    x8 = -y + xC;
    y8 = -x + yC;
    if (x1 < le[y1])
        le[y1] = x1;
    if (x1 > re[y1])
        re[y1] = x1;
    if (x2 < le[y2])
        le[y2] = x2;
    if (x2 > re[y2])
        re[y2] = x2;
    if (x3 < le[y3])
        le[y3] = x3;
    if (x3 > re[y3])
        re[y3] = x3;
    if (x4 < le[y4])
        le[y4] = x4;
    if (x4 > re[y4])
        re[y4] = x4;
    if (x5 < le[y5])
        le[y5] = x5;
    if (x5 > re[y5])
        re[y5] = x5;
    if (x6 < le[y6])
        le[y6] = x6;
    if (x6 > re[y6])
        re[y6] = x6;
    if (x7 < le[y7])
        le[y7] = x7;
    if (x7 > re[y7])
        re[y7] = x7;
    if (x8 < le[y8])
        le[y8] = x8;
    if (x8 > re[y8])
        re[y8] = x8;
}
void drawpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Circle(int Radius, int xC, int yC, int le[], int re[])
{
    int P;
    int x, y;
    void Draw(int x, int y, int xC, int yC);
    P = 1 - Radius;
    x = 0;
    y = Radius;
    edgedetect(x, y, xC, yC, le, re);
    while (x <= y) {
        x++;
        if (P < 0) {
            P += 2 * x + 1;
        }
        else {
            P += 2 * (x - y) + 1;
            y--;
        }
        edgedetect(x, y, xC, yC, le, re);
    }
}
void scanfill(int x1, int y1, int r)
{
    int le[SCREEN_WIDTH], re[SCREEN_WIDTH];
    int i, y;
    for (i = 0; i < SCREEN_WIDTH; i++) // initialize le and re array values
    {
        le[i] = SCREEN_WIDTH;
        re[i] = 0;
    }
    Circle(r, x1, y1, le, re);
    for (y = 0; y < SCREEN_WIDTH; y++) // for every scan line with value y
    {
        if (le[y] <= re[y]) // refer to le and re arrays to see if a part
            for (i = le[y] + 1; i < re[y]; i++) // of the scanline is inside polygon
                drawpixel(i, y); // if so draw a horizontal line from
    } // left edge to right edge
}
