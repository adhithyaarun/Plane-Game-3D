#include "dashboard.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z, float size, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = 0.0;
    this->rotation_y = 0.0;
    this->rotation_z = 0.0;
    this->units = 4;
    this->counter = 0;

    static const GLfloat vertex_buffer_data[] = {
        0.50 * size, 0.62 * size, 0.00,
        0.00 * size, 0.62 * size, 0.00,
        0.00 * size, 0.00 * size, 0.00,

        0.50 * size, 0.62 * size, 0.00,       
        0.00 * size, 0.00 * size, 0.00,
        0.60 * size, 0.49 * size, 0.00,

        0.60 * size, 0.49 * size, 0.00,
        0.00 * size, 0.00 * size, 0.00, 
        0.60 * size, 0.00 * size, 0.00,

        0.00 * size, 0.70 * size, 0.00,
        0.00 * size, 0.62 * size, 0.00,
        0.14 * size, 0.62 * size, 0.00,

        0.14 * size, 0.70 * size, 0.00,
        0.00 * size, 0.70 * size, 0.00,
        0.14 * size, 0.62 * size, 0.00
    };
    this->unit_1 = Rectangle(this->position.x + 0.3, this->position.y + 0.11, this->position.z, 0.40 * size, 0.07 * size, 0.00, COLOR_GREEN);
    this->unit_2 = Rectangle(this->position.x + 0.3, this->position.y + 0.24, this->position.z, 0.40 * size, 0.07 * size, 0.00, COLOR_GREEN);
    this->unit_3 = Rectangle(this->position.x + 0.3, this->position.y + 0.37, this->position.z, 0.40 * size, 0.07 * size, 0.00, COLOR_GREEN);
    this->unit_4 = Rectangle(this->position.x + 0.3, this->position.y + 0.49, this->position.z, 0.40 * size, 0.07 * size, 0.00, COLOR_GREEN);

    this->object = create3DObject(GL_TRIANGLES, 5 * 3, vertex_buffer_data, color, GL_FILL);
}

void Fuel::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    /* No need as coordinates centered at (0, 0, 0) of the cube around which we want to rotate. */
    // rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_z * rotate_x * rotate_y);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->units > 0)
    {
        this->unit_1.draw(VP);
        if(this->units > 1)
        {
            this->unit_2.draw(VP);
            if(this->units > 2)
            {
                this->unit_3.draw(VP);
                if(this->units > 3)
                {
                    this->unit_4.draw(VP);
                }
            }
        }
    }
}

void Fuel::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Fuel::refill()
{
    this->units = 4;
}

void Fuel::tick()
{
    ++this->counter;
    if(counter == 300)
    {
        --this->units;
        this->counter = 0;
    }
}

Dashboard::Dashboard(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->altitude = 35000.0;
    this->speed = 800.0;
    this->fuel = Fuel(this->position.x - 0.8, this->position.y, this->position.z + 0.0, 1.0, 0.0, 0.0, 0.0, COLOR_BLACK);
    this->altimeter = Display(this->position.x, this->position.y + 0.5, this->position.z, this->altitude);
    this->speedometer = Display(this->position.x, this->position.y, this->position.z, this->speed);
}

void Dashboard::draw(glm::mat4 VP)
{
    this->fuel.draw(VP);
    this->altimeter.draw(VP);
    this->speedometer.draw(VP);
}

void Dashboard::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->fuel.set_position(x, y, z);
}

void Dashboard::tick()
{
    this->set_position(this->position.x, this->position.y, this->position.z);
    this->fuel.tick();
    this->altimeter.tick(this->altitude);
    this->speedometer.tick(this->speed);
}