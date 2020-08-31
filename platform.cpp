#include "platform.hpp"
#include <iostream>

platform::platform() {};

platform::platform(int x, int y, int z, unsigned int n) {
    
    x_pos = x;
    y_pos = y;
    z_pos = z;
    
    neighbours = n;
}

void platform::draw_platform() {
    
    glPushMatrix();
        std::cout << this->neighbours << std::endl;
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(this->x_pos, this->y_pos, this->z_pos);
        glScalef(4, 4, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}

platform::~platform() {};

