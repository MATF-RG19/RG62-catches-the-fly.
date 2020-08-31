#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

#include "spider.hpp"
#include "platform.hpp"

using namespace std;

static int window_width = 1000;
static int window_height = 600;

static void on_display(void);
static void on_keyboard(unsigned char key,int x,int y);
static void on_reshape(int width, int height);

int angle = 0;
float xPos = 0;
float yPos = 0;

platform p1(0, 0, 0, TOP | LEFT);
spider s(p1);

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2);
    glutCreateWindow("Catch the fly");
    
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    
    glClearColor(0.52 ,0.8 ,0.92, 0);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat light_position[] = { 30, 150, -120, 0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_specular[] = { 0.5, 0.8, 0.5, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    
    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

static void on_display(void){
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, window_width, window_height);
    
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1 ,1, -1, 1, 0.9, 7);*/
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) window_width / window_height, 1, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, 0, 0, 0, 0, 0, 1);
    
    glPushMatrix();
        p1.draw_platform();
    glPopMatrix();
    
    glPushMatrix();
        s.draw_spider();
    glPopMatrix();
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key,int x,int y){
    
    switch(key){
        
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
