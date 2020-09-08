#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

#include "spider.hpp"
#include "platform.hpp"
#include "enemy.hpp"

using namespace std;

static int window_width = 1000;
static int window_height = 600;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void draw_level();

int angle = 0;
float xPos = 0;
float yPos = 0;

platform p15(-12, 8, 0, BOTTOM | LEFT);
platform p14(-12, -8, 0, BOTTOM | RIGHT);
platform p13(-12, 4, 0, LEFT | RIGHT);
platform p12(-8, 8, 0, TOP | BOTTOM);
platform p11(-12, -4, 0, LEFT | RIGHT);
platform p10(-8, -8, 0, TOP | BOTTOM | LEFT);
platform p9(-12, 0, 0, TOP | BOTTOM | LEFT | RIGHT);
platform p8(-8, 4, 0, LEFT);
platform p7(-4, 8, 0, TOP | LEFT);
platform p6(-8, -4, 0, BOTTOM | LEFT | RIGHT);
platform p5(-4, -8, 0, TOP | BOTTOM | RIGHT);
platform p4(-8, 0, 0, TOP | LEFT | RIGHT);
platform p3(-4, 4, 0, LEFT | RIGHT);
platform p2(-4, -4, 0, TOP | LEFT | RIGHT);
platform p1(-4, 0, 0, BOTTOM | LEFT | RIGHT);

platform special(0, -8, 0, TOP);
platform end_game(-16, 0, 0, BOTTOM);
platform start(0, 0, 0, TOP);

spider s(&start);

enemy e1(-4, -8, 0);
enemy e2(-8, 4, 0);
enemy e3(-12, -4, 0);

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2);
    glutCreateWindow("Catch the fly");

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);

    glClearColor(0.52, 0.8, 0.92, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_position[] = {30, 150, -120, 0};
    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1};
    GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1};
    GLfloat light_specular[] = {0.5, 0.8, 0.5, 1};

    GLfloat model_ambient[] = {0.4, 0.4, 0.4, 1};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    start.set_neighbours(nullptr, nullptr, &p1, nullptr);
    end_game.set_neighbours(nullptr, nullptr, nullptr, &p9);
    special.set_neighbours(nullptr, nullptr, &p5, nullptr);

    p1.set_neighbours(&p2, &p3, &p4, &start);
    p2.set_neighbours(&p5, &p1, &p6, nullptr);
    p3.set_neighbours(&p1, &p7, &p8, nullptr);
    p4.set_neighbours(&p6, &p8, &p9, &p1);
    p5.set_neighbours(nullptr, &p2, &p10, &special);
    p6.set_neighbours(&p10, &p4, &p11, &p2);
    p7.set_neighbours(&p3, nullptr, &p12, nullptr);
    p8.set_neighbours(&p4, &p12, &p13, &p3);
    p9.set_neighbours(&p11, &p13, &end_game, &p4);
    p10.set_neighbours(nullptr, &p6, &p14, &p5);
    p11.set_neighbours(&p14, &p9, nullptr, &p6);
    p12.set_neighbours(&p8, nullptr, &p15, &p7);
    p13.set_neighbours(&p9, &p15, nullptr, &p8);
    p14.set_neighbours(nullptr, &p11, nullptr, &p10);
    p15.set_neighbours(&p13, nullptr, nullptr, &p12);


    /*p2.set_neighbours(&p5, &p1, &p5, nullptr);
    p3.set_neighbours(&p1, &p7, &p8, nullptr);
    p4.set_neighbours(&p6, &p8, &p9, &p1);*/

    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

static void on_display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1 ,1, -1, 1, 0.9, 7);*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)window_width / window_height, 1, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, -8, 0, 0, 0, 0, 1);

    glPushMatrix();

        e1.draw_enemy();
        e2.draw_enemy();
        e3.draw_enemy();
        
        p15.draw_platform();
        p14.draw_platform();
        p13.draw_platform();
        p12.draw_platform();
        p11.draw_platform();
        p10.draw_platform();
        p9.draw_platform();
        p8.draw_platform();
        p7.draw_platform();
        p6.draw_platform();
        p5.draw_platform();
        p4.draw_platform();
        p3.draw_platform();
        p2.draw_platform();
        p1.draw_platform();

        special.draw_platform();
        end_game.draw_platform();
        start.draw_platform();
    glPopMatrix();

    glPushMatrix();
        s.draw_spider();
    glPopMatrix();

    glPushMatrix();
        draw_level();
    glPopMatrix();

    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 27:
        exit(0);
        break;

    case 'w':
        s.move_forward();
        break;

    case 's':
        s.move_backward();
        break;

    case 'a':
        s.rotate_left();
        break;

    case 'd':
        s.rotate_right();
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

static void draw_level()
{
}
