#include "main.h"
#include "parachute.h"

Parachute::Parachute(float x, float y, float z, float r_inner, float width, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);

    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    this->shot_down = false;

    this->r_inner = r_inner;
    this->r_outer = r_inner + width;

    GLfloat vertex_buffer_data[1500];
    GLfloat vertex_buffer_data_strings[20];

    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    float aggr_angle = 2 * angle;

    int iteration_size = 72;

    vertex_buffer_data_strings[0] = this->r_inner * cos(aggr_angle - angle);
    vertex_buffer_data_strings[1] = this->r_inner * sin(aggr_angle - angle);
    vertex_buffer_data_strings[2] = -1.0;

    vertex_buffer_data_strings[3] = this->r_inner * cos(aggr_angle - angle);
    vertex_buffer_data_strings[4] = this->r_inner * sin(aggr_angle - angle);
    vertex_buffer_data_strings[5] = 1.0;

    vertex_buffer_data_strings[6] = 0.0;
    vertex_buffer_data_strings[7] = -this->r_outer;
    vertex_buffer_data_strings[8] = 0.0;

    for (int i = 0; i < 8; ++i)
    {
        // Front
        vertex_buffer_data[i * iteration_size + 0] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 1] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 2] = -1.0;

        vertex_buffer_data[i * iteration_size + 3] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 4] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 5] = -1.0;

        vertex_buffer_data[i * iteration_size + 6] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 7] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 8] = -1.0;

        vertex_buffer_data[i * iteration_size + 9] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 10] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 11] = -1.0;

        vertex_buffer_data[i * iteration_size + 12] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 13] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 14] = -1.0;

        vertex_buffer_data[i * iteration_size + 15] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 16] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 17] = -1.0;

        // Back
        vertex_buffer_data[i * iteration_size + 18] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 19] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 20] = 1.0;

        vertex_buffer_data[i * iteration_size + 21] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 22] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 23] = 1.0;

        vertex_buffer_data[i * iteration_size + 24] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 25] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 26] = 1.0;

        vertex_buffer_data[i * iteration_size + 27] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 28] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 29] = 1.0;

        vertex_buffer_data[i * iteration_size + 30] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 31] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 32] = 1.0;

        vertex_buffer_data[i * iteration_size + 33] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 34] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 35] = 1.0;

        // Joining
        vertex_buffer_data[i * iteration_size + 36] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 37] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 38] = -1.0;

        vertex_buffer_data[i * iteration_size + 39] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 40] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 41] = 1.0;

        vertex_buffer_data[i * iteration_size + 42] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 43] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 44] = -1.0;

        vertex_buffer_data[i * iteration_size + 45] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 46] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 47] = -1.0;

        vertex_buffer_data[i * iteration_size + 48] = this->r_inner * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 49] = this->r_inner * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 50] = 1.0;

        vertex_buffer_data[i * iteration_size + 51] = this->r_inner * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 52] = this->r_inner * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 53] = 1.0;

        vertex_buffer_data[i * iteration_size + 54] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 55] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 56] = -1.0;

        vertex_buffer_data[i * iteration_size + 57] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 58] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 59] = 1.0;

        vertex_buffer_data[i * iteration_size + 60] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 61] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 62] = -1.0;

        vertex_buffer_data[i * iteration_size + 63] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 64] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 65] = -1.0;

        vertex_buffer_data[i * iteration_size + 66] = this->r_outer * cos(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 67] = this->r_outer * sin(aggr_angle - angle);
        vertex_buffer_data[i * iteration_size + 68] = 1.0;

        vertex_buffer_data[i * iteration_size + 69] = this->r_outer * cos(aggr_angle);
        vertex_buffer_data[i * iteration_size + 70] = this->r_outer * sin(aggr_angle);
        vertex_buffer_data[i * iteration_size + 71] = 1.0;

        aggr_angle += angle;
    }

    vertex_buffer_data_strings[9] = this->r_inner * cos(aggr_angle - angle);
    vertex_buffer_data_strings[10] = this->r_inner * sin(aggr_angle - angle);
    vertex_buffer_data_strings[11] = -1.0;

    vertex_buffer_data_strings[12] = this->r_inner * cos(aggr_angle - angle);
    vertex_buffer_data_strings[13] = this->r_inner * sin(aggr_angle - angle);
    vertex_buffer_data_strings[14] = 1.0;

    vertex_buffer_data_strings[15] = 0.0;
    vertex_buffer_data_strings[16] = -this->r_outer;
    vertex_buffer_data_strings[17] = 0.0;

    vertex_buffer_data[594 - 18] = 0.0;
    vertex_buffer_data[595 - 18] = -this->r_outer;
    vertex_buffer_data[596 - 18] = 0.0;
    
    vertex_buffer_data[597 - 18] = 0.3;
    vertex_buffer_data[598 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[599 - 18] = 0.3;
    
    vertex_buffer_data[600 - 18] = -0.3;
    vertex_buffer_data[601 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[602 - 18] = 0.3;

    vertex_buffer_data[603 - 18] = 0.0;
    vertex_buffer_data[604 - 18] = -this->r_outer;
    vertex_buffer_data[605 - 18] = 0.0;

    vertex_buffer_data[606 - 18] = 0.3;
    vertex_buffer_data[607 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[608 - 18] = -0.3;
    
    vertex_buffer_data[609 - 18] = -0.3;
    vertex_buffer_data[610 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[611 - 18] = -0.3;
    
    vertex_buffer_data[612 - 18] = 0.0;
    vertex_buffer_data[613 - 18] = -this->r_outer;
    vertex_buffer_data[614 - 18] = 0.0;

    vertex_buffer_data[615 - 18] = 0.3;
    vertex_buffer_data[616 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[617 - 18] = -0.3;
    
    vertex_buffer_data[618 - 18] = 0.3;
    vertex_buffer_data[619 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[620 - 18] = 0.3;
    
    vertex_buffer_data[621 - 18] = 0.0;
    vertex_buffer_data[622 - 18] = -this->r_outer;
    vertex_buffer_data[623 - 18] = 0.0;

    vertex_buffer_data[624 - 18] = -0.3;
    vertex_buffer_data[625 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[626 - 18] = -0.3;
    
    vertex_buffer_data[627 - 18] = -0.3;
    vertex_buffer_data[628 - 18] = -this->r_outer - 0.3;
    vertex_buffer_data[629 - 18] = 0.3;

    this->object = create3DObject(GL_TRIANGLES, 8 * 24 + 12, vertex_buffer_data, color, GL_FILL);
    this->strings = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_strings, color, GL_LINE);
}

void Parachute::draw(glm::mat4 VP)
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
    draw3DObject(this->strings);
}

void Parachute::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick()
{
    if(this->position.y >= -348.8)
    {
        this->position.y -= 0.08;
    }
    
}