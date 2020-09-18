#include "spider.hpp"
#include "platform.hpp"
#include <iostream>
#include <GL/glut.h>

using namespace std;

platform::platform() {};

platform::platform(int x, int y, int z, unsigned int n) {
    
    x_pos = x;
    y_pos = y;
    z_pos = z;
    
    neighbours = n;
}

void platform::set_neighbours(platform* lp_in, platform* rp_in, platform* tp_in, platform* bp_in) {

    this->lp = lp_in;
    this->rp = rp_in;
    this->tp = tp_in;
    this->bp = bp_in;

}

platform* platform::get_neighbour(unsigned int side) {

    switch (side) {
        case TOP:
            return this->tp;
        case BOTTOM:
            return this->bp;
        case LEFT:
            return this->lp;
        case RIGHT:
            return this->rp;
        default:
            return nullptr;
    }
}

//deo koda je pod komentarom jer se te stranice platforme ne vide
void platform::draw_platform(GLuint front, GLuint top, GLuint side) {
    
    glPushMatrix();
    glTranslatef(this->x_pos, this->y_pos, this->z_pos);
    glScalef(3.8, 3.8, 1);

    /*
    //left
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
    glBindTexture(GL_TEXTURE_2D, 0);*/

    //right
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

    /*//bottom
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
    glBindTexture(GL_TEXTURE_2D, 0);*/

    //top
    glBindTexture(GL_TEXTURE_2D, top);
        glBegin(GL_POLYGON);
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

    /*//back
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
    glBindTexture(GL_TEXTURE_2D, 0);*/

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
        
    glPopMatrix();
}

platform::~platform() {};

