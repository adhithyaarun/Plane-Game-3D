#include "shape.h"
#include "main.h"

/************************************** 
                CIRCLE
**************************************/
Circle::Circle(float x, float y, float r, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->radius = r;

    this->boundary.x = this->position.x;
    this->boundary.y = this->position.y;
    this->boundary.width = this->radius;
    this->boundary.height = this->radius;

    const float poly_angle = 360.0 / 20;
    const float poly_rad = (poly_angle * 3.14159) / 180.0;

    GLfloat vertex_buffer_data[9 * 20];

    float x_coord = this->radius;
    float y_coord = 0.0;
    float temp_x = 0.0;
    float temp_y = 0.0;

    for (int i = 0; i < 3 * 20; ++i)
    {
        if (i < 3 * 20)
        {
            if (i % 3 == 0)
            {
                vertex_buffer_data[3 * i] = 0.0;
                vertex_buffer_data[3 * i + 1] = 0.0;
                vertex_buffer_data[3 * i + 2] = 0.0;
            }
            else
            {
                vertex_buffer_data[3 * i] = x_coord;
                vertex_buffer_data[3 * i + 1] = y_coord;
                vertex_buffer_data[3 * i + 2] = 0.0;
                if ((i + 1) % 3 != 0)
                {
                    temp_x = (x_coord * cos(poly_rad)) - (y_coord * sin(poly_rad));
                    temp_y = (x_coord * sin(poly_rad)) + (y_coord * cos(poly_rad));
                    x_coord = temp_x;
                    y_coord = temp_y;
                }
            }
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 20 * 3, vertex_buffer_data, color, GL_FILL);
}

Circle::Circle(float x, float y, float z, float r, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle_z;
    this->rotation_x = angle_x;
    this->rotation_y = angle_y;

    this->radius = r;

    this->boundary.x = this->position.x;
    this->boundary.y = this->position.y;
    this->boundary.width = this->radius;
    this->boundary.height = this->radius;

    const float poly_angle = 360.0 / 20;
    const float poly_rad = (poly_angle * 3.14159) / 180.0;

    GLfloat vertex_buffer_data[9 * 20];

    float x_coord = this->radius;
    float y_coord = 0.0;
    float temp_x = 0.0;
    float temp_y = 0.0;

    for (int i = 0; i < 3 * 20; ++i)
    {
        if (i < 3 * 20)
        {
            if (i % 3 == 0)
            {
                vertex_buffer_data[3 * i] = 0.0;
                vertex_buffer_data[3 * i + 1] = 0.0;
                vertex_buffer_data[3 * i + 2] = 0.0;
            }
            else
            {
                vertex_buffer_data[3 * i] = x_coord;
                vertex_buffer_data[3 * i + 1] = y_coord;
                vertex_buffer_data[3 * i + 2] = 0.0;
                if ((i + 1) % 3 != 0)
                {
                    temp_x = (x_coord * cos(poly_rad)) - (y_coord * sin(poly_rad));
                    temp_y = (x_coord * sin(poly_rad)) + (y_coord * cos(poly_rad));
                    x_coord = temp_x;
                    y_coord = temp_y;
                }
            }
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 20 * 3, vertex_buffer_data, color, GL_FILL);
}

void Circle::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    /* No need as coordinates centered at (0, 0, 0) of the cube around which we want to rotate. */
    // rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate_x * rotate_y);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Circle::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Circle::tick()
{
    ;
}

/************************************** 
              RECTANGLE
**************************************/
Rectangle::Rectangle(float x, float y, float z, float l, float b, float angle, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = angle;

    this->length = l;
    this->breadth = b;

    this->boundary.width = this->length;
    this->boundary.height = this->breadth;

    GLfloat vertex_buffer_data[] = { 
        -l/2.0, b/2.0, 0.0,
        -l/2.0,-b/2.0, 0.0,
           0.0,-b/2.0, 0.0,

           0.0, b/2.0, 0.0,
        -l/2.0, b/2.0, 0.0,
           0.0,-b/2.0, 0.0,

           0.0, b/2.0, 0.0,
           0.0,-b/2.0, 0.0,
         l/2.0,-b/2.0, 0.0,
         
         l/2.0, b/2.0, 0.0,
           0.0, b/2.0, 0.0,
         l/2.0,-b/2.0, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, color, GL_FILL);
}

Rectangle::Rectangle(float x, float y, float z, float l, float b, float angle_x, float angle_y, float angle_z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = angle_z;
    this->rotation_y = angle_y;
    this->rotation_x = angle_x;

    this->length = l;
    this->breadth = b;

    this->boundary.width = this->length;
    this->boundary.height = this->breadth;

    GLfloat vertex_buffer_data[] = { 
        -l/2.0, b/2.0, 0.0,
        -l/2.0,-b/2.0, 0.0,
           0.0,-b/2.0, 0.0,

           0.0, b/2.0, 0.0,
        -l/2.0, b/2.0, 0.0,
           0.0,-b/2.0, 0.0,

           0.0, b/2.0, 0.0,
           0.0,-b/2.0, 0.0,
         l/2.0,-b/2.0, 0.0,
         
         l/2.0, b/2.0, 0.0,
           0.0, b/2.0, 0.0,
         l/2.0,-b/2.0, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, color, GL_FILL);
}

void Rectangle::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    /* No need as coordinates centered at (0, 0, 0) of the cube around which we want to rotate. */
    // rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate_x * rotate_y);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rectangle::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, this->position.z);
    this->boundary.x = this->position.x;
    this->boundary.y = this->position.y;
}

void Rectangle::tick()
{
    ;
}

