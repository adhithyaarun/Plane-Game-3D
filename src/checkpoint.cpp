#include "main.h"
#include "checkpoint.h"

Checkpoint::Checkpoint(float x, float y, float z, float r_inner, float width, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);

    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    this->r_inner = r_inner;
    this->r_outer = r_inner + width;

    GLfloat vertex_buffer_data[1500];

    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    float aggr_angle = angle;

    int iteration_size = 72;

    for (int i = 0; i < 20; ++i)
    {
        // Front
        vertex_buffer_data[i * iteration_size + 0] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 1] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 2] = -0.2;

        vertex_buffer_data[i * iteration_size + 3] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 4] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 5] = -0.2;

        vertex_buffer_data[i * iteration_size + 6] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 7] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 8] = -0.2;
        
        vertex_buffer_data[i * iteration_size + 9] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 10] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 11] = -0.2;

        vertex_buffer_data[i * iteration_size + 12] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 13] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 14] = -0.2;

        vertex_buffer_data[i * iteration_size + 15] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 16] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 17] = -0.2;

        // Back
        vertex_buffer_data[i * iteration_size + 18] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 19] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 20] = 0.2;

        vertex_buffer_data[i * iteration_size + 21] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 22] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 23] = 0.2;

        vertex_buffer_data[i * iteration_size + 24] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 25] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 26] = 0.2;
        
        vertex_buffer_data[i * iteration_size + 27] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 28] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 29] = 0.2;

        vertex_buffer_data[i * iteration_size + 30] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 31] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 32] = 0.2;

        vertex_buffer_data[i * iteration_size + 33] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 34] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 35] = 0.2;

        // Joining
        vertex_buffer_data[i * iteration_size + 36] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 37] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 38] = -0.2;
        
        vertex_buffer_data[i * iteration_size + 39] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 40] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 41] = 0.2;
        
        vertex_buffer_data[i * iteration_size + 42] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 43] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 44] = -0.2;
        
        vertex_buffer_data[i * iteration_size + 45] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 46] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 47] = -0.2;
        
        vertex_buffer_data[i * iteration_size + 48] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 49] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 50] = 0.2;
        
        vertex_buffer_data[i * iteration_size + 51] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 52] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 53] = 0.2;
        
        vertex_buffer_data[i * iteration_size + 54] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 55] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 56] = -0.2;
        
        vertex_buffer_data[i * iteration_size + 57] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 58] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 59] = 0.2;
        
        vertex_buffer_data[i * iteration_size + 60] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 61] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 62] = -0.2;

        vertex_buffer_data[i * iteration_size + 63] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 64] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 65] = -0.2;

        vertex_buffer_data[i * iteration_size + 66] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 67] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 68] = 0.2;

        vertex_buffer_data[i * iteration_size + 69] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 70] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 71] = 0.2;

        aggr_angle += angle;
    }
    this->object = create3DObject(GL_TRIANGLES, 20 * 24, vertex_buffer_data, color, GL_FILL);
}

void Checkpoint::complete(color_t color)
{
    GLfloat vertex_buffer_data[1500];

    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    float aggr_angle = angle;

    int iteration_size = 72;

    for (int i = 0; i < 20; ++i)
    {
        // Front
        vertex_buffer_data[i * iteration_size + 0] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 1] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 2] = -0.2;

        vertex_buffer_data[i * iteration_size + 3] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 4] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 5] = -0.2;

        vertex_buffer_data[i * iteration_size + 6] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 7] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 8] = -0.2;

        vertex_buffer_data[i * iteration_size + 9] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 10] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 11] = -0.2;

        vertex_buffer_data[i * iteration_size + 12] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 13] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 14] = -0.2;

        vertex_buffer_data[i * iteration_size + 15] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 16] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 17] = -0.2;

        // Back
        vertex_buffer_data[i * iteration_size + 18] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 19] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 20] = 0.2;

        vertex_buffer_data[i * iteration_size + 21] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 22] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 23] = 0.2;

        vertex_buffer_data[i * iteration_size + 24] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 25] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 26] = 0.2;

        vertex_buffer_data[i * iteration_size + 27] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 28] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 29] = 0.2;

        vertex_buffer_data[i * iteration_size + 30] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 31] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 32] = 0.2;

        vertex_buffer_data[i * iteration_size + 33] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 34] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 35] = 0.2;

        // Joining
        vertex_buffer_data[i * iteration_size + 36] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 37] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 38] = -0.2;

        vertex_buffer_data[i * iteration_size + 39] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 40] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 41] = 0.2;

        vertex_buffer_data[i * iteration_size + 42] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 43] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 44] = -0.2;

        vertex_buffer_data[i * iteration_size + 45] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 46] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 47] = -0.2;

        vertex_buffer_data[i * iteration_size + 48] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 49] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 50] = 0.2;

        vertex_buffer_data[i * iteration_size + 51] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 52] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 53] = 0.2;

        vertex_buffer_data[i * iteration_size + 54] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 55] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 56] = -0.2;

        vertex_buffer_data[i * iteration_size + 57] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 58] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 59] = 0.2;

        vertex_buffer_data[i * iteration_size + 60] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 61] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 62] = -0.2;

        vertex_buffer_data[i * iteration_size + 63] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 64] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 65] = -0.2;

        vertex_buffer_data[i * iteration_size + 66] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 67] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 68] = 0.2;

        vertex_buffer_data[i * iteration_size + 69] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 70] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 71] = 0.2;

        aggr_angle += angle;
    }
    this->object = create3DObject(GL_TRIANGLES, 20 * 24, vertex_buffer_data, color, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP)
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
}

void Checkpoint::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick()
{
    ;
}