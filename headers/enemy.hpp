#ifndef ENEMY_HPP

#define ENEMY_HPP

#include "platform.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class enemy {
  public:
  // konstruktor
  enemy();
  enemy(double x, double y, double z, int pos, std::vector<platform *> &p,
        int d);

  /*metode*/
  void draw_enemy(GLUquadricObj *sphere, GLuint texture);

  void init(double x, double y, double z, int pos, std::vector<platform *> &p,
            int d);
  void reset(double x, double y, double z, int pos, std::vector<platform *> &p,
             int d);

  void tanslate();

  // sledeca platforma
  void next_position();

  bool get_show();
  bool get_dead();
  bool get_kill();
  void set_position(double x, double y, double z, int pos, int d);

  void set_show(bool s);
  void set_dead(bool d);
  void set_kill(bool k);
  platform *get_platform();

  /*polja*/

  // pozicija neprijatelja
  double x_pos;
  double y_pos;
  double z_pos;

  // pravac kretanja
  int direction;

  // indikator koji govori da li treba prikazivati neprijatelja
  bool show;

  // indikator koji govori da li je neprijatelj ziv
  bool is_dead;

  // indikator koji govori da li je potrebno eliminisati neprijatelja
  bool kill;

  // niz platformi po kojima se neprijatelj krece
  std::vector<platform *> platforms;
  // pozicija u nizu platformi
  int position;

  // destruktor
  ~enemy();
};

#endif