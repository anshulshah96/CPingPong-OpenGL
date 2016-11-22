#include <stdio.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

#include <string>
#include <iostream>
#include <sstream> 
#include "GL/freeglut.h"

// #include <GLFW/glfw3.h>

using namespace std;

#define VK_W 0x57
#define VK_S 0x53

int width = 1000;
int height = 400;
int interval=1000/60;

int score_left = 0;
int score_right = 0;

int racket_width = 10;
int racket_height = 80;
int racket_speed = 10;

// left racket position
float racket_left_x = 10.0f;
float racket_left_y = 50.0f;

// right racket position
float racket_right_x = width - racket_width - 10;
float racket_right_y = 50;
int MAX_SCORE = 2   ;
float ball_pos_x = width / 2;
float ball_pos_y = height / 2;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;
int ball_size = 8;
int ball_speed = 5;

bool winner;
bool PLAYING = true;

string int2str(int x) 
{
    // converts int to string
    std::stringstream ss;
    ss << x;
    return ss.str( );
}

void drawRect(float x, float y, float width, float height) 
{
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void drawText(float x, float y, std::string text) 
{
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void initial()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,30.0,0.0,30.0);
}

void game_reset(){
    PLAYING = true;
    score_right = 0;
    score_left = 0;
}

void draw()
{
    if(PLAYING)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // ToDo: draw our scene
        drawRect(racket_left_x, racket_left_y, racket_width, racket_height);
        drawRect(racket_right_x, racket_right_y, racket_width, racket_height);
        drawRect(ball_pos_x - ball_size / 2, ball_pos_y - ball_size / 2, ball_size, ball_size);
        // draw score
        drawText(width / 2 - 10, height - 15, int2str(score_left) + ":" + int2str(score_right)); 

        // swap buffers (has to be done at the end)
        glutSwapBuffers();
    }
    else{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();   
        drawText(width / 2 - 10, height/2, winner?"Winner is Left":"Winner is Right"); 
        glutSwapBuffers();
    }
}

void vec2_norm(float& x, float &y) 
{
    // sets a vectors length to 1 (which means that x + y == 1)
    float length = sqrt((x * x) + (y * y));
    if (length != 0.0f) 
    {
        length = 1.0f / length;
        x *= length;
        y *= length;
    }
}

void keyboard(unsigned char k, int x, int y) 
{
    // printf("%c %d %d\n", k,x,y);
    if(!PLAYING) game_reset();
    switch(k)  
    {
        case 'w'     : if(racket_left_y + racket_height < height) racket_left_y += racket_speed;   break;
        case 's'     : if(racket_left_y > 0)  racket_left_y -= racket_speed;    break;
        // case 'i'     : racket_right_y += racket_speed;  break;
        // case 'k'     : racket_right_y -= racket_speed;  break;
    }
}
void special_keyboard(int k, int x, int y){
    // printf("%d %d %d\n", k,x,y);
    if(!PLAYING) game_reset();
    switch(k) 
    {
        case GLUT_KEY_UP      : if(racket_right_y + racket_height < height) racket_right_y += racket_speed;       break;
        case GLUT_KEY_DOWN    : if(racket_right_y > 0) racket_right_y -= racket_speed;    break;
        // case GLUT_KEY_RIGHT   : printf("GLUT_KEY_UP %d\n",k);       break;
        // case GLUT_KEY_LEFT    : printf("GLUT_KEY_DOWN %d\n",k);     break;
    }
}

void updateBall() 
{
    // fly a bit
    ball_pos_x += ball_dir_x * ball_speed;
    ball_pos_y += ball_dir_y * ball_speed;
    
    // hit by left racket?
    if (ball_pos_x < racket_left_x + racket_width && 
        ball_pos_x > racket_left_x &&
        ball_pos_y < racket_left_y + racket_height &&
        ball_pos_y > racket_left_y) {
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - racket_left_y) / racket_height) - 0.5f;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = t;
    }
    
    // hit by right racket?
    if (ball_pos_x > racket_right_x && 
        ball_pos_x < racket_right_x + racket_width &&
        ball_pos_y < racket_right_y + racket_height &&
        ball_pos_y > racket_right_y) {
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - racket_right_y) / racket_height) - 0.5f;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = t;
    }

    // hit left wall?
    if (ball_pos_x < 0) {
        ++score_right;
        ball_pos_x = width / 2;
        ball_pos_y = height / 2;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = 0;
    }

    // hit right wall?
    if (ball_pos_x > width) {
        ++score_left;
        ball_pos_x = width / 2;
        ball_pos_y = height / 2;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = 0;
    }

    // hit top wall?
    if (ball_pos_y > height) {
        ball_dir_y = -fabs(ball_dir_y); // force it to be negative
    }

    // hit bottom wall?
    if (ball_pos_y < 0) {
        ball_dir_y = fabs(ball_dir_y); // force it to be positive
    }

    // make sure that length of dir stays at 1
    vec2_norm(ball_dir_x, ball_dir_y);
}


void draw2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // draw score
    drawText(width / 2 - 10, height - 15, winner?"winner is Left":"winner is right"); 

    // swap buffers (has to be done at the end)
    glutSwapBuffers();
}


void update(int value) 
{
    // update ball
    if(PLAYING) updateBall();

    // Call update() again in 'interval' milliseconds
    glutTimerFunc(interval, update, 0);

    if(score_left==MAX_SCORE || score_right==MAX_SCORE)
    {
        PLAYING = false;
        if(score_right == MAX_SCORE) winner=false;
        else winner = true;
    }
    // Redisplay frame
    glutPostRedisplay();
}

void enable2D(int width, int height) 
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    // glutInit(&argc, argv);    
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);             // Initialize GLUT
    // glutInitWindowPosition(200, 100); // Position the window's initial top-left corner
    // glutInitWindowSize(640, 480);   // Set the window's initial width & height
    // glutCreateWindow("Ping Pong Game"); // Create a window with the given title
    // initial();
    // glutDisplayFunc(draw); // Register display callback handler for window re-paint
    // glutTimerFunc(interval, update, 0);
    // glutMainLoop();           // Enter the infinitely event-processing loop


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 100); 
    glutInitWindowSize(width, height);
    glutCreateWindow("Ping Pong Game");

    // Register callback functions   
    glutDisplayFunc(draw);
    glutTimerFunc(interval, update, 0);

    enable2D(width, height);
    glColor3f(1.0f, 1.0f, 1.0f);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);

    // start the whole thing
    glutMainLoop();
    return 0;
}

