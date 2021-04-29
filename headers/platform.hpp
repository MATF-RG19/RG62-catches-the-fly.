#ifndef PLATFORM_HPP

#define PLATFORM_HPP

#include <GL/glut.h>
#include <stdlib.h>

class platform {
  public:
  // konstruktor
  platform();
  platform(int x, int y, int z, unsigned int n);

  /*metode*/

  // iscrtava platformu
  void draw_platform(GLuint front, GLuint top, GLuint side);

  // postavlja sesede platforme
  void set_neighbours(platform *lp_in, platform *rp_in, platform *tp_in,
                      platform *bp_in);

  // vraca pokazivac na susednu platformu sa prosledjene strane
  platform *get_neighbour(unsigned int side);

  /*polja*/

  // pozicija platforme
  double x_pos;
  double y_pos;
  double z_pos;

  // indikator da li se platforma granici sa drugim platformama
  unsigned int neighbours;

  // promenljive koje pokazuju na susedne platforme
  platform *lp;
  platform *rp;
  platform *tp;
  platform *bp;

  // destruktor
  ~platform();
};

#endif
