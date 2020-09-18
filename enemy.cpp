#include "enemy.hpp"
#include <iostream>

enemy::enemy() {};

enemy::enemy(double x, double y, double z, int pos, std::vector<platform*>& p, int d) {
    init(x, y, z, pos, p, d);
}

void enemy::init(double x, double y, double z, int pos, std::vector<platform*>& p, int d) {
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;
    this->position = pos;
    this->direction = d;

    this->platforms = p;

    this->show = true;
    this->kill = false;
    this->is_dead = false;
}

void enemy::reset(double x, double y, double z, int pos, std::vector<platform*>& p, int d) {
    init(x, y, z, pos, p, d);
}

void enemy::draw_enemy(GLUquadricObj *sphere, GLuint texture) {

    if (show) {
        glPushMatrix();
            //glColor3f(0, 0, 0);
            glTranslatef(this->x_pos, this->y_pos, this->z_pos);
            glScalef(0.8, 0.8, 1);

            gluQuadricDrawStyle(sphere, GLU_FILL);
            glBindTexture(GL_TEXTURE_2D, texture);
            gluQuadricTexture(sphere, GLU_TRUE);
            gluQuadricNormals(sphere, GLU_SMOOTH);
            gluSphere(sphere, 1, 20, 20);
        glPopMatrix();
    }

}

void enemy::next_position() {

    if (direction > 0) {
        if (position == platforms.size() - 1) {
            position--;
            direction = -direction;
        }
        else {
            position++;
        }
    }
    else {
         if (position == 0) {
            position++;
            direction = -direction;
        }
        else {
            position--;
        }
    }
}

void enemy::tanslate() {
    this->y_pos += direction * 0.4;
}

void enemy::set_dead(bool d) {
    this->is_dead = d;
}

void enemy::set_kill(bool k) {
    this->kill = k;
}

void enemy::set_show(bool s) {

    this->show = s;
}

void enemy::set_position(double x, double y, double z, int pos, int d) {
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;

    this->position = pos;
    this->direction = d;
}

bool enemy::get_show() {

    return this->show;
}

bool enemy::get_dead() {
    return this->is_dead;
}

bool enemy::get_kill() {
    return this->kill;
}

platform* enemy::get_platform() {

    return platforms[position];
}

enemy::~enemy() {};