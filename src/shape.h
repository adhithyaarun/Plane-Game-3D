#include "main.h"

#ifndef SHAPE_H
#define SHAPE_H

class Circle
{
  public:
    Circle() {}
    Circle(float x, float y, float r, color_t color);
    Circle(float x, float y, float z, float r, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotation_x;
    float rotation_y;
    bounding_box_t boundary;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;

  private:
    VAO *object;
};

class Rectangle
{
  public:
    Rectangle() {}
    Rectangle(float x, float y, float z, float l, float b, float angle, color_t color);
    Rectangle(float x, float y, float z, float l, float b, float angle_x, float angle_y, float angle_z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotation_x;
    float rotation_y;
    bounding_box_t boundary;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float length;
    float breadth;
  private:
    VAO *object;
};

#endif
