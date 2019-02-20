#include "main.h"
#include "missile.h"
#include <stdlib.h>

#ifndef CANNON_H
#define CANNON_H

class Cannon
{
  public:
    Cannon() {}
    Cannon(float x, float y, float z, float r_large, float r_small, float height, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float r_large;
    float r_small;
    float height;
    int recharge;
    std::vector<Bomb> bombs;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float angle_x, float angle_y, float angle_z);
    void fire(float x, float y, float z);
    void tick();

  private:
    VAO *object;
};

#endif