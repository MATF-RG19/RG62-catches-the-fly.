#include "spider.hpp"
#include <iostream>
#include <cmath>

spider::spider(platform * p) {
    
    x_pos = 0;
    y_pos = 0;
    z_pos = 1;
    
    angle = 0;
    
    direction_coordinate_x = -T_VALUE;
    direction_coordinate_y = 0;
    
    looking_at = 1;
    
    current_platform = p;

    key = false;

    dead = false;

    bool rot = true;
}

platform* spider::get_platform() {
    return current_platform;
}

bool spider::get_key() {
    return key;
}
void spider::set_key(bool k) {
    this->key = k;
}

bool spider::get_dead() {
    return this->dead;
}

void spider::set_dead(bool d) {
    this->dead = d;
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

//metod koji iscrtava pauka
void spider::draw_spider() {
    
    if (!dead) {
        glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(this->x_pos, this->y_pos, this->z_pos);
            glRotatef(this->angle, 0, 0, 1);
            glScalef(1.4, 1, 1);
            glutSolidSphere(1, 20, 20);
        glPopMatrix();
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

spider::~spider() {};
