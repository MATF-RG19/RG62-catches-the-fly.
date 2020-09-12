#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>
#include <unistd.h>

#include "spider.hpp"
#include "platform.hpp"
#include "enemy.hpp"

#define TIMER_ID 0
#define TIMER_ID1 1
#define TIMER_ID2 2
#define TIMER_ID3 3
using namespace std;

static int window_width = 1000;
static int window_height = 600;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

static void draw_level();
static void on_timer_move_player(int value);
static void on_timer_move_enemyes(int value);
static void on_timer_move_enemy(int value);
static void on_timer_rotate_player(int value);

int angle = 0;
float xPos = 0;
float yPos = 0;

bool player_animation = false;
bool rotate_animation = false;
bool enemy_animation = false;

int translation_value = 10;
bool block_keyboard = false;

bool show_fly = true;

platform ordinary_platform1(-16,-8, 0, 0);
platform ordinary_platform2(-16, -4, 0, 0);
platform ordinary_platform3(-16, 4, 0, 0);
platform ordinary_platform4(-16, 8, 0, 0);
platform ordinary_platform5(0, -4, 0, 0);
platform ordinary_platform6(0, 4, 0, 0);
platform ordinary_platform7(0, 8, 0, 0);

platform p15(-12, 8, 0, BOTTOM | LEFT);
platform p14(-12, -8, 0, BOTTOM | RIGHT);
platform p13(-12, 4, 0, LEFT | RIGHT);
platform p12(-8, 8, 0, TOP | BOTTOM);
platform p11(-12, -4, 0, LEFT | RIGHT);
platform p10(-8, -8, 0, TOP | BOTTOM | RIGHT);
platform p9(-12, 0, 0, BOTTOM | LEFT | RIGHT);
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

vector<platform*> v1 = {&p5, &p2, &p1, &p3, &p7};
vector<platform*> v2 = {&p10, &p6, &p4, &p8};
vector<platform*> v3 = {&p14, &p11, &p9, &p13, &p15};
enemy e1(-4, -4, 0, 1, v1, -1);
enemy e2(-8, -4, 0, 1, v2, -1);
enemy e3(-12, 4, 0, 3, v3, 1);

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


    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    //gluLookAt(s.x_pos + 15, s.y_pos + 15, 15, s.x_pos, s.y_pos, 0, 0, 0, 1);

    if (!s.get_key()) {
        glPushMatrix();
            glColor3f(1, 1, 0);
            glTranslatef(0, -8, 2);
            glutSolidCube(1);
        glPopMatrix();
    }
    else {
        glPushMatrix();
            end_game.draw_platform(0);
        glPopMatrix();
    }

    if (show_fly) {
        glPushMatrix();
            glTranslatef(-16, 0, 2);
            glColor3f(1, 0, 0);
            glutSolidCube(1);
        glPopMatrix();
    }

    glPushMatrix();
        e1.draw_enemy();
        e2.draw_enemy();
        e3.draw_enemy();
        
        ordinary_platform1.draw_platform(1);
        ordinary_platform2.draw_platform(1);
        ordinary_platform3.draw_platform(1);
        ordinary_platform4.draw_platform(1);
        ordinary_platform5.draw_platform(1);
        ordinary_platform6.draw_platform(1);
        ordinary_platform7.draw_platform(1);

        p15.draw_platform(0);
        p14.draw_platform(0);
        p13.draw_platform(0);
        p12.draw_platform(0);
        p11.draw_platform(0);
        p10.draw_platform(0);
        p9.draw_platform(0);
        p8.draw_platform(0);
        p7.draw_platform(0);
        p6.draw_platform(0);
        p5.draw_platform(0);
        p4.draw_platform(0);
        p3.draw_platform(0);
        p2.draw_platform(0);
        p1.draw_platform(0);

        special.draw_platform(0);
        start.draw_platform(0);

    glPopMatrix();

    glPushMatrix();
        s.draw_spider();
    glPopMatrix();


    glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslatef(0, -3.5, 1);
        glutSolidCone(1, 2, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(0, 6, 1);
        glScalef(2, 6, 2);
        glutSolidCube(1);
        draw_level();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(-16, 6, 1);
        glScalef(2, 6, 2);
        glutSolidCube(1);
        draw_level();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(-16, -6, 1);
        glScalef(2, 6, 2);
        glutSolidCube(1);
        draw_level();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-8, 0, -1.5);
        glScalef(1, 1, 0.1);
        glutSolidCube(21);
        draw_level();
    glPopMatrix();

    glutSwapBuffers();
}

void activate_enemies() {

    if (!e1.get_dead()) {
        e1.next_position();
        if (e1.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID1);
            return;
        }
    }
    if (!e2.get_dead()) {
        e2.next_position();
        if (e2.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID2);
            return;
        }
    }
    if (!e3.get_dead()) {
        e3.next_position();
        if (e3.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID3);
            return;
        }
    }

    glutTimerFunc(15, on_timer_move_enemyes, TIMER_ID);
}

static void on_timer_move_player(int value) {

    if (value != TIMER_ID) {
        return;
    }

    s.move_forward();

    if (e1.get_kill()) {
        e1.set_show(false);
    }
    if (e2.get_kill()) {
        e2.set_show(false);
    }
    if (e3.get_kill()) {
        e3.set_show(false);
    }

    glutPostRedisplay();

    translation_value--;

    if (translation_value == 0) {
        player_animation = false;
        translation_value = 10;
        activate_enemies();
    }

    if (player_animation) 
        glutTimerFunc(15, on_timer_move_player, TIMER_ID);
}

static void on_timer_move_enemyes(int value) {

    if (value != TIMER_ID) {
        return;
    }

    e1.tanslate();
    e2.tanslate();
    e3.tanslate();

    glutPostRedisplay();

    translation_value--;

    if (translation_value == 0) {
        translation_value = 10;
        player_animation = false;
        enemy_animation = false;
        block_keyboard = false;

        if (s.get_platform() == &end_game && s.get_key()) {
            block_keyboard = true;
            show_fly = false;
            cout << "End" << endl;
        }
    }

    if (enemy_animation) 
        glutTimerFunc(15, on_timer_move_enemyes, TIMER_ID);
}

static void on_timer_move_enemy(int value) {

    if (value == TIMER_ID1) {
        e1.tanslate();
    }
    if (value == TIMER_ID2) {
        e2.tanslate();
    }
    if (value == TIMER_ID3) {
        e3.tanslate();
    }

    glutPostRedisplay();

    translation_value--;

    if (translation_value == 0) {
        translation_value = 10;
        player_animation = false;
        enemy_animation = false;
        block_keyboard = true;
        s.set_dead(true);
    }

    if (enemy_animation) 
        glutTimerFunc(15, on_timer_move_enemy, value);
}

static void on_timer_rotate_player(int value) {

    /*if (value != TIMER_ID1 && value != TIMER_ID2) {
        return;
    }*/

    if (value == TIMER_ID1) {
        s.rotate_left(false);
    }
    else {
        s.rotate_right(false);
    }

    glutPostRedisplay();

    translation_value--;

    if (translation_value == 0) {
        translation_value = 10;
        rotate_animation = false;
        block_keyboard = false;
    }

    if (rotate_animation) 
        glutTimerFunc(15, on_timer_rotate_player, value);
}

static void on_keyboard(unsigned char key, int x, int y)
{

    platform* last = nullptr;
    platform* next = nullptr;
    
    switch (key)
    {

    case 27:
        exit(0);
        break;

    case 'w':

        if (!player_animation && !block_keyboard) {
            player_animation = true;
            enemy_animation = true;
            block_keyboard = true;

            last = s.get_platform();
            next = s.next_platform();

            if (last == next) {
                player_animation = false;
                enemy_animation = false;
                block_keyboard = false;
                break;
            }

            if (s.get_platform() == &special) {
                s.set_key(true);
                p9.neighbours |= TOP;
                cout << "Key" << endl;
            }
            
            if (s.get_platform() == e1.get_platform() && !e1.get_dead()) {
                e1.set_dead(true);
                e1.set_kill(true);
            }
            if (s.get_platform() == e2.get_platform() && !e2.get_dead()) {
                e2.set_dead(true);
                e2.set_kill(true);
            }
            if (s.get_platform() == e3.get_platform() && !e3.get_dead()) {
                e3.set_dead(true);
                e3.set_kill(true);
            }
            
            glutTimerFunc(15, on_timer_move_player, TIMER_ID);
        }
        break;

    case 'a':
            if (!rotate_animation && !block_keyboard) {
                s.rotate_left(true);

                rotate_animation = true;
                block_keyboard = true;
                glutTimerFunc(15, on_timer_rotate_player, TIMER_ID1);
            }
        break;

    case 'd':
            if (!rotate_animation && !block_keyboard) {

                rotate_animation = true;
                block_keyboard = true;
                s.rotate_right(true);
                glutTimerFunc(15, on_timer_rotate_player, TIMER_ID2);
            }
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

static void draw_level() {}