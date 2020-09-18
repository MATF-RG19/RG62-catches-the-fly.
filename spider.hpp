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

	/*metode*/

    //iscrtava model pauka
	void draw_spider(GLUquadricObj *sphere, GLuint texture) ;

    //rotacija ulevo
    void rotate_left(bool r);
    //rotacija udesno
	void rotate_right(bool r);
    //pomeranje napred
	void move_forward();
    
    //na osnovu vrednosti promenljive looking_at odredjuje vektor pravca igraca
    void calculate_the_direction_vector();

    //inicijalizacija informacija o igracu
    void init(platform * p);

    //postavljanje igraca na specificnu lokaciju
    void set_position(double x, double y, double z);

    //postavljanje platforme na kojoj se igrac nalazi
    void set_platform(platform *p);
    
    //platforma na koju bi se igrac premestio u slucaju da nastavi kretanje
    platform* next_platform();

    //vracanje igraca na pocetnu poziciju
    void reset(platform * p);

    
    void set_key(bool k);
    void set_dead(bool d);
    void set_angle(double a);

    bool get_key();
    bool get_dead();
    platform* get_platform();

    /*polja*/

    //pozicija igraca
    double x_pos;
    double y_pos;
    double z_pos;

    //platforma na kojoj se igrac trenutno nalazi
    platform* current_platform;
    
    //vektor pravca igraca
    double direction_coordinate_x;
    double direction_coordinate_y;

    //ugao pod kojim se nalazi igrac - oko z ose
    double angle;

    //pravac u kom igrac gleda
    unsigned int looking_at;

    //indikator da li je igrac ziv
    bool dead;

    //indikator da li je igrac sakupio kljuc
    bool key;

    //pomocna promenljiva
    bool rot;

	/*destruktor*/
	~spider();
};
#endif