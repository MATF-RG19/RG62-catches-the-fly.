#include "spider.hpp"
#include "platform.hpp"
#include <iostream>

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

void platform::draw_platform(int p) {
    
    glPushMatrix();
        glColor3f(p, 0.5, 0.5);
        glTranslatef(this->x_pos, this->y_pos, this->z_pos);
        glScalef(3.8, 3.8, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}

platform::~platform() {};

