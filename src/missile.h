#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile
{
  public:
    Missile() {}
    Missile(float x, float y, float z, float angle_x, float angle_y, float angle_z, double speed, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float angle_x, float angle_y, float angle_z);
    void tick();
    double speed;
  private:
    VAO *object;
};

class Bomb
{
  public:
    Bomb() {}
    Bomb(float x, float y, float z, float angle_x, float angle_y, float angle_z, double speed, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    coord_t vec;
    void cannon_fire(coord_t unit);
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    double gravity;
  private:
    VAO *object;
};

#endif
