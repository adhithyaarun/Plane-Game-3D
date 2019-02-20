#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;

    static GLfloat vertex_buffer_data_inner[200];
    static GLfloat vertex_buffer_data_outer[200];
    static GLfloat vertex_buffer_data_pointer_r[10];
    static GLfloat vertex_buffer_data_pointer_b[10];

    this->r_outer = 4.0;
    this->r_inner = 3.5;
    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    float aggr_angle = angle;

    int iteration_size = 9;

    for (int i = 0; i < 20; ++i)
    {
        vertex_buffer_data_outer[i * iteration_size + 0] = this->r_outer * cos(aggr_angle);        
        vertex_buffer_data_outer[i * iteration_size + 1] = this->r_outer * sin(aggr_angle);        
        vertex_buffer_data_outer[i * iteration_size + 2] = 0.0;

        vertex_buffer_data_outer[i * iteration_size + 3] = 0.0;        
        vertex_buffer_data_outer[i * iteration_size + 4] = 0.0;        
        vertex_buffer_data_outer[i * iteration_size + 5] = 0.0;
                
        vertex_buffer_data_outer[i * iteration_size + 6] = this->r_outer * cos(aggr_angle - angle);        
        vertex_buffer_data_outer[i * iteration_size + 7] = this->r_outer * sin(aggr_angle - angle);        
        vertex_buffer_data_outer[i * iteration_size + 8] = 0.0;

        vertex_buffer_data_inner[i * iteration_size + 0] = this->r_inner * cos(aggr_angle);        
        vertex_buffer_data_inner[i * iteration_size + 1] = this->r_inner * sin(aggr_angle);        
        vertex_buffer_data_inner[i * iteration_size + 2] = 0.0;

        vertex_buffer_data_inner[i * iteration_size + 3] = 0.0;        
        vertex_buffer_data_inner[i * iteration_size + 4] = 0.0;        
        vertex_buffer_data_inner[i * iteration_size + 5] = 0.0;
                
        vertex_buffer_data_inner[i * iteration_size + 6] = this->r_inner * cos(aggr_angle - angle);        
        vertex_buffer_data_inner[i * iteration_size + 7] = this->r_inner * sin(aggr_angle - angle);        
        vertex_buffer_data_inner[i * iteration_size + 8] = 0.0;        

        aggr_angle += angle;
    }

    vertex_buffer_data_pointer_r[0] = 0.0; 
    vertex_buffer_data_pointer_r[1] = 2.8; 
    vertex_buffer_data_pointer_r[2] = 0.0;

    vertex_buffer_data_pointer_r[3] = -0.5; 
    vertex_buffer_data_pointer_r[4] = 0.0; 
    vertex_buffer_data_pointer_r[5] = 0.0;
    
    vertex_buffer_data_pointer_r[6] = 0.5;
    vertex_buffer_data_pointer_r[7] = 0.0; 
    vertex_buffer_data_pointer_r[8] = 0.0;
    
    vertex_buffer_data_pointer_b[0] = 0.0; 
    vertex_buffer_data_pointer_b[1] = -2.8; 
    vertex_buffer_data_pointer_b[2] = 0.0;

    vertex_buffer_data_pointer_b[3] = 0.5; 
    vertex_buffer_data_pointer_b[4] = 0.0; 
    vertex_buffer_data_pointer_b[5] = 0.0;
    
    vertex_buffer_data_pointer_b[6] = -0.5;
    vertex_buffer_data_pointer_b[7] = 0.0; 
    vertex_buffer_data_pointer_b[8] = 0.0;

    this->outer = create3DObject(GL_TRIANGLES, 3 * 20, vertex_buffer_data_outer, color, GL_FILL);
    this->inner = create3DObject(GL_TRIANGLES, 3 * 20, vertex_buffer_data_inner, COLOR_WHITE, GL_FILL);
    this->pointer_red = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_pointer_r, COLOR_RED, GL_FILL);
    this->pointer_black = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_pointer_b, COLOR_BLACK, GL_FILL);
}

void Compass::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->outer);
    draw3DObject(this->inner);
    Matrices.model *= (rotate_y * rotate_x * rotate_z);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->pointer_red);
    draw3DObject(this->pointer_black);
}

void Compass::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Compass::set_angle(float angle_x, float angle_y, float angle_z)
{
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;
    this->rotation_z = angle_z;
}

void Compass::tick(float angle)
{
    this->rotation_z = fmod(angle, 360.0);
}