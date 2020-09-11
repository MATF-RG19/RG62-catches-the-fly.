#include "enemy.hpp"
#include <iostream>

enemy::enemy() {};

enemy::enemy(double x, double y, double z, int pos, std::vector<platform*>& p, int d) {

    x_pos = x;
    y_pos = y;
    z_pos = z;
    position = pos;
    direction = d;

    platforms = p;

    show = true;

    kill = false;
    is_dead = false;
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