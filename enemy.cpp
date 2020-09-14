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
void enemy::draw_enemy() {

    if (show) {
        glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(this->x_pos, this->y_pos, this->z_pos);
            glScalef(0.8, 0.8, 1);
            glutSolidSphere(1, 20, 20);
        glPopMatrix();
    }

}

void enemy::set_show(bool s) {

    this->show = s;
}

bool enemy::get_show() {

    return this->show;
}

platform* enemy::get_platform() {

    return platforms[position];
}

bool enemy::get_dead() {
    return this->is_dead;
}
void enemy::set_dead(bool d) {
    this->is_dead = d;
}
bool enemy::get_kill() {
    return this->kill;
}
void enemy::set_kill(bool k) {
    this->kill = k;
}

void enemy::tanslate() {
    this->y_pos += direction * 0.4;
}

void enemy::set_position(double x, double y, double z, int pos, int d) {
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;

    this->position = pos;
    this->direction = d;
}

void enemy::next_position() {

    if (direction > 0) {
        if (position == platforms.size() - 1) {
            position--;
            direction = -direction;
            //this->y_pos -= DY;
        }
        else {
            position++;
            //this->y_pos += DY;
        }
    }
    else {
         if (position == 0) {
            position++;
            direction = -direction;
            //this->y_pos += DY;
        }
        else {
            position--;
            //this->y_pos -= DY;
        }
    }

}

enemy::~enemy() {};