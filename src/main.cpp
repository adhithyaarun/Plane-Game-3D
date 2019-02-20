#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "dashboard.h"
#include "shape.h"
#include "checkpoint.h"
#include "arrow.h"
#include "fuelup.h"
#include "volcano.h"
#include "parachute.h"
#include "cannon.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Dashboard_Matrices;
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

FuelUp fuelups[10];
Checkpoint checkpoints[8];
vector<Checkpoint> smoke;
Volcano volcanoes[6];
Island islands[24];
vector<Parachute> parachutes;
vector<Cannon> cannons;

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
    
    glm::vec3 dashboard_eye(0.0, 0.0, 0.1);
    glm::vec3 dashboard_target(0.0, 0.0, 0.0);
    glm::vec3 dashboard_up(0.0, 1.0, 0.0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Dashboard_Matrices.view = glm::lookAt( dashboard_eye, dashboard_target, dashboard_up );
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY jet

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 Dashboard_VP = Dashboard_Matrices.projection * Dashboard_Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0; i<smoke.size(); ++i)
    {
        smoke[i].draw(VP);
    }

    dashboard.draw(Dashboard_VP);
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

    for(int i=0; i<10; ++i)
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

    for(int i=0; i<parachutes.size(); ++i)
    {
        if(!parachutes[i].shot_down)
        {
            parachutes[i].draw(VP);
        }
    }

    for(int i=0; i<24; ++i)
    {
        islands[i].draw(VP);
    }

    for(int i=0; i<cannons.size(); ++i)
    {
        cannons[i].draw(VP);
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
        jet.rotation_z = fmod(jet.rotation_z - 1.0, 360.0);
    }
    if(roll_right)
    {
        jet.rotation_z = fmod(jet.rotation_z + 1.0, 360.0);
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
    dashboard.tick((jet.position.y + 350.0) * 100.0, jet.speed * 450.0, jet.rotation_y);
    
    if(dashboard.fuel.units < 0 || dashboard.altitude <= 0)
    {
        cout << "You ran out of fuel" << endl;
        quit(window);
    }
    arrow.set_angle(90.0, jet.rotation_y, jet.rotation_z);

    // Collision detection
    // Checkpoint collection
    double distance = 0.0;
    for(int i=0; i<8; ++i)
    {
        if(arrow_pos == i)
        {
            distance = sqrt(pow(jet.position.x - checkpoints[i].position.x, 2) + pow(jet.position.y - checkpoints[i].position.y, 2) + pow(jet.position.z - checkpoints[i].position.z, 2));
            if(abs(distance) < 4.0)
            {
                checkpoints[i].complete(COLOR_GREEN);
                dashboard.score_val += 1000.0;
                arrow_pos++;
                if(arrow_pos >= 8)
                {
                    cout << "You've completed the obstacle course. Great job!" << endl;
                    quit(window);
                }
                arrow.set_position(checkpoints[arrow_pos].position.x,
                                checkpoints[arrow_pos].position.y + checkpoints[arrow_pos].r_outer + 12.0,
                                checkpoints[arrow_pos].position.z);
            }
        }
    }

    // Fuel-up collection
    for(int i=0; i<10; ++i)
    {
        distance = sqrt(pow(jet.position.x - fuelups[i].position.x, 2) + pow(jet.position.y - fuelups[i].position.y, 2) + pow(jet.position.z - fuelups[i].position.z, 2));
        if(abs(distance) < 4.0)
        {
            fuelups[i].collected = true;
            dashboard.fuel.refill();
        }
    }

    // Volcano No Fly Zone
    for(int i=0; i<6; ++i)
    {
        if((abs(jet.position.x - volcanoes[i].position.x) < (volcanoes[i].r_large + 1.5)) && 
           (abs(jet.position.z - volcanoes[i].position.z) < (volcanoes[i].r_large + 1.5)))
        {
            cout << "You flew into a NO FLY zone."<< endl;
            quit(window);
        }
    }

    // Shooting down parachutes
    for(int i=0; i<parachutes.size(); ++i)
    {
        if(!parachutes[i].shot_down)
        {
            for(int j=0; j<jet.missiles.size(); ++j)
            {
                distance = sqrt(sqrt(pow(jet.missiles[j].position.x - parachutes[i].position.x, 2) + pow(jet.missiles[j].position.y - parachutes[i].position.y, 2) + pow(jet.missiles[j].position.z - parachutes[i].position.z, 2)));
                if((abs(jet.missiles[j].position.y - parachutes[i].position.y) < parachutes[i].r_outer) && abs(distance) < 2.0)
                {
                    parachutes[i].shot_down = true;
                    jet.missiles.erase(jet.missiles.begin() + j);
                    dashboard.score_val += 500.0;
                    --j;
                }
            }
            
            for(int j=0; j<jet.bombs.size(); ++j)
            {
                distance = sqrt(sqrt(pow(jet.bombs[j].position.x - parachutes[i].position.x, 2) + pow(jet.bombs[j].position.y - parachutes[i].position.y, 2) + pow(jet.bombs[j].position.z - parachutes[i].position.z, 2)));
                if((abs(jet.bombs[j].position.y - parachutes[i].position.y) < parachutes[i].r_outer) && abs(distance) < 2.0)
                {
                    parachutes[i].shot_down = true;
                    jet.bombs.erase(jet.bombs.begin() + j);
                    dashboard.score_val += 500.0;
                    --j;
                }
            }
        }

        if(!parachutes[i].shot_down)
        {
            parachutes[i].tick();
            if(parachutes[i].position.y <= -345.0)
            {
                parachutes.erase(parachutes.begin() + i);
                --i;
            }
        }
        else
        {
                parachutes.erase(parachutes.begin() + i);
                --i;
        }
        
    }

    // Pass through smoke
    for(int i=0; i<smoke.size(); ++i)
    {
        distance = sqrt(pow(jet.position.x - smoke[i].position.x, 2) + pow(jet.position.y - smoke[i].position.y, 2) + pow(jet.position.z - smoke[i].position.z, 2));
        if(abs(distance) < 4.0)
        {
            smoke.erase(smoke.begin() + i);
            dashboard.score_val += 300.0;
            --i;
        }
        else
        {
            smoke[i].tick();
            if (smoke[i].position.y < -10.0)
            {
                smoke.erase(smoke.begin() + i);
                --i;
            }
        }
    }

    // Cannon shooting
    for (int i = 0; i < cannons.size(); ++i)
    {
        for (int j = 0; j < jet.missiles.size(); ++j)
        {
            distance = sqrt(sqrt(pow(jet.missiles[j].position.x - cannons[i].position.x, 2) + pow(jet.missiles[j].position.y - cannons[i].position.y, 2) + pow(jet.missiles[j].position.z - cannons[i].position.z, 2)));
            if (abs(distance) < 2.0)
            {
                jet.missiles.erase(jet.missiles.begin() + j);
                cannons.erase(cannons.begin() + i);
                --j;
            }
        }

        for (int j = 0; j < jet.bombs.size(); ++j)
        {
            distance = sqrt(sqrt(pow(jet.bombs[j].position.x - cannons[i].position.x, 2) + pow(jet.bombs[j].position.y - cannons[i].position.y, 2) + pow(jet.bombs[j].position.z - cannons[i].position.z, 2)));
            if (abs(distance) < 2.0)
            {
                jet.bombs.erase(jet.bombs.begin() + j);
                cannons.erase(cannons.begin() + i);
                --j;
            }
        }
        
        if(abs(jet.position.x - cannons[i].position.x) < 70.0 &&
           abs(jet.position.z - cannons[i].position.z) < 70.0)
        {
            cannons[i].fire(jet.position.x, jet.position.y, jet.position.z);   
        }
        cannons[i].tick();
        for(int j=0; j<cannons[i].bombs.size(); ++j)
        {
            distance = sqrt(pow(cannons[i].bombs[j].position.x - jet.position.x, 2) +
                            pow(cannons[i].bombs[j].position.y - jet.position.y, 2) +
                            pow(cannons[i].bombs[j].position.z - jet.position.z, 2));
            if(abs(distance) <= 3.0)
            {
                cout << "You got shot by an enemy CANNON" <<endl;
                quit(window);
            }
            else if(abs(distance) > 10.0 && cannons[i].bombs[j].position.y > (jet.position.y + 5.0))
            {
                cannons[i].bombs.erase(cannons[i].bombs.begin() + j);
                --j;
            }
        }
    }


    float x_rand = 0.0;
    float y_rand = 0.0;
    float z_rand = 0.0;

    float x_angle_rand = 0.0;
    float y_angle_rand = 0.0;
    float z_angle_rand = 0.0;

    // Create new parachutes
    while(parachutes.size() < 15)
    {
        x_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + parachutes[parachutes.size() - 1].position.x;
        y_rand = 350.0 + fmod(rand() % 30, 30) * (rand() % 2 == 0 ? 1 : -1);
        z_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + parachutes[parachutes.size() - 1].position.z;

        parachutes.push_back(Parachute(x_rand, y_rand, z_rand, 1.5, 0.01, 0.0, 0.0, 0.0, COLOR_GREEN));
    }

    // Create new smoke
    while(smoke.size() < 5)
    {
        x_rand = jet.position.x + (rand() % 200) * (rand() % 2 == 0 ? 1 : -1);
        z_rand = jet.position.z + (rand() % 200) * (rand() % 2 == 0 ? 1 : -1);
        x_angle_rand = rand() % 360;
        y_angle_rand = rand() % 360;
        z_angle_rand = rand() % 360;
        smoke.push_back(Checkpoint(x_rand, 25.0, z_rand, 8.0, 1.0, x_angle_rand, y_angle_rand, z_angle_rand, COLOR_WHITE));
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    jet = Jet(0.0, -200.0, 0.0, COLOR_RED);
    dashboard = Dashboard(-15.0, -15.0, 0.0);
    sea = Circle(0.0, -350.0, 0.0, 7000.0, 90.0, 0.0, 0.0, COLOR_BLUE);

    int x_rand = 0.0;
    int y_rand = 0.0;
    int z_rand = 0.0;

    srand(time(0));
    // Volcano creation
    for(int i=0; i<6; ++i)
    {
        if(i == 0)
        {
            x_rand = (rand() % 200);
            z_rand = (rand() % 200);
        }
        else
        {
            x_rand = fmod(((rand() % 180) + volcanoes[i-1].position.x + 205.0) * (rand() % 2 == 0 ? 1 : -1), 1600.0);
            z_rand = fmod(((rand() % 180) + volcanoes[i-1].position.z + 205.0) * (rand() % 2 == 0 ? 1 : -1), 1600.0);
        }
        
        volcanoes[i] = Volcano(x_rand, -349.8, z_rand, 36.0, 14.0, 52.0, 90.0, 0.0, 0.0, COLOR_DARK_BROWN);
    }

    // Checkpoint creation
    for(int i=0; i<8 ; ++i)
    {
        if(i == 0)
        {
            checkpoints[i] = Checkpoint(fmod(rand(), 100.0), jet.position.y + fmod(rand(), 100.0), fmod(rand(), 100.0), 8.0, 1.0, 0.0, fmod(rand(), 360.0), 0.0, COLOR_ORANGE);
        }
        else
        {
            checkpoints[i] = Checkpoint(fmod(checkpoints[i-1].position.x + (rand() % 2 == 0 ? 1 : -1) * (100.0 + fmod(rand(), 200.0)), 1400.0), // X-coordinate
                                        fmod(checkpoints[i-1].position.y + (rand() % 2 == 0 ? 1 : -1) * (fmod(rand(), 100.0)), 348.0), // Y-coordinate
                                        fmod(checkpoints[i-1].position.z + (rand() % 2 == 0 ? 1 : -1) * (100.0 + fmod(rand(), 200.0)), 1400.0), // Z-coordinate
                                        8.0,                                               // Inner radius
                                        1.0,                                               // Width
                                        0.0,                                               // Angle along X 
                                        fmod(rand(), 360.0),                               // Angle along Y
                                        0.0,                                               // Angle along Z
                                        COLOR_ORANGE);                                     // Colour
        }
    }
    
    // Fuelup creation
    for(int i=0; i<10; ++i)
    {
        if(i <= 1)
        {
            x_rand = ((rand() % 100) + jet.position.x) * (rand() % 2 == 0 ? 1 : -1);
            y_rand = fmod(((rand() % 50) + jet.position.y) * (rand() % 2 == 0 ? 1 : -1), 348.0);
            z_rand = ((rand() % 100) + jet.position.z) * (rand() % 2 == 0 ? 1 : -1);
        }
        else
        {
            x_rand = ((rand() % 150) + checkpoints[i-2].position.x) * (rand() % 2 == 0 ? 1 : -1);
            y_rand = fmod(((rand() % 50) + y_rand) * (rand() % 2 == 0 ? 1 : -1), 348.0);
            z_rand = ((rand() % 250) + checkpoints[i-2].position.z) * (rand() % 2 == 0 ? 1 : -1);
        }

        fuelups[i] = FuelUp(x_rand, y_rand, z_rand, jet.rotation_x, jet.rotation_y, jet.rotation_z, COLOR_GREEN);
    }

    // Arrow creation
    arrow = Arrow(checkpoints[0].position.x, 
                  checkpoints[0].position.y + checkpoints[0].r_outer + 12.0,
                  checkpoints[0].position.z,
                  90.0,
                  jet.rotation_y,
                  jet.rotation_z,
                  COLOR_RED);

    // Parachute creation
    for(int i=0; i<15; ++i)
    {
        if(i == 0)
        {
            x_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + jet.position.x;
            y_rand = -50.0 + (fmod(rand() % 30, 30)) * (rand() % 2 == 0 ? 1 : -1);
            z_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + jet.position.z;
        }
        else        
        {
            x_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + parachutes[i-1].position.x;
            y_rand = 150.0 + fmod(rand() % 30, 30) * (rand() % 2 == 0 ? 1 : -1);
            z_rand = (rand() % 300) * (rand() % 2 == 0 ? 1 : -1) + parachutes[i-1].position.z;
        }
        parachutes.push_back(Parachute(x_rand, y_rand, z_rand, 1.5, 0.01, 0.0, 0.0, 0.0, COLOR_PURPLE));
    }

    // Island creation, Cannon creation
    for(int i=0; i<24; ++i)
    {
        if(i < 8)
        {
            islands[i] = Island(checkpoints[i].position.x, -349.8, checkpoints[i].position.z, 10.0 + (float)(rand() % 15), 90.0, 0.0, 0.0, COLOR_BROWN);
        }
        else if(i < 14)
        {
            islands[i] = Island(volcanoes[i-8].position.x, -349.8, volcanoes[i-8].position.z, volcanoes[i-8].r_large + (float)(rand() % 15), 90.0, 0.0, 0.0, COLOR_BROWN);
        }
        else
        {
            islands[i] = Island((rand() % 300), -349.8, (rand() % 300), 10.0 + (float)(rand() % 15), 90.0, 0.0, 0.0, COLOR_BROWN);
        }
        
        cannons.push_back(Cannon(islands[i].position.x, -350, islands[i].position.z, 0.50, 0.50, 3.0, 45.0, 0.0, 0.0, COLOR_YELLOW));
    }

    float x_angle_rand = 0.0;
    float y_angle_rand = 0.0;
    float z_angle_rand = 0.0;

    for(int i=0; i<5; ++i)
    {
        x_rand = jet.position.x + (rand() % 200) * (rand() % 2 == 0 ? 1 : -1);
        z_rand = jet.position.z + (rand() % 200) * (rand() % 2 == 0 ? 1 : -1);
        x_angle_rand = rand() % 360;
        y_angle_rand = rand() % 360;
        z_angle_rand = rand() % 360;
        smoke.push_back(Checkpoint(x_rand, 25.0, z_rand, 8.0, 1.0, x_angle_rand, y_angle_rand, z_angle_rand, COLOR_WHITE));
    }

    view_options[0].eye.x = jet.position.x;
    view_options[0].eye.y = jet.position.y + 16.0;
    view_options[0].eye.z = jet.position.z - 20.0;

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
    float bottom = screen_center_y - 20 / screen_zoom;
    float left   = screen_center_x - 20 / screen_zoom;
    float right  = screen_center_x + 20 / screen_zoom;
    float top    = screen_center_y + 20 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(90.0), 1.0, 0.1, 5000.0);
    Dashboard_Matrices.projection = glm::ortho(left, right, bottom, top);
}
