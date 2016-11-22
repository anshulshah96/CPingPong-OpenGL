#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanconvertcircle.c"
typedef struct pingpong {
    int x, y;
    int sx, sy;
    float color[3];
} pingpongt;
pingpongt pp1;
int tile1_x = 100, tile1_y;
int tile2_x = 100, tile2_y;
void init()
{
    pp1.x = 100;
    pp1.y = 100;
    pp1.sx = 1;
    pp1.sy = -1;
    pp1.color[0] = (float)(rand() % 255) / 255;
    pp1.color[1] = (float)(rand() % 255) / 255;
    pp1.color[2] = (float)(rand() % 255) / 255;
    printf("%f", pp1.color[0]);
    //	glClearColor(1.0,1.0,1.0,1.0);
    //	glColor3f(0.9,0.9,0.9);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(pp1.color);
    scanfill(pp1.x, pp1.y, 10);
    glBegin(GL_POLYGON);
    glVertex2f(tile1_x, tile1_y);
    glVertex2f(tile1_x, tile1_y - 20);
    glVertex2f(tile1_x + 60, tile1_y - 20);
    glVertex2f(tile1_x + 60, tile1_y);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(tile2_x, tile2_y);
    glVertex2f(tile2_x, tile2_y + 20);
    glVertex2f(tile2_x + 60, tile2_y + 20);
    glVertex2f(tile2_x + 60, tile2_y);
    glEnd();
    glutSwapBuffers();
    glFlush();
}
void mouse(int btn, int state, int x, int y) {}
void idle()
{
    pp1.x += pp1.sx;
    pp1.y += pp1.sy;
    if (pp1.x < 20 || pp1.x > 480)
        pp1.sx = -pp1.sx;
    if (pp1.y < 20 || pp1.y > 480)
        pp1.sy = -pp1.sy;
    glutPostRedisplay();
}
void keyboard(unsigned char k, int x, int y) 
{
    // printf("%c %d %d\n", k,x,y);
    switch(k) 
    {
        case 'a'     : printf("a\n");    break;
        case 'q'     : printf("q\n");    break;
    }
}
void special_keyboard(int k, int x, int y){
    // printf("%d %d %d\n", k,x,y);
    switch(k) 
    {
        case GLUT_KEY_UP      : printf("GLUT_KEY_UP %d\n",k);       break;
        case GLUT_KEY_DOWN    : printf("GLUT_KEY_DOWN %d\n",k);     break;
        case GLUT_KEY_RIGHT   : printf("GLUT_KEY_UP %d\n",k);       break;
        case GLUT_KEY_LEFT    : printf("GLUT_KEY_DOWN %d\n",k);     break;
    }
}
void tile(int a, int b)
{
    tile1_x = a;
    tile1_y = 20;
    tile2_x = a;
    tile2_y = 480;
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("College Model");
    glutDisplayFunc(display);
    glutPassiveMotionFunc(tile);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    // glutMouseFunc(mouse);
    init();

    glutMainLoop();
    return (0);
}
