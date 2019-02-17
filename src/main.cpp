#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "dashboard.h"
#include "shape.h"
#include "checkpoint.h"
#include "arrow.h"
#include "fuelup.h"
#include "volcano.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Jet jet;
Dashboard dashboard;
Circle sea;
Arrow arrow;
int arrow_pos = 0;

view_t view_options[5];
coord_t plane_pos;

FuelUp fuelups[5];
Checkpoint checkpoints[8];
Volcano volcanoes[6];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    plane_pos.x = jet.position.x;
    plane_pos.y = jet.position.y;
    plane_pos.z = jet.position.z;

    switch(current_view)
    {
        case 0:
            view_options[0].target.x = jet.position.x;
            view_options[0].target.y = jet.position.y;
            view_options[0].target.z = jet.position.z;
            break;
        case 1:
            view_options[1].eye.x = jet.position.x;
            view_options[1].eye.y = jet.position.y + 15.0;
            view_options[1].eye.z = jet.position.z;

            view_options[1].target.x = jet.position.x;
            view_options[1].target.y = jet.position.y;
            view_options[1].target.z = jet.position.z;

            view_options[1].up.x = 0.0;
            view_options[1].up.y = 0.0;
            view_options[1].up.z = 1.0;
            break;
        case 2:
            view_options[2].eye.x = jet.position.x - 10.0 * sin(jet.rotation_y * M_PI / 180.0);
            view_options[2].eye.y = jet.position.y + 3.0;
            view_options[2].eye.z = jet.position.z - 10.0 * cos(jet.rotation_y * M_PI / 180.0);

            view_options[2].target.x = jet.position.x;
            view_options[2].target.y = jet.position.y;
            view_options[2].target.z = jet.position.z;

            view_options[2].up.x = 0.0;
            view_options[2].up.y = 1.0;
            view_options[2].up.z = 0.0;
            break;
        case 3:
            view_options[3].eye.x = jet.position.x + 0.5 * sin(jet.rotation_y * M_PI / 180.0);
            view_options[3].eye.y = jet.position.y + 2.0;
            view_options[3].eye.z = jet.position.z + 0.5 * cos(jet.rotation_y * M_PI / 180.0);

            view_options[3].target.x = jet.position.x + 50 * sin(jet.rotation_y * M_PI / 180.0);
            view_options[3].target.y = jet.position.y + 1 * cos(jet.rotation_x * M_PI / 180.0);
            view_options[3].target.z = jet.position.z + 50 * cos(jet.rotation_y * M_PI / 180.0);

            view_options[3].up.x = 0.0;
            view_options[3].up.y = 1.0;
            view_options[3].up.z = 0.0;
            break;
        case 4:
            view_options[4].up.x = 0.0;
            view_options[4].up.y = 1.0;
            view_options[4].up.z = 0.0;
            
            view_options[4].target.x = jet.position.x;
            view_options[4].target.y = jet.position.y;
            view_options[4].target.z = jet.position.z;

            track_cursor(window, 600, 600);
            break;
    }

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(view_options[current_view].eye.x, view_options[current_view].eye.y, view_options[current_view].eye.z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(view_options[current_view].target.x, view_options[current_view].target.y, view_options[current_view].target.z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(view_options[current_view].up.x, view_options[current_view].up.y, view_options[current_view].up.z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY jet

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    dashboard.draw(VP);
    sea.draw(VP);
    arrow.draw(VP);

    for(int i=0; i<8 ; ++i)
    {
        checkpoints[i].draw(VP);
    }

    for(int i=0; i<jet.missiles.size(); ++i)
    {
        jet.missiles[i].draw(VP);
    }
    
    for(int i=0; i<jet.bombs.size(); ++i)
    {
        jet.bombs[i].draw(VP);
    }

    for(int i=0; i<5; ++i)
    {
        if(!fuelups[i].collected)
        {
            fuelups[i].draw(VP);
        }
    }

    for(int i=0; i<6; ++i)
    {
        volcanoes[i].draw(VP);
    }

    jet.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int yaw_left  = glfwGetKey(window, GLFW_KEY_Q);
    int yaw_right = glfwGetKey(window, GLFW_KEY_E);
    
    int pitch_up = glfwGetKey(window, GLFW_KEY_UP);
    int pitch_down = glfwGetKey(window, GLFW_KEY_DOWN);

    int roll_left = glfwGetKey(window, GLFW_KEY_A);
    int roll_right = glfwGetKey(window, GLFW_KEY_D);

    int accelerate = glfwGetKey(window, GLFW_KEY_W);
    int decelerate = glfwGetKey(window, GLFW_KEY_S);

    if(pitch_up) 
    {
        if(jet.rotation_x >= -24.0)
        {
            jet.rotation_x -= 0.5;
        }
        jet.position.y += 0.2;
    }
    if(pitch_down) 
    {
        if(jet.rotation_x <= 24.0)
        {
            jet.rotation_x += 0.5;
        }    
        jet.position.y -= 0.2;
    }
    if(yaw_left)
    {
        jet.rotation_y += 0.8;
        // Roll
        if(jet.rotation_z >= -59.5)
        {
            jet.rotation_z -= 0.5;
        }
    }
    if(yaw_right)
    {
        jet.rotation_y -= 0.8;
        // Roll
        if(jet.rotation_z <= 59.5)
        {
            jet.rotation_z += 0.5;
        }
    }
    if(roll_left)
    {
        if(jet.rotation_z >= -89.0)
        {
            jet.rotation_z -= 1.0;
        }
    }
    if(roll_right)
    {
        if(jet.rotation_z <= 89.0)
        {
            jet.rotation_z += 1.0;
        }
    }

    if(accelerate)
    {
        jet.accelerate();
    }
    else if(decelerate)
    {
        jet.decelerate();
    }

    if(!pitch_up && !pitch_down)
    {
        jet.stabilize_x();
    }
    if(!roll_right && !roll_left && !yaw_left && !yaw_right)
    {
        jet.stabilize_z();
    }
}

void tick_elements() 
{
    jet.tick();
    arrow.set_angle(90.0, jet.rotation_y, jet.rotation_z);
    // Collision detection
    double distance = 0.0;
    for(int i=0; i<8; ++i)
    {
        if(arrow_pos == i)
        {
            distance = sqrt(pow(jet.position.x - checkpoints[i].position.x, 2) + pow(jet.position.y - checkpoints[i].position.y, 2) + pow(jet.position.z - checkpoints[i].position.z, 2));
            if(abs(distance) < 4.0)
            {
                checkpoints[i].complete(COLOR_GREEN);
                arrow_pos++;
                arrow.set_position(checkpoints[arrow_pos].position.x,
                                checkpoints[arrow_pos].position.y + checkpoints[arrow_pos].r_outer + 12.0,
                                checkpoints[arrow_pos].position.z);
            }
        }
    }

    for(int i=0; i<5; ++i)
    {
        distance = sqrt(pow(jet.position.x - fuelups[i].position.x, 2) + pow(jet.position.y - fuelups[i].position.y, 2) + pow(jet.position.z - fuelups[i].position.z, 2));
        if(abs(distance) < 4.0)
        {
            fuelups[i].collected = true;
            dashboard.fuel.refill();
        }
    }

    for(int i=0; i<6; ++i)
    {
        if((abs(jet.position.x - volcanoes[i].position.x) < (volcanoes[i].r_large + 1.5)) && 
           (abs(jet.position.z - volcanoes[i].position.z) < (volcanoes[i].r_large + 1.5)))
        {
            quit(window);
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    jet = Jet(0.0, 0.0, 0.0, COLOR_RED);
    dashboard = Dashboard(2.0, 14.0, -18.0);
    sea = Circle(0.0, -350.0, 0.0, 7000.0, 90.0, 0.0, 0.0, COLOR_BLUE);

    int x_rand = 0.0;
    int y_rand = 0.0;
    int z_rand = 0.0;

    srand(time(0));
    for(int i=0; i<6; ++i)
    {
        if(i == 0)
        {
            x_rand = (rand() % 350);
            z_rand = (rand() % 350);
        }
        else
        {
            x_rand = ((rand() % 550) + volcanoes[i-1].position.x + 205.0) * (rand() % 2 == 0 ? 1 : -1);
            z_rand = ((rand() % 550) + volcanoes[i-1].position.z + 205.0) * (rand() % 2 == 0 ? 1 : -1);
        }
        
        volcanoes[i] = Volcano(x_rand, -350.0, z_rand, 28.0, 12.0, 32.0, 90.0, 0.0, 0.0, COLOR_BROWN);
    }

    for(int i=0; i<8 ; ++i)
    {
        if(i == 0)
        {
            checkpoints[i] = Checkpoint(fmod(rand(), 100.0), fmod(rand(), 100.0), fmod(rand(), 100.0), 8.0, 1.0, 0.0, fmod(rand(), 360.0), 0.0, COLOR_ORANGE);
        }
        else
        {
            checkpoints[i] = Checkpoint(checkpoints[i-1].position.x + (rand() % 2 == 0 ? 1 : -1) * (100.0 + fmod(rand(), 200.0)), // X-coordinate
                                        fmod(checkpoints[i-1].position.y + (rand() % 2 == 0 ? 1 : -1) * (fmod(rand(), 100.0)), 348.0), // Y-coordinate
                                        checkpoints[i-1].position.z + (rand() % 2 == 0 ? 1 : -1) * (100.0 + fmod(rand(), 200.0)), // Z-coordinate
                                        8.0,                                               // Inner radius
                                        1.0,                                               // Width
                                        0.0,                                               // Angle along X 
                                        fmod(rand(), 360.0),                               // Angle along Y
                                        0.0,                                               // Angle along Z
                                        COLOR_ORANGE);                                     // Colour
        }
    }
    
    for(int i=0; i<5; ++i)
    {
        if(i == 0)
        {
            x_rand = ((rand() % 200) + jet.position.x) * (rand() % 2 == 0 ? 1 : -1);
            y_rand = ((rand() % 200) + jet.position.y) * (rand() % 2 == 0 ? 1 : -1);
            z_rand = fmod(((rand() % 50) + jet.position.z) * (rand() % 2 == 0 ? 1 : -1), 348.0);
        }
        else
        {
            x_rand = ((rand() % 200) + x_rand) * (rand() % 2 == 0 ? 1 : -1);
            y_rand = ((rand() % 200) + y_rand) * (rand() % 2 == 0 ? 1 : -1);
            z_rand = fmod(((rand() % 50) + z_rand) * (rand() % 2 == 0 ? 1 : -1), 348.0);
        }

        fuelups[i] = FuelUp(x_rand, y_rand, z_rand, jet.rotation_x, jet.rotation_y, jet.rotation_z, COLOR_GREEN);
    }

    arrow = Arrow(checkpoints[0].position.x, 
                  checkpoints[0].position.y + checkpoints[0].r_outer + 12.0,
                  checkpoints[0].position.z,
                  90.0,
                  jet.rotation_y,
                  jet.rotation_z,
                  COLOR_RED);

    view_options[0].eye.x = 0.0;
    view_options[0].eye.y = 16.0;
    view_options[0].eye.z = -20.0;

    view_options[0].target.x = 0.0;
    view_options[0].target.y = 0.0;
    view_options[0].target.z = 0.0;

    view_options[0].up.x = 0.0;
    view_options[0].up.y = 1.0;
    view_options[0].up.z = 0.0;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void fire_missile()
{
    jet.fire_missile();
}

void drop_bomb()
{
    jet.drop_bomb();
}

void reset_screen() {
    // float bottom = screen_center_y - 20 / screen_zoom;
    // float left   = screen_center_x - 20 / screen_zoom;
    // float right  = screen_center_x + 20 / screen_zoom;
    // float top    = screen_center_y + 20 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(90.0), 1.0, 0.1, 5000.0);
}
