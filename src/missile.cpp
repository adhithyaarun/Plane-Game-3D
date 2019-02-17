#include "missile.h"
#include "main.h"

// Missile
Missile::Missile(float x, float y, float z, float angle_x, float angle_y, float angle_z, double speed, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
    this->speed = speed + 1.0;

    static GLfloat vertex_buffer_data[10000];
    float angle = ((360.0 / 20.0) * M_PI) / 180.0;

    float x_coord = 0.2;
    float y_coord = 0.0;

    float temp_x = 0.0;
    float temp_y = 0.0;

    float length = 3.0;

    int iteration_size = 36;

    for (int i = 0; i < 20; ++i)
    {
        // Front Arc
        vertex_buffer_data[i * iteration_size] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 1] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 2] = 1.0;

        vertex_buffer_data[i * iteration_size + 3] = 0.0;
        vertex_buffer_data[i * iteration_size + 4] = 0.0;
        vertex_buffer_data[i * iteration_size + 5] = (length / 2.0);

        vertex_buffer_data[i * iteration_size + 6] = x_coord;
        vertex_buffer_data[i * iteration_size + 7] = y_coord;
        vertex_buffer_data[i * iteration_size + 8] = 1.0;

        // Back Arc
        vertex_buffer_data[i * iteration_size + 9] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 10] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 11] = -(length / 1.5);

        vertex_buffer_data[i * iteration_size + 12] = 0.0;
        vertex_buffer_data[i * iteration_size + 13] = 0.0;
        vertex_buffer_data[i * iteration_size + 14] = -(length / 1.5);

        vertex_buffer_data[i * iteration_size + 15] = x_coord;
        vertex_buffer_data[i * iteration_size + 16] = y_coord;
        vertex_buffer_data[i * iteration_size + 17] = -(length / 1.5);

        // Join Triangle 1
        // Front
        vertex_buffer_data[i * iteration_size + 18] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 19] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 20] = 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 21] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 22] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 23] = -(length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 24] = x_coord;
        vertex_buffer_data[i * iteration_size + 25] = y_coord;
        vertex_buffer_data[i * iteration_size + 26] = 1.0;

        // Join Triangle 2
        // Back
        vertex_buffer_data[i * iteration_size + 27] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 28] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 29] = -(length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 30] = x_coord;
        vertex_buffer_data[i * iteration_size + 31] = y_coord;
        vertex_buffer_data[i * iteration_size + 32] = 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 33] = x_coord;
        vertex_buffer_data[i * iteration_size + 34] = y_coord;
        vertex_buffer_data[i * iteration_size + 35] = -(length / 1.5);

        // Reset x & y
        temp_x = (x_coord * cos(angle)) - (y_coord * sin(angle));
        temp_y = (x_coord * sin(angle)) + (y_coord * cos(angle));

        x_coord = temp_x;
        y_coord = temp_y;
    }

    this->object = create3DObject(GL_TRIANGLES, 21 * 20 + 72, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP)
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

void Missile::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Missile::set_angle(float angle_x, float angle_y, float angle_z)
{
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
}

void Missile::tick()
{
    this->position.x += this->speed * sin(this->rotation_y * M_PI / 180.0);
    this->position.y -= 0.3;
    this->position.z += this->speed * cos(this->rotation_y * M_PI / 180.0);;
    this->set_position(this->position.x, this->position.y, this->position.z);
}

// Bomb
Bomb::Bomb(float x, float y, float z, float angle_x, float angle_y, float angle_z, double speed, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = 90.0 ;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
    this->speed = speed;
    this->gravity = 0.02;

    static GLfloat vertex_buffer_data[10000];
    float angle = ((360.0 / 20.0) * M_PI) / 180.0;

    float x_coord = 0.6;
    float y_coord = 0.0;

    float temp_x = 0.0;
    float temp_y = 0.0;

    int iteration_size = 63;

    for (int i = 0; i < 20; ++i)
    {
        // Middle Arc
        vertex_buffer_data[i * iteration_size + 0] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 1] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 2] = 0.0;

        vertex_buffer_data[i * iteration_size + 3] = 0.0;
        vertex_buffer_data[i * iteration_size + 4] = 0.0;
        vertex_buffer_data[i * iteration_size + 5] = 0.0;

        vertex_buffer_data[i * iteration_size + 6] = x_coord;
        vertex_buffer_data[i * iteration_size + 7] = y_coord;
        vertex_buffer_data[i * iteration_size + 8] = 0.0;

        // Front Arc
        vertex_buffer_data[i * iteration_size + 9] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 10] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 11] = 1.0;

        vertex_buffer_data[i * iteration_size + 12] = 0.0;
        vertex_buffer_data[i * iteration_size + 13] = 0.0;
        vertex_buffer_data[i * iteration_size + 14] = 1.0;

        vertex_buffer_data[i * iteration_size + 15] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 16] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 17] = 1.0;

        // Join
        vertex_buffer_data[i * iteration_size + 18] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 19] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 20] = 0.0;

        vertex_buffer_data[i * iteration_size + 21] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 22] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 23] = 1.0;

        vertex_buffer_data[i * iteration_size + 24] = x_coord;
        vertex_buffer_data[i * iteration_size + 25] = y_coord;
        vertex_buffer_data[i * iteration_size + 26] = 0.0;

        vertex_buffer_data[i * iteration_size + 27] = x_coord;
        vertex_buffer_data[i * iteration_size + 28] = y_coord;
        vertex_buffer_data[i * iteration_size + 29] = 0.0;

        vertex_buffer_data[i * iteration_size + 30] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 31] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 32] = 1.0;

        vertex_buffer_data[i * iteration_size + 33] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 34] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 35] = 1.0;

        // Back
        vertex_buffer_data[i * iteration_size + 36] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 37] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 38] = -1.0;

        vertex_buffer_data[i * iteration_size + 39] = 0.0;
        vertex_buffer_data[i * iteration_size + 40] = 0.0;
        vertex_buffer_data[i * iteration_size + 41] = -1.0;

        vertex_buffer_data[i * iteration_size + 42] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 43] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 44] = -1.0;

        // Join
        vertex_buffer_data[i * iteration_size + 45] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 46] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 47] = 0.0;

        vertex_buffer_data[i * iteration_size + 48] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 49] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 50] = -1.0;

        vertex_buffer_data[i * iteration_size + 51] = x_coord;
        vertex_buffer_data[i * iteration_size + 52] = y_coord;
        vertex_buffer_data[i * iteration_size + 53] = 0.0;

        vertex_buffer_data[i * iteration_size + 54] = x_coord;
        vertex_buffer_data[i * iteration_size + 55] = y_coord;
        vertex_buffer_data[i * iteration_size + 56] = 0.0;

        vertex_buffer_data[i * iteration_size + 57] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 58] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 59] = -1.0;

        vertex_buffer_data[i * iteration_size + 60] = (x_coord / 1.5 * cos(angle)) - (y_coord / 1.5 * sin(angle));
        vertex_buffer_data[i * iteration_size + 61] = (x_coord / 1.5 * sin(angle)) + (y_coord / 1.5 * cos(angle));
        vertex_buffer_data[i * iteration_size + 62] = -1.0;

        // Reset x & y
        temp_x = (x_coord * cos(angle)) - (y_coord * sin(angle));
        temp_y = (x_coord * sin(angle)) + (y_coord * cos(angle));

        x_coord = temp_x;
        y_coord = temp_y;
    }

    this->object = create3DObject(GL_TRIANGLES, 23 * 20, vertex_buffer_data, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP)
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

void Bomb::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick()
{
    this->position.x += this->speed * sin(this->rotation_y * M_PI / 180.0);
    if(this->gravity < 0.6)
    {
        this->gravity += 0.02;
    }
    this->position.y -= this->gravity;
    this->position.z += this->speed * cos(this->rotation_y * M_PI / 180.0);;
    this->set_position(this->position.x, this->position.y, this->position.z);
}