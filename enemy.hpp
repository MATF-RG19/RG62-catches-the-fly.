#ifndef ENEMY_HPP

#define ENEMY_HPP

#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include "platform.hpp"

#define DY 4

class enemy
{
public:
    
	//konstruktor
    enemy();
    enemy(double x, double y, double z, int pos, std::vector<platform*>& p, int d);

	//metode
    void draw_enemy();
    void next_position();
    bool get_show();  
    void set_show(bool s);

    platform* get_platform();

    //polja
    double x_pos;
    double y_pos;
    double z_pos;

    int position;
    int direction;
    bool show;

    std::vector<platform*> platforms;

	//destruktor
	~enemy();
};

#endif