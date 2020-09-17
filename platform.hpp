#ifndef PLATFORM_HPP

#define PLATFORM_HPP

#include <stdlib.h>
#include <GL/glut.h>

class platform
{
public:
    
	//konstruktor
    platform();
	platform(int x, int y, int z, unsigned int n);

	//metode
	void draw_platform(GLuint front, GLuint top, GLuint side);
    void set_neighbours(platform* lp_in, platform* rp_in, platform* tp_in, platform* bp_in);
    platform* get_neighbour(unsigned int side);

    //polja
    double x_pos;
    double y_pos;
    double z_pos;
    
    unsigned int neighbours;

    platform* lp;
    platform* rp;
    platform* tp;
    platform* bp;

	//destruktor
	~platform();
};

#endif
