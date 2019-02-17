#include "fuelup.h"
#include "main.h"

FuelUp::FuelUp(float x, float y, float z, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    this->collected = false;

    static GLfloat vertex_buffer_data[] = {
         1.2 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0,-0.3 * 2.0,

         1.2 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0,-0.3 * 2.0,

         0.0 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0,-0.3 * 2.0,

         0.8 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0,-0.3 * 2.0,

         0.8 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         1.2 * 2.0, 0.8 * 2.0,-0.3 * 2.0,

         0.0 * 2.0, 1.6 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         0.2 * 2.0, 1.4 * 2.0,-0.3 * 2.0,

         0.2 * 2.0, 1.6 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 1.6 * 2.0,-0.3 * 2.0,
         0.2 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
       
         1.2 * 2.0, 0.0 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0, 0.3 * 2.0,

         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0, 0.3 * 2.0,

         0.0 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0, 0.3 * 2.0,

         0.8 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0, 0.3 * 2.0,

         0.8 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.8 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,

         0.0 * 2.0, 1.6 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.2 * 2.0, 1.4 * 2.0, 0.3 * 2.0,

         0.2 * 2.0, 1.6 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 1.6 * 2.0, 0.3 * 2.0,
         0.2 * 2.0, 1.4 * 2.0, 0.3 * 2.0,

         0.0 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0, 0.3 * 2.0,

         1.2 * 2.0, 0.0 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0,-0.3 * 2.0,

         0.0 * 2.0, 1.6 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 1.6 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0,-0.3 * 2.0,

         0.0 * 2.0, 1.6 * 2.0, 0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         0.0 * 2.0, 0.0 * 2.0, 0.3 * 2.0,
         
         1.2 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0,-0.3 * 2.0,

         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0,-0.3 * 2.0,
         1.2 * 2.0, 0.0 * 2.0, 0.3 * 2.0,

         1.2 * 2.0, 0.8 * 2.0,-0.3 * 2.0,
         0.8 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,

         1.2 * 2.0, 0.8 * 2.0, 0.3 * 2.0,
         0.8 * 2.0, 1.4 * 2.0, 0.3 * 2.0,
         0.8 * 2.0, 1.4 * 2.0,-0.3 * 2.0,
    };

    this->object = create3DObject(GL_TRIANGLES, 3 * 22, vertex_buffer_data, color, GL_FILL);
}

void FuelUp::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_y * rotate_x * rotate_z);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void FuelUp::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void FuelUp::set_angle(float angle_x, float angle_y, float angle_z)
{
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
}

void FuelUp::tick()
{
    ;
}