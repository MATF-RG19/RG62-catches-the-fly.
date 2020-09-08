#include "enemy.hpp"
#include <iostream>

enemy::enemy() {};

enemy::enemy(double x, double y, double z) {

    x_pos = x;
    y_pos = y;
    z_pos = z;

}

void enemy::draw_enemy() {

    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(this->x_pos, this->y_pos, this->z_pos);
        glScalef(0.8, 0.8, 1);
        glutSolidSphere(1, 20, 20);
    glPopMatrix();

}

enemy::~enemy() {};