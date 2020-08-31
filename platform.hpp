#ifndef PLATVORMA_HPP

#define PLATVORMA_HPP

#include <stdlib.h>
#include <GL/glut.h>

class platform
{
public:
    
	//konstruktor
    platform();
	platform(int x, int y, int z, unsigned int n);

	//metode
	void draw_platform();
    
    //polja
    double x_pos;
    double y_pos;
    double z_pos;
    
    unsigned int neighbours;
    
	//destruktor
	~platform();
};

#endif
