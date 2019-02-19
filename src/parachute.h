#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute
{
  public:
    Parachute() {}
    Parachute(float x, float y, float z, float r_inner, float width, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float r_inner;
    float r_outer;
    bool shot_down;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
  private:
    VAO *object;
    VAO *strings;
};

#endif