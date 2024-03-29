#include "display.h"
#include "main.h"

//  1     ___
//  2    |___|    3
//  5    |_4_|    6
//         7

Digit::Digit(float x, float y, float z, int digit)
{
    this->position = glm::vec3(x, y, z);
    this->digit = digit;

    this->segment1 = Rectangle(x - 0.0, y - 0.0, z, 1.0, 0.2, 0.0, 0.0, 0.0, COLOR_BLACK);
    this->segment2 = Rectangle(x - 0.4, y - 0.6, z, 1.0, 0.2, 0.0, 0.0, -90.0, COLOR_BLACK);
    this->segment3 = Rectangle(x + 0.4, y - 0.6, z, 1.0, 0.2, 0.0, 0.0, -90.0, COLOR_BLACK);
    this->segment4 = Rectangle(x - 0.0, y - 1.2, z, 1.0, 0.2, 0.0, 0.0, 0.0, COLOR_BLACK);
    this->segment5 = Rectangle(x - 0.4, y - 1.8, z, 1.0, 0.2, 0.0, 0.0, -90.0, COLOR_BLACK);
    this->segment6 = Rectangle(x + 0.4, y - 1.8, z, 1.0, 0.2, 0.0, 0.0, -90.0, COLOR_BLACK);
    this->segment7 = Rectangle(x - 0.0, y - 2.4, z, 1.0, 0.2, 0.0, 0.0, 0.0, COLOR_BLACK);
}

void Digit::draw(glm::mat4 VP)
{
    switch (this->digit)
    {
    case 0:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment3.draw(VP);
        this->segment5.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    case 1:
        this->segment3.draw(VP);
        this->segment6.draw(VP);
        break;
    case 2:
        this->segment1.draw(VP);
        this->segment3.draw(VP);
        this->segment4.draw(VP);
        this->segment5.draw(VP);
        this->segment7.draw(VP);
        break;
    case 3:
        this->segment1.draw(VP);
        this->segment3.draw(VP);
        this->segment4.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    case 4:
        this->segment2.draw(VP);
        this->segment3.draw(VP);
        this->segment4.draw(VP);
        this->segment6.draw(VP);
        break;
    case 5:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment4.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    case 6:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment4.draw(VP);
        this->segment5.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    case 7:
        this->segment1.draw(VP);
        this->segment3.draw(VP);
        this->segment6.draw(VP);
        break;
    case 8:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment3.draw(VP);
        this->segment4.draw(VP);
        this->segment5.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    case 9:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment3.draw(VP);
        this->segment4.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    default:
        this->segment1.draw(VP);
        this->segment2.draw(VP);
        this->segment3.draw(VP);
        this->segment5.draw(VP);
        this->segment6.draw(VP);
        this->segment7.draw(VP);
        break;
    }
}

void Digit::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, 0);
    this->segment1.set_position(x - 3.0, y + 0.4, z);
    this->segment2.set_position(x - 3.1, y + 0.3, z);
    this->segment3.set_position(x - 2.9, y + 0.3, z);
    this->segment4.set_position(x - 3.0, y + 0.2, z);
    this->segment5.set_position(x - 3.1, y + 0.1, z);
    this->segment6.set_position(x - 2.9, y + 0.1, z);
    this->segment7.set_position(x - 3.0, y + 0.0, z);
}

void Digit::tick(float x, int digit)
{
    this->digit = digit;
}

// Display
Display::Display(float x, float y, float z, int value)
{
    this->position = glm::vec3(x, y, z);
    this->value = value;

    this->d10_0 = Digit(x + 9.0, y, z, value % 10);
    value /= 10;
    this->d10_1 = Digit(x + 7.5, y, z, value % 10);
    value /= 10;
    this->d10_2 = Digit(x + 6.0, y, z, value % 10);
    value /= 10;
    this->d10_3 = Digit(x + 4.5, y, z, value % 10);
    value /= 10;
    this->d10_4 = Digit(x + 3.0, y, z, value % 10);
    value /= 10;
    this->d10_5 = Digit(x + 1.5, y, z, value % 10);
    value /= 10;
    this->d10_6 = Digit(x + 0.0, y, z, value % 10);
}

void Display::draw(glm::mat4 VP)
{
    this->d10_0.draw(VP);
    if(this->value > 9)
    {
        this->d10_1.draw(VP);
        if(this->value > 99)
        {
            this->d10_2.draw(VP);
            if(this->value > 999)
            {
                this->d10_3.draw(VP);
                if(this->value > 9999)
                {
                    this->d10_4.draw(VP);
                    if(this->value > 99999)
                    {
                        this->d10_5.draw(VP);
                        if(this->value > 999999)
                        {
                            this->d10_6.draw(VP);
                        }
                    }    
                }
            }
        }
    }
}

void Display::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->d10_6.set_position(x + 0.0, y, z);
    this->d10_5.set_position(x + 1.5, y, z);
    this->d10_4.set_position(x + 3.0, y, z);
    this->d10_3.set_position(x + 4.5, y, z);
    this->d10_2.set_position(x + 6.0, y, z);
    this->d10_1.set_position(x + 7.5, y, z);
    this->d10_0.set_position(x + 9.0, y, z);
}

void Display::tick(float value)
{
    int temp = value;
    this->value = value;
    this->d10_0.tick(this->position.x + 9.0, temp % 10);
    temp /= 10;
    this->d10_1.tick(this->position.x + 7.5, temp % 10);
    temp /= 10;
    this->d10_2.tick(this->position.x + 6.0, temp % 10);
    temp /= 10;
    this->d10_3.tick(this->position.x + 4.5, temp % 10);
    temp /= 10;
    this->d10_4.tick(this->position.x + 3.0, temp % 10);
    temp /= 10;
    this->d10_5.tick(this->position.x + 1.5, temp % 10);
    temp /= 10;
    this->d10_6.tick(this->position.x + 0.0, temp % 10);
}