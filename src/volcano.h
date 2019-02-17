#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano
{
  public:
    Volcano() {}
    Volcano(float x, float y, float z, float r_large, float r_small, float height, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float r_large;
    float r_small;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float angle_x, float angle_y, float angle_z);
    void tick();

  private:
    VAO *object;
};

#endif