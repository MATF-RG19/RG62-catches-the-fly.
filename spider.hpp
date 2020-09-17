#ifndef SPIDER_HPP

#define SPIDER_HPP

#include "platform.hpp"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
	void draw_spider(GLUquadricObj *sphere, GLuint texture) ;

    void rotate_left(bool r);
	void rotate_right(bool r);

	void move_forward();
    
    void calculate_the_direction_vector();

    platform* get_platform();
    platform* next_platform();

    bool get_key();
    void set_key(bool k);
    bool get_dead();
    void set_dead(bool d);
    void set_position(double x, double y, double z);
    void set_platform(platform *p);
    void set_angle(double a);
    void init(platform * p);
    void reset(platform * p);

    //polja
    double x_pos;
    double y_pos;
    double z_pos;
    platform* current_platform;
    
    double direction_coordinate_x;
    double direction_coordinate_y;
    double a;
    
    double angle;
    
    unsigned int looking_at;
    bool dead;
    bool key;
    bool rot;

	//destruktor
	~spider();
};
#endif