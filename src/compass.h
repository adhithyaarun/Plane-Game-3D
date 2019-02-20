#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass
{
  public:
    Compass() {}
    Compass(float x, float y, float z, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float r_inner;
    float r_outer;
    float radius_n;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float angle_x, float angle_y, float angle_z);
    void tick(float angle);

  private:
    VAO *inner;
    VAO *outer;
    VAO *pointer_red;
    VAO *pointer_black;
};

#endif