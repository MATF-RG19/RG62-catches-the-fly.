#include <iostream>
#include <cmath>
#include "../headers/spider.hpp"

void spider::init(platform * p) {
    this->x_pos = 0;
    this->y_pos = 0;
    this->z_pos = 1;
    
    this->angle = 0;
    
    this->direction_coordinate_x = -T_VALUE;
    this->direction_coordinate_y = 0;
    
    this->looking_at = 1;
    
    this->current_platform = p;

    this->key = false;

    this->dead = false;

    this->rot = true;
}

spider::spider(platform * p) {
    init(p);
}

void spider::reset(platform * p) {
    init(p);
}

//metod koji na osnovu informacije u kom smeru igrac gleda odredjuje vektor pravca
void spider::calculate_the_direction_vector() {
    
    switch(this->looking_at) {
        case TOP :
            this->direction_coordinate_x = -T_VALUE;
            this->direction_coordinate_y = 0;
            break;
        case LEFT :
            this->direction_coordinate_x = 0;
            this->direction_coordinate_y = -T_VALUE;
            break;
        case BOTTOM :
            this->direction_coordinate_x = T_VALUE;
            this->direction_coordinate_y = 0;
            break;
        case RIGHT :
            this->direction_coordinate_x = 0;
            this->direction_coordinate_y = T_VALUE;
            break;
    }
}

void spider::rotate_left(bool r) {
    
    if (r) {

        this->looking_at <<= 1;
        
        if (this->looking_at == OVERFLOW) {
            this->looking_at = 1;
        }
        
        calculate_the_direction_vector();
    }
    else {
        this->angle += 9.0;
    }
}

void spider::rotate_right(bool r) {
    
    if (r) {
    
        this->looking_at >>= 1;
        
        if (this->looking_at == UNDERFLOW) {
            this->looking_at = RIGHT;
        }
        
        calculate_the_direction_vector();
    }
    else {
        this->angle -= 9.0;
    }
}

void spider::move_forward() {

        x_pos += direction_coordinate_x * 0.4;
        y_pos += direction_coordinate_y * 0.4;
}

platform* spider::next_platform() {

    if (this->looking_at & this->current_platform->neighbours) {
        current_platform = current_platform->get_neighbour(this->looking_at);
    }
    return current_platform;
}

//metod koji iscrtava pauka
void spider::draw_spider(GLUquadricObj *sphere, GLuint texture) {
    
    if (!dead) {
        glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(this->x_pos, this->y_pos, this->z_pos);
            glRotatef(this->angle, 0, 0, 1);
            glScalef(1.2, 1.2, 1.2);


            glPushMatrix();
                glColor3f(0.93, 0.44, 0.42);
                glTranslatef(-0.7, -0.15, -0.25);
                glRotatef(-20, 0, 0, 1);
                glRotatef(-90, 0, 1, 0);
                gluCylinder(sphere, 0.05, 0, 0.3, 15, 15);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.93, 0.44, 0.42);
                glTranslatef(-0.55, 0, -0.25);
                glRotatef(40, 0, 0, 1);
                glRotatef(-90, 0, 1, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.25, 15, 15);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.93, 0.44, 0.42);
                glTranslatef(-0.7, 0.15, -0.25);
                glRotatef(20, 0, 0, 1);
                glRotatef(-90, 0, 1, 0);
                gluCylinder(sphere, 0.05, 0, 0.3, 15, 15);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.93, 0.44, 0.42);
                glTranslatef(-0.55, 0, -0.25);
                glRotatef(-40, 0, 0, 1);
                glRotatef(-90, 0, 1, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.25, 15, 15);
            glPopMatrix();

            //fourth leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(25, 0, 0, 1);
                glTranslatef(-0.1, -0.5, 0.04);
                glRotatef(135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(25, 0, 0, 1);
                glTranslatef(-0.1, -0.2, -0.25);
                glRotatef(45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //third leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(5, 0, 0, 1);
                glTranslatef(-0.20, -0.58, 0.04);
                glRotatef(135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(5, 0, 0, 1);
                glTranslatef(-0.20, -0.3, -0.25);
                glRotatef(45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //second leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(-20, 0, 0, 1);
                glTranslatef(-0.24, -0.64, 0.04);
                glRotatef(135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(-20, 0, 0, 1);
                glTranslatef(-0.25, -0.35, -0.25);
                glRotatef(45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //first leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(-35, 0, 0, 1);
                glTranslatef(-0.36, -0.76, 0.04);
                glRotatef(135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(-35, 0, 0, 1);
                glTranslatef(-0.35, -0.45, -0.25);
                glRotatef(45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //right side
            //fourth leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(-25, 0, 0, 1);
                glTranslatef(-0.1, 0.5, 0.04);
                glRotatef(-135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(-25, 0, 0, 1);
                glTranslatef(-0.1, 0.2, -0.25);
                glRotatef(-45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //third leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(-5, 0, 0, 1);
                glTranslatef(-0.20, 0.58, 0.04);
                glRotatef(-135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(-5, 0, 0, 1);
                glTranslatef(-0.20, 0.3, -0.25);
                glRotatef(-45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //second leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(20, 0, 0, 1);
                glTranslatef(-0.24, 0.64, 0.04);
                glRotatef(-135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(20, 0, 0, 1);
                glTranslatef(-0.25, 0.35, -0.25);
                glRotatef(-45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //first leg
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(35, 0, 0, 1);
                glTranslatef(-0.36, 0.76, 0.04);
                glRotatef(-135, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0, 0.8, 15, 15);
            glPopMatrix();


            glPushMatrix();
                glColor3f(0.95, 0.88, 0.84);
                glRotatef(35, 0, 0, 1);
                glTranslatef(-0.35, 0.45, -0.25);
                glRotatef(-45, 1, 0, 0);
                gluCylinder(sphere, 0.05, 0.05, 0.4, 15, 15);
            glPopMatrix();

            //body
            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glTranslatef(-0.2, 0, -0.2);
                glScalef(1.2, 0.8, 0.5);
                gluQuadricNormals(sphere, GLU_SMOOTH);
                gluSphere(sphere, 0.4, 20, 20);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.33, 0.32, 0.40);
                glRotatef(-10, 0, 1, 0);
                glTranslatef(0.55, 0, 0);
                glScalef(1, 0.90, 0.7);

                gluQuadricDrawStyle(sphere, GLU_FILL);
                glBindTexture(GL_TEXTURE_2D, texture);
                gluQuadricTexture(sphere, GLU_TRUE);
                gluQuadricNormals(sphere, GLU_SMOOTH);
                gluSphere(sphere, 0.6, 20, 20);
            glPopMatrix();

        glPopMatrix();
    }
}

void spider::set_angle(double a) {
    this->angle = a;
}

void spider::set_key(bool k) {
    this->key = k;
}

void spider::set_dead(bool d) {
    this->dead = d;
}

void spider::set_position(double x, double y, double z) {
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;
}

void spider::set_platform(platform *p) {
    this->current_platform = p;
}

bool spider::get_key() {
    return key;
}

bool spider::get_dead() {
    return this->dead;
}

platform* spider::get_platform() {
    return current_platform;
}

spider::~spider() {};
