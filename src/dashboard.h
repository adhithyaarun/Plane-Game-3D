#include "main.h"
#include "shape.h"
#include "display.h"

class Fuel
{
    public:
        Fuel() {}
        Fuel(float x, float y, float z, float size, float angle_x, float angle_y, float angle_z, color_t color);
        glm::vec3 position;
        float rotation_x;
        float rotation_y;
        float rotation_z;
        void draw(glm::mat4 VP);
        void refill();
        int units;
        Rectangle unit_1;
        Rectangle unit_2;
        Rectangle unit_3;
        Rectangle unit_4;
        int counter;
        void set_position(float x, float y, float z);
        void tick();
    private:
        VAO* object;
};

class Dashboard
{
    public:
        Dashboard() {}
        Dashboard(float x, float y, float z);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y, float z);
        void tick();
        float altitude;
        float speed;
        Fuel fuel;
        Display altimeter;
        Display speedometer;
};