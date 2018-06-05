/*#include "graphics.h"
#include <math.h>
#include <string>
using namespace std;

GLdouble width, height;
int wd;

void init() {
    width = 700;
    height = 700;
}

*//* Initialize OpenGL Graphics *//*
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Black and opaque
}

*//* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. *//*
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    *//*
     * Draw here
     *//*
    double PI=3.14;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(500, 200);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (double i = 0; i < 2.0*PI+0.05; i += 2.0*PI/360.0) {
        glVertex2i(500 + 35 * cos(i),
                   200 + 35 * sin(i));
    }
    glEnd();

    // draw words
    string message = "Press Space to change color to blue";
    glColor3f(0.0, 1.0, 0.1);
    glRasterPos2i(250, 150);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    string message2 = "left mouse click to change color back!";
    glColor3f(0.0, 1.0, 0.1);
    glRasterPos2i(250, 550);
    for (char c : message2) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if(key ==32){
        glClearColor(0.0f, 0.0f, 1.0f,0.0f);
    }
    
    glutPostRedisplay();
    
    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
    
    return;
}

void cursor(int x, int y) {
    
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    }
    
    
    glutPostRedisplay();
}

void timer(int extra) {
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

*//* Main function: GLUT runs as a console application starting at main()  *//*
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(500, 400); // Position the window's initial top-left corner
    *//* create the window and store the handle to it *//*
    wd = glutCreateWindow("Project 7!!!" *//* title *//* );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}*/
#include <string.h>
#include <stdlib.h>
#include "graphics.h"
#include <time.h>
#include <sstream>

const int interval = 500;
const int block_size = 20;
const int column_count = 20;
const int row_count = 20;
const int init_pos[2] = {3, 0};

const int tetrominos[7][4][4] = {
        {{0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}},
        {{0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}},
        {{0, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0}},
        {{0, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 0}},
        {{0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0}},
        {{0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0}},
        {{0, 0, 0, 0},
                {0, 0, 1, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0}},
};

int points = 0;
int curr_block[4][4] = {};
int curr_pos[2] = {};
int blocks[column_count][row_count] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void init_curr_block() {
    memcpy(curr_block, tetrominos[rand() % 7], 4 * 4 * sizeof(int));
    curr_pos[0] = init_pos[0];
    curr_pos[1] = init_pos[1];
}

void init() {
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    srand(time(NULL));
    init_curr_block();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    for (int i = 0; i < column_count; i++) {
        for (int j = 0; j < row_count; j++) {
            if (blocks[i][j]) {
                glColor3f(0,0,1);
                glVertex2f(j, column_count - i);
                glVertex2f(j, column_count - i - 1);
                glVertex2f(j + 1, column_count - i - 1);
                glVertex2f(j + 1, column_count - i);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (curr_block[i][j]) {
                glColor3f(1,0,0);
                glVertex2f(curr_pos[0] + j, column_count - (curr_pos[1] + i));
                glVertex2f(curr_pos[0] + j, column_count - (curr_pos[1] + i + 1));
                glVertex2f(curr_pos[0] + j + 1, column_count - (curr_pos[1] + i + 1));
                glVertex2f(curr_pos[0] + j + 1, column_count - (curr_pos[1] + i));
            }
        }
    }
    glEnd();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluOrtho2D(0, width / block_size, 0, height / block_size);
}

bool is_empty(int next_x, int next_y) {
    if (next_x < 0 || row_count <= next_x) {
        return false;
    }
    if (next_y < 0 || column_count <= next_y) {
        return false;
    }
    if (blocks[next_y][next_x]) {
        return false;
    }
    return true;
}

bool move(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (curr_block[i][j]) {
                int next_x = curr_pos[0] + j + x;
                int next_y = curr_pos[1] + i + y;
                if (!is_empty(next_x, next_y)) {
                    return false;
                }
            }
        }
    }
    curr_pos[0] += x;
    curr_pos[1] += y;
    glutPostRedisplay();
    return true;
}

void game_over() {
    memset(curr_block, 0, 4 * 4 * sizeof(int));
    curr_pos[0] = 0;
    curr_pos[1] = 0;
    glutSetWindowTitle("GAME OVER");
}

void timer(int value);

void flush(int value);

void shift(int value);

void timer(int value) {
    if (!move(0, 1)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (curr_block[i][j]) {
                    blocks[curr_pos[1] + i][curr_pos[0] + j] = 1;
                }
            }
        }
        memset(curr_block, 0, 4 * 4 * sizeof(int));
        curr_pos[0] = 0;
        curr_pos[1] = 0;
        flush(0);
        return;
    }
    glutTimerFunc(interval, timer, 0);
}

void throw_new_block() {
    init_curr_block();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (curr_block[i][j] && blocks[curr_pos[1] + i][curr_pos[0] + j]) {
                game_over();
                return;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(interval, timer, 0);
}

void flush(int value) {
    for (int i = column_count - 1; i >= 0; i--) {
        int j;
        for (j = 0; j < row_count; j++) {
            if (!blocks[i][j]) {
                break;
            }
        }
        if (j == row_count) {
            std::ostringstream os;
            os << "tris: " << ++points * 10 << " points";
            glutSetWindowTitle(os.str().c_str());
            memset(blocks[i], 0, row_count * sizeof(int));
            glutPostRedisplay();
            glutTimerFunc(interval, shift, i);
            return;
        }
    }
    throw_new_block();
}

void shift(int y) {
    for (int i = y; i >= 1; i--) {
        for (int j = 0; j < row_count; j++) {
            blocks[i][j] = blocks[i - 1][j];
        }
    }
    glutPostRedisplay();
    glutTimerFunc(interval, flush, 0);
}

void rotate() {
    int tmp[4][4] = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (curr_block[i][j]) {
                int next_x = curr_pos[0] + i;
                int next_y = curr_pos[1] + 4 - j;
                if (!is_empty(next_x, next_y)) {
                    return;
                }
                tmp[4 - j][i] = 1;
            }
        }
    }
    memcpy(curr_block, tmp, 4 * 4 * sizeof(int));
    glutPostRedisplay();
}

void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            move(-1, 0);
            break;
        case GLUT_KEY_RIGHT:
            move(1, 0);
            break;
        case GLUT_KEY_UP:
            rotate();
            break;
        case GLUT_KEY_DOWN:
            move(0, 1);
            break;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(block_size * row_count, block_size * column_count);
    glutCreateWindow("Score: 0 points");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(interval, timer, 0);
    glutSpecialFunc(special);
    init();
    glutMainLoop();
    return 0;
}
