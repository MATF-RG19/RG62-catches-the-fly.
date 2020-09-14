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

    bool get_dead();
    void set_dead(bool d);
    bool get_kill();
    void set_kill(bool k);
    void init(double x, double y, double z, int pos, std::vector<platform*>& p, int d);
    void reset(double x, double y, double z, int pos, std::vector<platform*>& p, int d);

    platform* get_platform();

    void tanslate();

    void set_position(double x, double y, double z, int pos, int d);

    //polja
    double x_pos;
    double y_pos;
    double z_pos;

    int position;
    int direction;
    bool show;

    bool is_dead;
    bool kill;

    std::vector<platform*> platforms;

	//destruktor
	~enemy();
};

#endif