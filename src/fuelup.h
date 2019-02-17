#include "main.h"

#ifndef FUEL_H
#define FUEL_H

class FuelUp
{
  public:
    FuelUp() {}
    FuelUp(float x, float y, float z, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    bool collected;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float angle_x, float angle_y, float angle_z);
    void tick();

  private:
    VAO *object;
};

#endif