#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;
int current_view = 0;
double x_initial = -1.0;
double y_initial = -1.0;
float radius = 15.0;
float theta = 60.0 * M_PI / 180.0;
float phi = 60.0 * M_PI / 180.0;
float cur_angle_theta = 0.0;
float cur_angle_phi = 0.0;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        // quit(window);
        break;
    case 'R':
    case 'r':
        if(current_view == 4)
        {
            x_initial = -1.0;
            y_initial = -1.0;
            radius = 15.0;
            theta = 60.0 * M_PI / 180.0;
            phi = 60.0 * M_PI / 180.0;
            cur_angle_theta = 0.0;
            cur_angle_phi = 0.0;
            
            view_options[4].eye.x = plane_pos.x + radius * sin(phi) * cos(theta);
            view_options[4].eye.y = plane_pos.y + radius * cos(phi);
            view_options[4].eye.z = plane_pos.z + radius * sin(phi) * sin(theta);
        }
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if(action == GLFW_PRESS) 
        {
            if(current_view == 4)
            {
                glfwGetCursorPos(window, &x_initial, &y_initial);
            }
            // Do something
            return;
        } 
        else if(action == GLFW_RELEASE) 
        {
            if(current_view == 4)
            {
                x_initial = -1.0;
                y_initial = -1.0;
                
                theta = fmod(theta + cur_angle_theta, 360.0);
                cur_angle_theta = 0.0;
                
                phi = fmod(phi + cur_angle_phi, 360.0);
                cur_angle_phi = 0.0;
            }
            // Do something
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action == GLFW_PRESS) 
        {
            // Do something
        }
        else if(action == GLFW_RELEASE) 
        {
            // Do something
        }
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        if(action == GLFW_PRESS)
        {
            current_view = (current_view + 1) % 5;
            if(current_view == 4)
            {
                view_options[4].eye.x = plane_pos.x + radius * sin(phi) * cos(theta);
                view_options[4].eye.y = plane_pos.y + radius * cos(phi);
                view_options[4].eye.z = plane_pos.z + radius * sin(phi) * sin(theta);
            }
            else
            {
                x_initial = -1.0;
                y_initial = -1.0;
            }
            
        }
        else if(action == GLFW_RELEASE)
        {
            // Do something
        }
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) 
{
    if(current_view == 4 && x_initial < 0.0 && y_initial < 0.0)
    {
        if(yoffset > 0 && radius > 7.0)
        {
            radius -= 1.0;
        }
        else if(yoffset < 0 && radius < 25.0)
        {
            radius += 1.0;
        }
        view_options[4].eye.x = plane_pos.x + radius * sin(phi) * cos(theta);
        view_options[4].eye.y = plane_pos.y + radius * cos(phi);
        view_options[4].eye.z = plane_pos.z + radius * sin(phi) * sin(theta);
    }
}

void track_cursor(GLFWwindow *window, int width, int height)
{
    double x_final, y_final;
    glfwGetCursorPos(window, &x_final, &y_final);

    float dx = (x_final - x_initial);
    float dy = (y_final - y_initial);
    float angle_plane = 0.0;
    float angle_vertical = 0.0;
    

    if(x_initial >= 0.0 && y_initial >= 0.0)
    {
        cur_angle_theta = atan(((abs(dx) / 10.0) / (2 * M_PI * radius)) * 2 * M_PI) * dx / abs(dx);
        cur_angle_phi = atan(((abs(dy) / 10.0) / (2 * M_PI * radius)) * 2 * M_PI) * dy / abs(dy) * (-1);

        angle_plane = fmod(theta + cur_angle_theta, 360.0);
        angle_vertical = fmod(phi + cur_angle_phi, 360.0);

        view_options[4].eye.x = plane_pos.x + radius * cos(angle_plane) * sin(angle_vertical);
        view_options[4].eye.y = plane_pos.y + radius * cos(angle_vertical);
        view_options[4].eye.z = plane_pos.z + radius * sin(angle_plane) * sin(angle_vertical);
    }
    else
    {
        view_options[4].eye.x = plane_pos.x + radius * sin(phi) * cos(theta);
        view_options[4].eye.y = plane_pos.y + radius * cos(phi);
        view_options[4].eye.z = plane_pos.z + radius * sin(phi) * sin(theta);
    }
    
}