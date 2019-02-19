#include "airplane.h"
#include "main.h"

// YAW - Y
// PITCH - X
// ROLL - Z

const float step = 0.04;

Jet::Jet(float x, float y, float z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->speed = 0.0;

    static GLfloat vertex_buffer_data[10000];
    float angle = ((360.0 / 20.0) * M_PI) / 180.0;
    
    float x_coord = 0.5;
    float y_coord = 0.0;
    
    float temp_x = 0.0;
    float temp_y = 0.0;

    float length = 8.0;

    int iteration_size = 63;

    for(int i=0; i < 20; ++i)
    {
        // Front Arc
        vertex_buffer_data[i * iteration_size] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 1] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 2] = this->position.z + 1.0;

        vertex_buffer_data[i * iteration_size + 3] = 0.0;
        vertex_buffer_data[i * iteration_size + 4] = -0.3;
        vertex_buffer_data[i * iteration_size + 5] = this->position.z + (length / 2.0);

        vertex_buffer_data[i * iteration_size + 6] = x_coord;
        vertex_buffer_data[i * iteration_size + 7] = y_coord;
        vertex_buffer_data[i * iteration_size + 8] = this->position.z + 1.0;
        
        // Back Arc
        vertex_buffer_data[i * iteration_size + 9] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 10] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 11] = this->position.z - (length / 1.5);

        vertex_buffer_data[i * iteration_size + 12] = 0.0;
        vertex_buffer_data[i * iteration_size + 13] = 0.0;
        vertex_buffer_data[i * iteration_size + 14] = this->position.z - (length / 1.5);

        vertex_buffer_data[i * iteration_size + 15] = x_coord;
        vertex_buffer_data[i * iteration_size + 16] = y_coord;
        vertex_buffer_data[i * iteration_size + 17] = this->position.z - (length / 1.5);

        // Join Triangle 1 
        // Front
        vertex_buffer_data[i * iteration_size + 18] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 19] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 20] = this->position.z + 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 21] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 22] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 23] = this->position.z - (length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 24] = x_coord;
        vertex_buffer_data[i * iteration_size + 25] = y_coord;
        vertex_buffer_data[i * iteration_size + 26] = this->position.z + 1.0;


        // Join Triangle 2
        // Back
        vertex_buffer_data[i * iteration_size + 27] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 28] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 29] = this->position.z - (length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 30] = x_coord;
        vertex_buffer_data[i * iteration_size + 31] = y_coord;
        vertex_buffer_data[i * iteration_size + 32] = this->position.z + 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 33] = x_coord;
        vertex_buffer_data[i * iteration_size + 34] = y_coord;
        vertex_buffer_data[i * iteration_size + 35] = this->position.z - (length / 1.5);

        // Small
        vertex_buffer_data[i * iteration_size + 36] = (x_coord * cos(angle) / 1.5) - (y_coord * sin(angle) / 1.5);
        vertex_buffer_data[i * iteration_size + 37] = (x_coord * sin(angle) / 1.5) + (y_coord * cos(angle) / 1.5);
        vertex_buffer_data[i * iteration_size + 38] = this->position.z - (length / 1.5) - 1.0;

        vertex_buffer_data[i * iteration_size + 39] = 0.0;
        vertex_buffer_data[i * iteration_size + 40] = 0.0;
        vertex_buffer_data[i * iteration_size + 41] = this->position.z - (length / 1.5) - 1.0;

        vertex_buffer_data[i * iteration_size + 42] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 43] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 44] = this->position.z - (length / 1.5) - 1.0;

        // Join Triangle 1
        // Front
        vertex_buffer_data[i * iteration_size + 45] = (x_coord * cos(angle) / 1.5) - (y_coord * sin(angle) / 1.5);
        vertex_buffer_data[i * iteration_size + 46] = (x_coord * sin(angle) / 1.5) + (y_coord * cos(angle) / 1.5);
        vertex_buffer_data[i * iteration_size + 47] = this->position.z - (length / 1.5) - 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 48] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 49] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 50] = this->position.z - (length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 51] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 52] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 53] = this->position.z - (length / 1.5) - 1.0;

        // Join Triangle 2
        // Back
        vertex_buffer_data[i * iteration_size + 54] = (x_coord * cos(angle)) - (y_coord * sin(angle));
        vertex_buffer_data[i * iteration_size + 55] = (x_coord * sin(angle)) + (y_coord * cos(angle));
        vertex_buffer_data[i * iteration_size + 56] = this->position.z - (length / 1.5);
        // Front
        vertex_buffer_data[i * iteration_size + 57] = x_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 58] = y_coord / 1.5;
        vertex_buffer_data[i * iteration_size + 59] = this->position.z - (length / 1.5) - 1.0;
        // Back
        vertex_buffer_data[i * iteration_size + 60] = x_coord;
        vertex_buffer_data[i * iteration_size + 61] = y_coord;
        vertex_buffer_data[i * iteration_size + 62] = this->position.z - (length / 1.5); 
        
        // Reset x & y
        temp_x = (x_coord * cos(angle)) - (y_coord * sin(angle));
        temp_y = (x_coord * sin(angle)) + (y_coord * cos(angle));

        x_coord = temp_x;
        y_coord = temp_y;
    }

    // Tail
    vertex_buffer_data[1260] = 0.0;
    vertex_buffer_data[1261] = 2.0;
    vertex_buffer_data[1262] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1263] = 0.0;
    vertex_buffer_data[1264] = 0.5;
    vertex_buffer_data[1265] = this->position.z - (length / 1.5) + 1.5;
    
    vertex_buffer_data[1266] = 0.0;
    vertex_buffer_data[1267] = 0.5;
    vertex_buffer_data[1268] = this->position.z - (length / 1.5) + 0.5;
    
    // Tail right
    vertex_buffer_data[1269] = 0.0;
    vertex_buffer_data[1270] = 2.0;
    vertex_buffer_data[1271] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1272] = 0.5 * sin(angle);
    vertex_buffer_data[1273] = 0.5 * cos(angle);
    vertex_buffer_data[1274] = this->position.z - (length / 1.5) + 1.5;
    
    vertex_buffer_data[1275] = 0.5 * sin(angle);
    vertex_buffer_data[1276] = 0.5 * cos(angle);
    vertex_buffer_data[1277] = this->position.z - (length / 1.5) + 0.5;
    
    // Tail left
    vertex_buffer_data[1278] = 0.0;
    vertex_buffer_data[1279] = 2.0;
    vertex_buffer_data[1280] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1281] = -0.5 * sin(angle);
    vertex_buffer_data[1282] = 0.5 * cos(angle);
    vertex_buffer_data[1283] = this->position.z - (length / 1.5) + 1.5;
    
    vertex_buffer_data[1284] = -0.5 * sin(angle);
    vertex_buffer_data[1285] = 0.5 * cos(angle);
    vertex_buffer_data[1286] = this->position.z - (length / 1.5) + 0.5;

    // Tail rectangles
    vertex_buffer_data[1287] = 0.0;
    vertex_buffer_data[1288] = 2.0;
    vertex_buffer_data[1289] = this->position.z - (length / 1.5);
    
    vertex_buffer_data[1290] = 0.0;
    vertex_buffer_data[1291] = 2.0;
    vertex_buffer_data[1292] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1293] = 0.0;
    vertex_buffer_data[1294] = 0.5;
    vertex_buffer_data[1295] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1287] = 0.0;
    vertex_buffer_data[1288] = 2.0;
    vertex_buffer_data[1289] = this->position.z - (length / 1.5);
    
    vertex_buffer_data[1290] = 0.0;
    vertex_buffer_data[1291] = 2.0;
    vertex_buffer_data[1292] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1293] = 0.5 * sin(angle);
    vertex_buffer_data[1294] = 0.5 * cos(angle);
    vertex_buffer_data[1295] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1296] = 0.0;
    vertex_buffer_data[1297] = 2.0;
    vertex_buffer_data[1298] = this->position.z - (length / 1.5);
    
    vertex_buffer_data[1299] = 0.0;
    vertex_buffer_data[1300] = 2.0;
    vertex_buffer_data[1301] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1302] = -0.5 * sin(angle);
    vertex_buffer_data[1303] = 0.5 * cos(angle);
    vertex_buffer_data[1304] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1305] = 0.0;
    vertex_buffer_data[1306] = 2.0;
    vertex_buffer_data[1307] = this->position.z - (length / 1.5);

    vertex_buffer_data[1308] = 0.0;
    vertex_buffer_data[1309] = 0.5;
    vertex_buffer_data[1310] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1311] = 0.0;
    vertex_buffer_data[1312] = 0.5;
    vertex_buffer_data[1313] = this->position.z - (length / 1.5);
    
    // Tail wings
    // Left
    vertex_buffer_data[1314] = 4.5 * sin(M_PI / 2.0);
    vertex_buffer_data[1315] = 0.0;
    vertex_buffer_data[1316] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1317] = 0.5 * sin(M_PI / 2.0);
    vertex_buffer_data[1318] = 0.0;
    vertex_buffer_data[1319] = this->position.z + 1.0;

    vertex_buffer_data[1320] = 0.5 * sin(M_PI / 2.0);
    vertex_buffer_data[1321] = 0.0;
    vertex_buffer_data[1322] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1323] = 4.5 * sin(M_PI / 2.0);
    vertex_buffer_data[1324] = 0.0;
    vertex_buffer_data[1325] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1326] = 0.5 * sin((M_PI / 2.0) - angle);
    vertex_buffer_data[1327] = 0.0;
    vertex_buffer_data[1328] = this->position.z + 1.0;

    vertex_buffer_data[1329] = 0.5 * sin((M_PI / 2.0) - angle);
    vertex_buffer_data[1330] = 0.0;
    vertex_buffer_data[1331] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1332] = 4.5 * sin(M_PI / 2.0);
    vertex_buffer_data[1333] = 0.0;
    vertex_buffer_data[1334] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1335] = 0.5 * sin((M_PI / 2.0) + angle);
    vertex_buffer_data[1336] = 0.0;
    vertex_buffer_data[1337] = this->position.z + 1.0;

    vertex_buffer_data[1338] = 0.5 * sin((M_PI / 2.0) + angle);
    vertex_buffer_data[1339] = 0.0;
    vertex_buffer_data[1340] = this->position.z - (length / 1.5) + 0.5;
    // Right
    vertex_buffer_data[1341] = 4.5 * sin(3 * M_PI / 2.0);
    vertex_buffer_data[1342] = 0.0;
    vertex_buffer_data[1343] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1344] = 0.5 * sin(3 * M_PI / 2.0);
    vertex_buffer_data[1345] = 0.0;
    vertex_buffer_data[1346] = this->position.z + 1.0;

    vertex_buffer_data[1347] = 0.5 * sin(3 * M_PI / 2.0);
    vertex_buffer_data[1348] = 0.0;
    vertex_buffer_data[1349] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1350] = 4.5 * sin(3 * M_PI / 2.0);
    vertex_buffer_data[1351] = 0.0;
    vertex_buffer_data[1352] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1353] = 0.5 * sin((3 * M_PI / 2.0) - angle);
    vertex_buffer_data[1354] = 0.0;
    vertex_buffer_data[1355] = this->position.z + 1.0;

    vertex_buffer_data[1356] = 0.5 * sin((3 * M_PI / 2.0) - angle);
    vertex_buffer_data[1357] = 0.0;
    vertex_buffer_data[1358] = this->position.z - (length / 1.5) + 0.5;
    
    vertex_buffer_data[1359] = 4.5 * sin(3 * M_PI / 2.0);
    vertex_buffer_data[1360] = 0.0;
    vertex_buffer_data[1361] = this->position.z - (length / 1.5) + 0.5;

    vertex_buffer_data[1362] = 0.5 * sin((3 * M_PI / 2.0) + angle);
    vertex_buffer_data[1363] = 0.0;
    vertex_buffer_data[1364] = this->position.z + 1.0;

    vertex_buffer_data[1365] = 0.5 * sin((3 * M_PI / 2.0) + angle);
    vertex_buffer_data[1366] = 0.0;
    vertex_buffer_data[1367] = this->position.z - (length / 1.5) + 0.5;

    this->object = create3DObject(GL_TRIANGLES, 21 * 20 + 72, vertex_buffer_data, color, GL_LINE);
}

void Jet::draw(glm::mat4 VP)
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

void Jet::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Jet::accelerate()
{  
    if(this->speed < 1.0)
    {
        this->speed += step;
    }
}

void Jet::decelerate()
{
    if(this->speed > 0)
    {
        this->speed -= (step / 2.0);
    }
}

void Jet::stabilize_x()
{
    if (this->rotation_x < 0)
    {
        this->rotation_x += 0.5;
    }
    if (this->rotation_x > 0)
    {
        this->rotation_x -= 0.5;
    }
}

void Jet::stabilize_z()
{
    if (this->rotation_z < 0)
    {
        this->rotation_z += 0.5;
    }
    if (this->rotation_z > 0)
    {
        this->rotation_z -= 0.5;
    }
}

void Jet::fire_missile()
{
    this->missiles.push_back(Missile(this->position.x, this->position.y, this->position.z, this->rotation_x + 15.0, this->rotation_y, this->rotation_z, this->speed, COLOR_YELLOW));
}

void Jet::drop_bomb()
{
    this->bombs.push_back(Bomb(this->position.x, this->position.y, this->position.z, 0.0, this->rotation_y, this->rotation_z, this->speed, COLOR_YELLOW));
}

void Jet::tick()
{
    this->position.x += this->speed * sin(this->rotation_y * M_PI / 180.0);
    this->position.z += this->speed * cos(this->rotation_y * M_PI / 180.0);
    for(int i=0; i < this->missiles.size(); ++i)
    {
        if(this->missiles[i].position.y < -350.0)
        {
            this->missiles.erase(this->missiles.begin() + i);
            --i;
        }
        else
        {
            this->missiles[i].tick();
        }
        
    }
    for(int i=0; i < this->bombs.size(); ++i)
    {
        if(this->bombs[i].position.y < -348.0)
        {
            this->bombs.erase(this->bombs.begin() + i);
            --i;
        }
        else
        {
            this->bombs[i].tick();
        }
        
    }
    this->set_position(this->position.x, this->position.y, this->position.z);
}
