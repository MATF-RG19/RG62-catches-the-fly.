#include "spider.hpp"
#include <iostream>
#include <cmath>

spider::spider(platform& p) {
    
    x_pos = 0;
    y_pos = 0;
    z_pos = 1;
    
    angle = 0;
    
    direction_coordinate_x = -1;
    direction_coordinate_y = 0;
    
    looking_at = 1;
    
    current_platform = p;
}

//metod koji na osnovu informacije u kom smeru igrac gleda odredjuje vektor pravca
void spider::calculate_the_direction_vector() {
    
    switch(this->looking_at) {
        case TOP :
            this->direction_coordinate_x = -1;
            this->direction_coordinate_y = 0;
            break;
        case LEFT :
            this->direction_coordinate_x = 0;
            this->direction_coordinate_y = -1;
            break;
        case BOTTOM :
            this->direction_coordinate_x = 1;
            this->direction_coordinate_y = 0;
            break;
        case RIGHT :
            this->direction_coordinate_x = 0;
            this->direction_coordinate_y = 1;
            break;
    }
}

//metod koji iscrtava pauka
void spider::draw_spider() {
    
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(this->x_pos, this->y_pos, this->z_pos);
        glRotatef(this->angle, 0, 0, 1);
        glScalef(1.2, 0.8, 0.2);
        glutSolidCube(2);
    glPopMatrix();

}

void spider::rotate_left() {
    
    this->angle -= 90.0;
    
    this->looking_at <<= 1;
    
    
    if (this->looking_at == OVERFLOW) {
        this->looking_at = 1;
    }
    
    calculate_the_direction_vector();
}

void spider::rotate_right() {
    
    this->angle += 90.0;
    
    this->looking_at >>= 1;
    
    if (this->looking_at == UNDERFLOW) {
        this->looking_at = RIGHT;
    }
    
    calculate_the_direction_vector();
}

void spider::move_forward() {
    
    if (this->looking_at & current_platform.neighbours) {
        this->x_pos += this->direction_coordinate_x;
        this->y_pos += this->direction_coordinate_y;
    }
}

void spider::move_backward() {
    
    if (this->looking_at & current_platform.neighbours) {
        this->x_pos -= this->direction_coordinate_x;
        this->y_pos -= this->direction_coordinate_y;
    }
}

spider::~spider() {};
