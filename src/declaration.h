#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define GLEW_STATIC 1
#include <GL/glew.h>

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#define MACOSX_COMPATIBILITY GLUT_3_2_CORE_PROFILE
#else
#include <GL/glut.h>
#define MACOSX_COMPATIBILITY 0
#endif

#include "glhelper.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "triangle_index.hpp"
#include "vertex_opengl.hpp"
#include "mesh.hpp"


//matrice de transformation
struct transformation
{
  //mat4 rotation;
  vec3 rotation_euler;    // rotation autour de x, y, z
  vec3 rotation_center;
  vec3 translation;

  transformation():rotation_euler(),rotation_center(),translation(){}
};

struct camera
{
  transformation tr;
  mat4 projection;
};

struct objet
{
  GLuint prog;        // identifiant du shader
  GLuint vao;         // identifiant du vao
  GLuint nb_triangle; // nombre de triangle du maillage
  GLuint texture_id;  // identifiant de la texture
  bool visible;       // montre ou cache l'objet
};

struct objet3d : public objet
{
  transformation tr;
};

struct text : public objet
{
  std::string value;           // Value of the text to display
  vec2 bottomLeft;
  vec2 topRight;
};


void init_text(text *t);
void draw_text(const text* const t);


void init_snowman();
void init_snow();
void init_armadillo();
void init_sapin();
void init_skate();
void init_snowman_skate();
void init_home();
void init_hat();
void init_santa();
void init_decor();


void draw_obj3d(const objet3d* const obj, camera cam);
bool collision_sapin(int objet1, int objet2);
bool collision_armadillo(int objet1, int objet2);
bool collision_skate(int objet1, int objet2);
bool collision_hat(int objet1, int objet2);
