#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, float r_large, float r_small, float height, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    static GLfloat vertex_buffer_data[750];

    this->r_large = r_large;
    this->r_small = r_small;
    this->height = height;
    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    float aggr_angle = angle;

    int iteration_size = 36;

    for (int i = 0; i < 20; ++i)
    {
        // Base
        vertex_buffer_data[i * iteration_size + 0] = this->r_large * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 1] = this->r_large * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 2] = 0.0;

        vertex_buffer_data[i * iteration_size + 3] = 0.0;
        vertex_buffer_data[i * iteration_size + 4] = 0.0;
        vertex_buffer_data[i * iteration_size + 5] = 0.0;

        vertex_buffer_data[i * iteration_size + 6] = this->r_large * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 7] = this->r_large * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 8] = 0.0;
        
        // Top
        vertex_buffer_data[i * iteration_size + 9] = this->r_small * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 10] = this->r_small * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 11] = -this->height;

        vertex_buffer_data[i * iteration_size + 12] = 0.0;
        vertex_buffer_data[i * iteration_size + 13] = 0.0;
        vertex_buffer_data[i * iteration_size + 14] = 0.0;

        vertex_buffer_data[i * iteration_size + 15] = this->r_small * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 16] = this->r_small * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 17] = -this->height;
        
        // Join
        vertex_buffer_data[i * iteration_size + 18] = this->r_large * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 19] = this->r_large * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 20] = 0.0;
        
        vertex_buffer_data[i * iteration_size + 21] = this->r_small * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 22] = this->r_small * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 23] = -this->height;
        
        vertex_buffer_data[i * iteration_size + 24] = this->r_small * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 25] = this->r_small * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 26] = -this->height;
        
        vertex_buffer_data[i * iteration_size + 27] = this->r_large * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 28] = this->r_large * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 29] = 0.0;

        vertex_buffer_data[i * iteration_size + 30] = this->r_large * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 31] = this->r_large * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 32] = 0.0;

        vertex_buffer_data[i * iteration_size + 33] = this->r_small * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 34] = this->r_small * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 35] = -this->height;

        aggr_angle += angle;
    }

    this->object = create3DObject(GL_TRIANGLES, 12 * 20, vertex_buffer_data, color, GL_FILL);
}

void Volcano::draw(glm::mat4 VP)
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

void Volcano::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Volcano::set_angle(float angle_x, float angle_y, float angle_z)
{
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
}

void Volcano::tick()
{
    ;
}

// Island
Island::Island(float x, float y, float z, float size, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    GLfloat vertex_buffer_data[750];
    
    int side = 8 + (float)(rand() % 13);

    float angle = ((360.0 / ((float)side)) * M_PI) / 180.0;
    float aggr_angle = angle;

    int iteration_size = 9;

    int index = 0;

    for (int i = 0; i < side; ++i)
    {
        // Base
        vertex_buffer_data[i * iteration_size + 0] = size * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 1] = size * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 2] = 0.0;

        vertex_buffer_data[i * iteration_size + 3] = 0.0;
        vertex_buffer_data[i * iteration_size + 4] = 0.0;
        vertex_buffer_data[i * iteration_size + 5] = 0.0;

        vertex_buffer_data[i * iteration_size + 6] = size * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 7] = size * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 8] = 0.0;

        aggr_angle += angle;
        index = i * iteration_size + 9;
    }

    int rand_vertex_1 = 0.0;
    int rand_vertex_2 = 0.0;

    for(int i=0; i<5; ++i)
    {
        rand_vertex_1 = (rand() + (int)size) % side;
        rand_vertex_2 = (rand() + (int)size) % side;

        while(rand_vertex_1 == rand_vertex_2)
        {
            rand_vertex_2 = (rand() + (int)size) % side;
        }

        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_1 * iteration_size + 0];
        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_1 * iteration_size + 1];
        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_1 * iteration_size + 2];

        vertex_buffer_data[index++] = ((vertex_buffer_data[rand_vertex_1 * iteration_size + 0] + vertex_buffer_data[rand_vertex_2 * iteration_size + 0]) / 2.0) + ((size * 2.5) * (rand() % 2 == 0 ? 1 : -1));
        vertex_buffer_data[index++] = ((vertex_buffer_data[rand_vertex_1 * iteration_size + 1] + vertex_buffer_data[rand_vertex_2 * iteration_size + 1]) / 2.0) + ((size * 2.5) * (rand() % 2 == 0 ? 1 : -1));
        vertex_buffer_data[index++] = 0.0;

        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_2 * iteration_size + 0];
        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_2 * iteration_size + 1];
        vertex_buffer_data[index++] = vertex_buffer_data[rand_vertex_2 * iteration_size + 2];
    }

    std::cout << std::endl;


    this->object = create3DObject(GL_TRIANGLES, 3 * (side + 2), vertex_buffer_data, color, GL_FILL);
}

void Island::draw(glm::mat4 VP)
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

void Island::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Island::set_angle(float angle_x, float angle_y, float angle_z)
{
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
}

void Island::tick()
{
    ;
}