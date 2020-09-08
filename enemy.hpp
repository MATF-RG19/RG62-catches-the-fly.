#ifndef ENEMY_HPP

#define ENEMY_HPP

#include <stdlib.h>
#include <GL/glut.h>

class enemy
{
public:
    
	//konstruktor
    enemy();
    enemy(double x, double y, double z);

	//metode
    void draw_enemy();

    //polja
    double x_pos;
    double y_pos;
    double z_pos;

	//destruktor
	~enemy();
};

#endif