#ifndef SPIDER_HPP

#define SPIDER_HPP

#include "platform.hpp"
#include <stdlib.h>
#include <GL/glut.h>

#define TOP 1
#define LEFT 2
#define BOTTOM 4
#define RIGHT 8
#define OVERFLOW 16
#define UNDERFLOW 0
#define T_VALUE 1

class spider
{
public:
    
	//konstruktor
	spider(platform * p);

	//metode
	void draw_spider();

    void rotate_left();
	void rotate_right();

	void move_forward();
    void move_backward();
    
    void calculate_the_direction_vector();

    platform* get_platform();
    platform* next_platform();

    bool get_key();
    void set_key(bool k);

    //polja
    double x_pos;
    double y_pos;
    double z_pos;
    
    double direction_coordinate_x;
    double direction_coordinate_y;
    
    double angle;
    
    unsigned int looking_at;
    bool key;

    bool dead;

    bool show;
    
    platform* current_platform;
    
	//destruktor
	~spider();
};
#endif