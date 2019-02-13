#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H

class Jet
{
  public:
    Jet() {}
    Jet(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void accelerate();
    void decelerate();
    void stabilize_x();
    void stabilize_y();
    void stabilize_z();
    void tick();
    double speed;

  private:
    VAO *object;
};

#endif
