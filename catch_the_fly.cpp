#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>
#include <unistd.h>

#include "image.h"
#include "spider.hpp"
#include "platform.hpp"
#include "enemy.hpp"


#define TIMER_ID 0
#define TIMER_ID1 1
#define TIMER_ID2 2
#define TIMER_ID3 3

#define WHITE 4
#define RED  5
#define GOLD 6

using namespace std;

static int window_width = 1400;
static int window_height = 800;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

static void on_timer_move_player(int value);
static void on_timer_move_enemyes(int value);
static void on_timer_move_enemy(int value);
static void on_timer_rotate_player(int value);
static void on_timer_game(int value);
static void on_timer_gate(int value);
static void on_timer(int value);

static void initialize(void);
static void draw_parametrized_cube(GLuint front, GLuint top, GLuint side);

//niz identifikatora tekstura
static GLuint names[25];

int angle = 0;
float xPos = 0;
float yPos = 0;

bool player_animation = false;
bool rotate_animation = false;
bool enemy_animation = false;

int translation_value = 10;
bool block_keyboard = false;
bool show_fly = true;

bool gate_down = false;
double gate_parameter = 0;

int key_angle = 0;
unsigned time_value = 0;

//indikatori vidljivosti teksta
bool show_noice = false;
bool show_ouch = false;

GLUquadricObj *quadratic = gluNewQuadric();

//platforme po kojima se igrac i neprijatelji ne krecu
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

//posebne platforme
platform special(0, -8, 0, TOP);
platform end_game(-16, 0, 0, BOTTOM);
platform start(0, 0, 0, TOP);

//instanciranje igraca
spider s(&start);

//niz sa platformama po kojima se krece neprijatelj
vector<platform*> v1 = {&p5, &p2, &p1, &p3, &p7};
vector<platform*> v2 = {&p10, &p6, &p4, &p8};
vector<platform*> v3 = {&p14, &p11, &p9, &p13, &p15};

//instanciranje neprijatelja
enemy e1(-4, -4, 0.1, 1, v1, -1);
enemy e2(-8, -4, 0.1, 1, v2, -1);
enemy e3(-12, 4, 0.1, 3, v3, 1);

//Funkcija koja vrsi ispis teksta u prostoru,
//koristi se za ispis broja preostalih klikova potrebnih 
//da bi se povrce skroz uvuklo pod zemlju
void show_text(string text, int color, double x, double y, double z)
{ 
    //Opcija 0 je ispis teksta belom bojom, odnosno kada je 
    //krtica delom uvukla povrce, ali trenutno nije zakacena za njega
    //Opcija 1 je za ispis u slucaju da krtica uvlaci trenutno, tekst se ispisuje crveno
    
    //Ne zelimo da se tekst osvetljava
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
        
    if(color == WHITE)
        glColor3f(1, 1, 1);
    else if (color == RED) 
        glColor3f(1, 0, 0);
    else if (color == GOLD)
        glColor3f(0.86, 0.68, 0.30);
    
    glRasterPos3f(x, y, z);

    for(int i = 0; i < text.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING); 
}

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

    GLfloat light_position[] = {-50, -50, 50, 0};
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

    glutTimerFunc(100, on_timer, TIMER_ID);
    glutTimerFunc(1000, on_timer_game, TIMER_ID);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //inicijalizacija tekstura
    initialize();
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)window_width / window_height, 1, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, -8, 0, 0, 0, 0, 1);

    show_text("Time:", WHITE, 0, 4, 14);
    show_text(to_string(time_value), WHITE, 0, 5.5, 14.05);

    if(show_noice) {
        show_text("Noice!", GOLD, 0, 4.155, 13.5);
    }
    if(show_ouch) {
        show_text("Ouch!", RED, 0, 4.15, 13.5);
    }

    if (!s.get_key()) {
        glPushMatrix();
            glColor3f(1, 1, 0);
            glTranslatef(0, -8, 2);
            glRotatef(key_angle, 0, 0, 1);
            glRotatef(-45, 0, 1 , 0);
            glRotatef(45, 1, 0, 0);
            draw_parametrized_cube(names[21], names[21], names[21]);
        glPopMatrix();
    }

    if (show_fly) {
        glPushMatrix();
            glTranslatef(-16, 0, 2.5);
            glRotatef(-10, 0, 1, 0);
            
            //krila
            glPushMatrix();

                glColor3f(1, 1, 1);
                glTranslatef(0.1, 0.06, 0.5);
                glRotatef(5, 1, 0, 0);
                glScalef(0.25, 0.25, 0.25);
                
                glBegin(GL_POLYGON);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, 0.5, 0.7);
                    glVertex3f(0, 2, -1);
                    glVertex3f(0, 2, -3);
                    glVertex3f(0, 1, -2.5);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3f(1, 1, 1);
                glTranslatef(0.1, -0.06, 0.5);
                glRotatef(-5, 1, 0, 0);
                glScalef(0.25, 0.25, 0.25);
                
                glBegin(GL_POLYGON);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, -0.5, 0.7);
                    glVertex3f(0, -2, -1);
                    glVertex3f(0, -2, -3);
                    glVertex3f(0, -1, -2.5);
                glEnd();
            glPopMatrix();

            //telo
            glTranslatef(0, 0, 0.22);
            glScalef(0.6, 0.6, 0.6);
            
            glPushMatrix();    
                glColor3f(0.2, 0, 0.2);
                glTranslatef(0, 0, 0.65);
                gluSphere(quadratic, 0.1, 10, 10);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(0, 0, 0.45);
                gluSphere(quadratic, 0.2, 10, 10);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2, 0.2, 0.2);
                glScalef(1, 0.8, 1.3);
                gluSphere(quadratic, 0.3, 10, 10);
            glPopMatrix();
        glPopMatrix();
    }

    glPushMatrix();
        s.draw_spider(quadratic, names[20]);
    glPopMatrix();

    //platforme
    glPopMatrix();
        ordinary_platform1.draw_platform(names[14], names[13], names[14]);
        ordinary_platform2.draw_platform(names[14], names[13], names[14]);
        ordinary_platform3.draw_platform(names[14], names[13], names[14]);
        ordinary_platform4.draw_platform(names[14], names[13], names[14]);
        ordinary_platform5.draw_platform(names[14], names[13], names[14]);
        ordinary_platform6.draw_platform(names[14], names[13], names[14]);
        ordinary_platform7.draw_platform(names[14], names[13], names[14]);

        p15.draw_platform(names[14], names[8], names[14]);
        p14.draw_platform(names[14], names[7], names[14]);
        p13.draw_platform(names[14], names[1], names[14]);
        p12.draw_platform(names[14], names[2], names[14]);
        p11.draw_platform(names[14], names[1], names[14]);
        p10.draw_platform(names[14], names[12], names[14]);
        p9.draw_platform(names[14], names[0], names[14]);
        p8.draw_platform(names[14], names[5], names[14]);
        p7.draw_platform(names[14], names[6], names[14]);
        p6.draw_platform(names[14], names[11], names[14]);
        p5.draw_platform(names[14], names[12], names[14]);
        p4.draw_platform(names[14], names[10], names[14]);
        p3.draw_platform(names[14], names[1], names[14]);
        p2.draw_platform(names[14], names[10], names[14]);
        p1.draw_platform(names[14], names[11], names[14]);

        special.draw_platform(names[14], names[3], names[14]);
        end_game.draw_platform(names[14], names[4], names[14]);
        start.draw_platform(names[14], names[3], names[14]);
    glPopMatrix();

    //ograda
    glPushMatrix();
        if (!gate_down) {
            glColor3f(0.86, 0.68, 0.30);
            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(-14, 1.8, -gate_parameter);
                gluCylinder(quadratic, 0.2, 0.0, 1, 32, 32);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(-14, 0.9, -gate_parameter);
                gluCylinder(quadratic, 0.2, 0.0, 1.5, 32, 32);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(-14, 0, -gate_parameter);
                gluCylinder(quadratic, 0.2, 0.0, 2, 32, 32);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(-14, -1.8, -gate_parameter);
                gluCylinder(quadratic, 0.2, 0.0, 1, 32, 32);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.86, 0.68, 0.30);
                glTranslatef(-14, -0.9, -gate_parameter);
                gluCylinder(quadratic, 0.2, 0.0, 1.5, 32, 32);
            glPopMatrix();
        }
    glPopMatrix();

    glPushMatrix();
        e1.draw_enemy(quadratic, names[22]);
        e2.draw_enemy(quadratic, names[22]);
        e3.draw_enemy(quadratic, names[22]);
    glPopMatrix();

    //zbunje
    glPushMatrix();
        glTranslatef(1, 6.5, 2);
        glScalef(1.8, 5, 1.8);
        draw_parametrized_cube(names[18], names[17], names[19]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15, 6.5, 2);
        glScalef(1.8, 5, 1.8);
        draw_parametrized_cube(names[18], names[17], names[19]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15, -5, 2);
        glScalef(1.8, 5, 1.8);
        draw_parametrized_cube(names[18], names[17], names[19]);
    glPopMatrix();

    //podloga
    glPushMatrix();
        glTranslatef(-8, 0, -0.4);
        glScalef(22, 22, 1);
        draw_parametrized_cube(names[16], names[15], names[16]);
    glPopMatrix();

    glutSwapBuffers();
}

void activate_enemies() {

    if (!e1.get_dead()) {
        e1.next_position();
        if (e1.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID1);
            show_ouch = true;
            return;
        }
    }
    if (!e2.get_dead()) {
        e2.next_position();
        if (e2.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID2);
            show_ouch = true;
            return;
        }
    }
    if (!e3.get_dead()) {
        e3.next_position();
        if (e3.get_platform() == s.get_platform()) {
            s.set_dead(true);
            glutTimerFunc(15, on_timer_move_enemy, TIMER_ID3);
            show_ouch = true;
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

        if (s.get_platform() == &end_game && s.get_key()) {
            block_keyboard = true;
            show_fly = false;
            show_noice = true;
            //cout << "End" << endl;
        }
        else {
            activate_enemies();
        }
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

static void on_timer_gate(int value) {

    if (value != TIMER_ID) {
        return;
    }

    gate_parameter += 0.1;

    if (gate_parameter > 3)
        gate_down = true;

    if(!gate_down)
        glutTimerFunc(15, on_timer_gate, value);
}

static void on_timer_game(int value) {

    if (value != TIMER_ID) {
        return;
    }

    time_value++;

    glutPostRedisplay();

    if(!s.get_dead())
        glutTimerFunc(1000, on_timer_game, value);
}

static void on_timer(int value) {

    if (value != TIMER_ID) {
        return;
    }

    key_angle += 4;

    key_angle %= 360;

    glutPostRedisplay();

    if(!s.get_key())
        glutTimerFunc(100, on_timer, value);
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
                glutTimerFunc(30, on_timer_gate, TIMER_ID);
                //cout << "Key" << endl;
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
    case 'r' :
            //postavljanje svih vrednosti na podrazumevane
            angle = 0;
            xPos = 0;
            yPos = 0;
            player_animation = false;
            rotate_animation = false;
            enemy_animation = false;
            translation_value = 10;
            block_keyboard = false;
            show_fly = true;

            gate_down = false;
            gate_parameter = 0;

            key_angle = 0;
            time_value = 0;
            
            e1.reset(-4, -4, 0, 1, v1, -1);
            e2.reset(-8, -4, 0, 1, v2, -1);
            e3.reset(-12, 4, 0, 3, v3, 1);

            s.reset(&start);

            show_noice = false;
            show_ouch = false;

            p9.neighbours = p9.neighbours & ~TOP;
            glutTimerFunc(1000, on_timer_game, TIMER_ID);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

//parametrizacija kocke
static void draw_parametrized_cube(GLuint front, GLuint top, GLuint side) {

    //right
    glBindTexture(GL_TEXTURE_2D, side);
        glBegin(GL_QUADS);
            glNormal3f(0, -1, 0);

            glTexCoord2f(0.1, 0.1);
            glVertex3f(0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(-0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(-0.5, -0.5, 0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(0.5, -0.5, 0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    //left
    glBindTexture(GL_TEXTURE_2D, side);
        glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);

            glTexCoord2f(0.1, 0.1);
            glVertex3f(0.5, 0.5, -0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(-0.5, 0.5, -0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(-0.5, 0.5, 0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(0.5, 0.5, 0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    //bottom
    glBindTexture(GL_TEXTURE_2D, top);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, -1);

            glTexCoord2f(0.1, 0.1);
            glVertex3f(-0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(0.5, 0.5, -0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    //top
    glBindTexture(GL_TEXTURE_2D, top);
       glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0.1, 0.1);
            glVertex3f(0.5, -0.5, 0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(0.5, 0.5, 0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(-0.5, 0.5, 0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(-0.5, -0.5, 0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    //back
    glBindTexture(GL_TEXTURE_2D, front);
        glBegin(GL_QUADS);
            glNormal3f(-1, 0, 0);
            
            glTexCoord2f(0.1, 0.1);
            glVertex3f(-0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(-0.5, 0.5, -0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(-0.5, 0.5, 0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(-0.5, -0.5, 0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    //front
    glBindTexture(GL_TEXTURE_2D, front);
        glBegin(GL_QUADS);
            glNormal3f(1, 0, 0);
            
            glTexCoord2f(0.1, 0.1);
            glVertex3f(0.5, -0.5, -0.5);

            glTexCoord2f(0.9, 0.1);
            glVertex3f(0.5, 0.5, -0.5);

            glTexCoord2f(0.9, 0.9);
            glVertex3f(0.5, 0.5, 0.5);

            glTexCoord2f(0.1, 0.9);
            glVertex3f(0.5, -0.5, 0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}


/**************************************/
/*
*Kod preuzet od Davida Nestorovica
*github: https://github.com/dnestorovic
*/
/*************************************/


//funkcija po uzoru na funkciju inicijalizacije sa vezbi
static void initialize(void)
{
    //instanciranje objekta tipa image
    Image * image;

    //glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    
    //inicijalizacija slike    
    image = image_init(0, 0);

    //trazimo da nam se obezbedi 1 id i smesti u niz names kako bismo koristili teksturu
    //niz se nalazi na ovom mestu jer sam planirao da ubacim 2 teksture, od toga sam
    //za sada odustao pa i nije neophodan niz, mogla je promenljiva
    glGenTextures(25, names);

    //ovde je bio problem konverzije string tipa u char*
    //verovatno zbog toga sto je biblioteka image pisana u c-u
    //kako bi radilo u image.c sam promenio da drugi argument fje image_read bude
    //konstantan char*
    //a onda sam na internetu pronasao metodu c_str() nad objektima tipa string
    string s1 = "textures/cross.bmp";
    image_read(image, s1.c_str());

    
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);



    std::string s2 = "textures/horizontal.bmp";
    image_read(image, s2.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s3 = "textures/vertical.bmp";
    image_read(image, s3.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s4 = "textures/top.bmp";
    image_read(image, s4.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s5 = "textures/bottom.bmp";
    image_read(image, s5.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[4]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s6 = "textures/left.bmp";
    image_read(image, s6.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[5]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s7 = "textures/angle_t_l.bmp";
    image_read(image, s7.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[6]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s8 = "textures/angle_b_r.bmp";
    image_read(image, s8.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[7]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s9 = "textures/angle_b_l.bmp";
    image_read(image, s9.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[8]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s10 = "textures/left_t.bmp";
    image_read(image, s10.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[9]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s11 = "textures/top_t.bmp";
    image_read(image, s11.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[10]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s12 = "textures/bottom_t.bmp";
    image_read(image, s12.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[11]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s13 = "textures/right_t.bmp";
    image_read(image, s13.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[12]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s14 = "textures/platform_front.bmp";
    image_read(image, s14.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[13]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s15 = "textures/platform_side.bmp";
    image_read(image, s15.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[14]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

     std::string s16 = "textures/base_top.bmp";
    image_read(image, s16.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[15]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s17 = "textures/base_front_side.bmp";
    image_read(image, s17.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[16]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s18 = "textures/bush_top.bmp";
    image_read(image, s18.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[17]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s19 = "textures/bush_front.bmp";
    image_read(image, s19.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[18]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s20 = "textures/bush_side.bmp";
    image_read(image, s20.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[19]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s21 = "textures/spider_body.bmp";
    image_read(image, s21.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[20]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s22 = "textures/key.bmp";
    image_read(image, s22.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[21]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);

    std::string s23 = "textures/enemy.bmp";
    image_read(image, s23.c_str());
 
    //podesavanja teksture
    //pocinjemo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, names[22]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //zavrsavamo rad nad teksturom
    glBindTexture(GL_TEXTURE_2D, 0);


    //uklanjamo dinamicki alociran objekat
    image_done(image);

}