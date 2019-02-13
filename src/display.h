#include "main.h"
#include "shape.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Digit
{
  public:
    Digit() {}
    Digit(float x, float y, int digit);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x, int digit);
    int digit;
    Rectangle segment1;
    Rectangle segment2;
    Rectangle segment3;
    Rectangle segment4;
    Rectangle segment5;
    Rectangle segment6;
    Rectangle segment7;
};

class Display
{
  public:
    Display() {}
    Display(float x, float y, int score);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float value);
    int value;
    Digit d10_0;
    Digit d10_1;
    Digit d10_2;
    Digit d10_3;
    Digit d10_4;
    Digit d10_5;
    Digit d10_6;
};

#endif