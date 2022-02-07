/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 * authors: TAIDER Silia / BEN SALAH Mariem
 * Programme principal des appels OpenGL
 \*****************************************************************************/

#include "declaration.h"
#include<time.h>
#include<string.h>
#include<string>

 //identifiant des shaders
GLuint shader_program_id;
GLuint gui_program_id;

camera cam;
vec3 cam_vec_directeur = vec3(0.0f, 0.0f, -0.3f);
vec3 cam_vec_cote = vec3(0.3f, 0.0f, 0.0f);

bool LOSE = false;
bool WIN = false;

const int nb_obj = 200;
objet3d obj[nb_obj];

const int nb_text = 4;
text text_to_draw[nb_text];

int k = 0; //initialisation nombre de sapins qu'on va mettre sur la scène
//dimension matrice formant les sapins
const int nb_lignes_sapin = 20;
const int nb_colonnes_sapin = 17;

const int nb_lignes_armadillo = 10;
const int nb_colonnes_armadillo = 10;

const int nb_lignes_decor = 10;
const int nb_colonnes_decor = 10;

int n_objet = 10;
int incrementation = n_objet;
int n_sapins = 65+ n_objet;
int n_armadillos = n_sapins + 30;

bool col_skate = false;
bool col_hat = false;


/*****************************************************************************\
* initialisation                                                              *
\*****************************************************************************/
static void init()
{
    shader_program_id = glhelper::create_program_from_file("shaders/shader.vert", "shaders/shader.frag"); CHECK_GL_ERROR();

    cam.projection = matrice_projection(60.0f * M_PI / 180.0f, 1.0f, 0.01f, 100.0f);
    cam.tr.translation = vec3(0.0f, 1.0f, 0.0f);
    cam.tr.rotation_center = vec3(0.0f, 20.0f, 0.0f);

    init_snowman(); // obj[0
    init_snow(); // obj[1
    init_armadillo(); // obj[2
    init_sapin(); // obj[03
    init_skate(); // obj[4
    init_snowman_skate(); // obj[5
    init_home(); //obj[6
    init_hat(); //obj[7
    init_santa(); //obj[8
    init_decor(); //obj[9


    int i;
    int j;
    int d_x = -60;
    int d_z = 10;
    int d_x_arm = 1;
    int d_z_arm = 10;
    int d_x_dec = 1;
    int d_z_dec = 10;


    char sapins[nb_lignes_sapin][nb_colonnes_sapin] = {
      {1,0,1,0,0,1,0,0,0,1,0,1,0,0,1,0,1},
      {1,0,0,1,0,0,0,1,0,1,0,0,1,0,0,1,1},
      {0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0},
      {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
      {0,0,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,1,1},
      {1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1},
      {0,0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0},
      {1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,1,0},
      {0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0},
      {1,1,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0},
      {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
    };

    for (i = 0; i < nb_lignes_sapin; i++) {
        for (j = 0; j < nb_colonnes_sapin; j++) { // pour chaque element de la matrice
            if (sapins[i][j] == 1) {
                obj[incrementation] = obj[3]; //objet[3] = le sapin d'origine
                obj[incrementation].tr.translation += vec3(2 * d_x, 0.0, -2 * d_z); //décalage horizontal
                incrementation++;
            }
            d_x += 10;
        }
        d_x = -60;
        d_z -= 10; //decalage vertical
    }

    char armadillos[nb_lignes_armadillo][nb_colonnes_armadillo] = {
      {1,0,0,1,0,0,1,1,0,1},
      {0,0,1,0,0,1,0,0,0,0},
      {1,1,0,1,0,0,0,1,0,1},
      {1,0,0,0,0,1,0,1,0,0},
      {0,0,1,0,0,0,0,0,0,1},
      {0,1,0,0,0,0,0,1,0,0},
      {1,0,0,0,0,1,0,0,1,0},
      {0,1,0,0,0,0,0,0,0,1},
      {1,0,0,1,0,0,0,1,0,0},
      {0,1,0,0,0,1,0,0,0,1},
    };

    for (i = 0; i < nb_lignes_armadillo; i++) {
        for (j = 0; j < nb_colonnes_armadillo; j++) { // pour chaque element de la matrice
            if (armadillos[i][j] == 1) {
                obj[n_sapins] = obj[2]; //objet[2] = l'armadillo d'origine
                obj[n_sapins].tr.translation += vec3(2*d_x_arm, 0.0, -2*d_z_arm); //décalage horizontal
                n_sapins++;
            }
            d_x_arm += 3;
        }
        d_x_arm = 1;
        d_z_arm -= 5; //decalage vertical
    }

    char decor[nb_lignes_decor][nb_colonnes_decor] = {
      {1,0,0,1,0,0,1,1,0,1},
      {0,0,1,0,0,1,0,0,0,0},
      {1,1,0,1,0,0,0,1,0,1},
      {1,0,0,0,0,1,0,1,0,0},
      {0,0,1,0,0,0,0,0,0,1},
      {0,1,0,0,0,0,0,1,0,0},
      {1,0,0,0,0,1,0,0,1,0},
      {0,1,0,0,0,0,0,0,0,1},
      {1,0,0,1,0,0,0,1,0,0},
      {0,1,0,0,0,1,0,0,0,1},
    };

    for (i = 0; i < nb_lignes_decor; i++) {
        for (j = 0; j < nb_colonnes_decor; j++) { // pour chaque element de la matrice
            if (decor[i][j] == 1) {
                obj[n_armadillos] = obj[9]; //objet[9] = le decor d'origine
                obj[n_armadillos].tr.translation += vec3(2 * d_x_dec, 0.0, -2 * d_z_dec); //décalage horizontal
                n_armadillos++;
            }
            d_x_dec += 3;
        }
        d_x_dec = 1;
        d_z_dec -= 5; //decalage vertical
    }

    gui_program_id = glhelper::create_program_from_file("shaders/gui.vert", "shaders/gui.frag"); CHECK_GL_ERROR();

    int var = 3;
    std::string s = std::to_string(var);


    text_to_draw[0].value = "Game Over";
    text_to_draw[0].bottomLeft = vec2(-0.4, 0.5);
    text_to_draw[0].topRight = vec2(0.4, 1.2);
    init_text(text_to_draw);

    text_to_draw[1] = text_to_draw[0];
    text_to_draw[1].value = "Press x";
    text_to_draw[1].bottomLeft.y = 0.0f;
    text_to_draw[1].topRight.y = 0.5f;

    text_to_draw[2] = text_to_draw[0];
    text_to_draw[2].value = "Bravo";
    text_to_draw[2].bottomLeft = vec2(-0.4, 0.5);
    text_to_draw[2].topRight = vec2(0.4, 1.2);

    text_to_draw[3] = text_to_draw[0];
    text_to_draw[3].value = "Press x";
    text_to_draw[3].bottomLeft.y = 0.0f;
    text_to_draw[3].topRight.y = 0.5f;
}


/*****************************************************************************\
* collision                                                           *
\*****************************************************************************/
bool collision_sapin(int objet1, int objet2) {

    bool collisionX = false;
    bool collisionZ = false;

    // collision x-axis?
    collisionX = ((obj[objet1].tr.translation.x + 0.71 <= (obj[objet2].tr.translation.x + 1)) && (obj[objet1].tr.translation.x + 0.71 >= (obj[objet2].tr.translation.x - 1))) || (((obj[objet1].tr.translation.x) <= (obj[objet2].tr.translation.x + 1)) && ((obj[objet1].tr.translation.x) >= (obj[objet2].tr.translation.x - 1)));
    // collision z-axis?
    collisionZ = (obj[objet1].tr.translation.z - +0.71 >= obj[objet2].tr.translation.z - 1 && obj[objet1].tr.translation.z - 0.71 <= obj[objet2].tr.translation.z + 1) || (((obj[objet1].tr.translation.z + 1) >= (obj[objet2].tr.translation.z - 1)) && ((obj[objet1].tr.translation.z + 0.71) <= (obj[objet2].tr.translation.z + 1)));
    // collision only if on both axes
    //printf("collision x =%d, collision y = %d\n", collisionX, collisionZ);
    return (collisionX && collisionZ);

}

bool collision_armadillo(int objet1, int objet2) {

    bool collisionX = false;
    bool collisionZ = false;

    // collision x-axis?
    collisionX = ((obj[objet1].tr.translation.x + 0.3 <= (obj[objet2].tr.translation.x + 0.5)) && (obj[objet1].tr.translation.x + 0.3 >= (obj[objet2].tr.translation.x - 0.5))) || (((obj[objet1].tr.translation.x) <= (obj[objet2].tr.translation.x + 0.5)) && ((obj[objet1].tr.translation.x) >= (obj[objet2].tr.translation.x - 0.5)));
    // collision z-axis?
    collisionZ = (obj[objet1].tr.translation.z - 0.3 >= obj[objet2].tr.translation.z - 0.5 && obj[objet1].tr.translation.z - 0.3 <= obj[objet2].tr.translation.z + 0.5) || (((obj[objet1].tr.translation.z + 0.5) >= (obj[objet2].tr.translation.z - 0.5)) && ((obj[objet1].tr.translation.z + 0.3) <= (obj[objet2].tr.translation.z + 0.5)));
    // collision only if on both axes
    //printf("collision x =%d, collision y = %d\n", collisionX, collisionZ);
    return (collisionX && collisionZ);

}

bool collision_skate(int objet1, int objet2) {

    bool collisionX = false;
    bool collisionZ = false;

    // collision x-axis?
    collisionX = ((obj[objet1].tr.translation.x + 0.3 <= (obj[objet2].tr.translation.x + 0.5)) && (obj[objet1].tr.translation.x + 0.3 >= (obj[objet2].tr.translation.x - 0.5))) || (((obj[objet1].tr.translation.x) <= (obj[objet2].tr.translation.x + 0.5)) && ((obj[objet1].tr.translation.x) >= (obj[objet2].tr.translation.x - 0.5)));
    // collision z-axis?
    collisionZ = (obj[objet1].tr.translation.z - 0.3 >= obj[objet2].tr.translation.z - 0.5 && obj[objet1].tr.translation.z - 0.3 <= obj[objet2].tr.translation.z + 0.5) || (((obj[objet1].tr.translation.z + 0.5) >= (obj[objet2].tr.translation.z - 0.5)) && ((obj[objet1].tr.translation.z + 0.3) <= (obj[objet2].tr.translation.z + 0.5)));
    // collision only if on both axes
    //printf("collision x =%d, collision y = %d\n", collisionX, collisionZ);
    return (collisionX && collisionZ);

}

bool collision_hat(int objet1, int objet2) {

    bool collisionX = false;
    bool collisionZ = false;

    // collision x-axis?
    collisionX = ((obj[objet1].tr.translation.x + 0.3 <= (obj[objet2].tr.translation.x + 0.2)) && (obj[objet1].tr.translation.x + 0.3 >= (obj[objet2].tr.translation.x - 0.2))) || (((obj[objet1].tr.translation.x) <= (obj[objet2].tr.translation.x + 0.2)) && ((obj[objet1].tr.translation.x) >= (obj[objet2].tr.translation.x - 0.2)));
    // collision z-axis?
    collisionZ = (obj[objet1].tr.translation.z - 0.3 >= obj[objet2].tr.translation.z - 0.2 && obj[objet1].tr.translation.z - 0.3 <= obj[objet2].tr.translation.z + 0.2) || (((obj[objet1].tr.translation.z + 0.2) >= (obj[objet2].tr.translation.z - 0.2)) && ((obj[objet1].tr.translation.z + 0.3) <= (obj[objet2].tr.translation.z + 0.2)));
    // collision only if on both axes
    //printf("collision x =%d, collision y = %d\n", collisionX, collisionZ);
    return (collisionX && collisionZ);

}

bool collision_home(int objet1, int objet2) {

    bool collisionX = false;
    bool collisionZ = false;

    // collision x-axis?
    collisionX = ((obj[objet1].tr.translation.x + 0.71 <= (obj[objet2].tr.translation.x + 10)) && (obj[objet1].tr.translation.x + 0.71 >= (obj[objet2].tr.translation.x - 10))) || (((obj[objet1].tr.translation.x) <= (obj[objet2].tr.translation.x + 10)) && ((obj[objet1].tr.translation.x) >= (obj[objet2].tr.translation.x - 10)));
    // collision z-axis?
    collisionZ = (obj[objet1].tr.translation.z - +0.71 >= obj[objet2].tr.translation.z - 10 && obj[objet1].tr.translation.z - 0.71 <= obj[objet2].tr.translation.z + 10) || (((obj[objet1].tr.translation.z + 1) >= (obj[objet2].tr.translation.z - 10)) && ((obj[objet1].tr.translation.z + 0.71) <= (obj[objet2].tr.translation.z + 10)));
    // collision only if on both axes
    //printf("collision x =%d, collision y = %d\n", collisionX, collisionZ);
    return (collisionX && collisionZ);

}

/*****************************************************************************\
* display_callback                                                           *
\*****************************************************************************/
static void display_callback()
{
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f); CHECK_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();

    if (cam.tr.translation.y < -50) {//pour ne pas tomber trop bas
        cam.tr.translation = vec3(0.0f, 0.0f, 0.0f);
    }

    cam.tr.rotation_center = cam.tr.translation;

    for (int i = 0; i < nb_obj; ++i) {
        if (i != 2)
            draw_obj3d(obj + i, cam);
    }

    if (LOSE) {
        for (int i = 0; i < 2; ++i)
            draw_text(text_to_draw + i);
    }

    if (WIN) {
        for (int i = 2; i < nb_text; ++i)
            draw_text(text_to_draw + i);
    }

    for (int i = 65 + n_objet; i < nb_obj; i++) {
        float dz = ((float)rand() / RAND_MAX)*0.03;
        float dl = (2 * ((float)rand() / RAND_MAX) - 1) * 0.03;
        if (i%2)
            obj[i].tr.translation += matrice_rotation(obj[i].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(dl, 0.0f, dz);
        else
            obj[i].tr.translation += matrice_rotation(obj[i].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(-dl, 0.0f, -dz);
    }

    glutSwapBuffers();
}

/*****************************************************************************\
* keyboard_callback                                                           *
\*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{
    float dL = 0.5f;
    float dz = 0.5f;
    float dtheta = 0.1f;
    bool isCollision = false;

    switch (key)
    {
        int i;
    case 'p':
        glhelper::print_screen();
        break;


    case 'd':
        obj[0].tr.translation += matrice_rotation(obj[0].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(dL, 0.0f, 0.0f);

        for (i = n_objet; i < 65+n_objet; i++) {
            if (collision_sapin(0, i)) {
                isCollision = true;
                printf("collision sapin avant\n");
                break;
            }
        }

        for (i = 65+n_objet; i < 65 + n_objet +30; i++) {
            if (collision_armadillo(0, i)) {
                obj[0].visible = false;
                LOSE = true;
                printf("game over\n");
                break;
            }
        }

        if (collision_home(0, 6)) {
            isCollision = true;
            printf("collision home avant\n");
        }

        if (collision_skate(0, 4)) {
            obj[0].vao = obj[5].vao;
            obj[0].nb_triangle = obj[5].nb_triangle;
            obj[4].visible = false;
            col_skate = true;
            printf("collision skate avant\n");
        }

        if (collision_hat(0, 7)) {
            obj[0].vao = obj[8].vao;
            obj[0].nb_triangle = obj[8].nb_triangle;
            obj[7].visible = false;
            col_hat = true;
            printf("collision hat recul\n");
        }

        if (col_skate && col_hat)
            WIN = true;

        if (isCollision) {
            obj[0].tr.translation -= matrice_rotation(obj[0].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(dL, 0.0f, 0.0f);
            isCollision = false;
        }

        break;

    case 'q':

        obj[0].tr.translation -= matrice_rotation(obj[0].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(dL, 0.0f, 0.0f);

        for (i = n_objet; i < 65 + n_objet; i++) {
            if (collision_sapin(0, i)) {
                isCollision = true;
                printf("collision sapin avant\n");
                break;
            }
        }

        for (i = 65 + n_objet; i < 65 + n_objet + 30; i++) {
            if (collision_armadillo(0, i)) {
                obj[0].visible = false;
                LOSE = true;
                printf("game over\n");
                break;
            }
        }

        if (collision_home(0, 6)) {
            isCollision = true;
            printf("collision home avant\n");
        }

        if (collision_skate(0, 4)) {
            obj[0].vao = obj[5].vao;
            obj[0].nb_triangle = obj[5].nb_triangle;
            obj[4].visible = false;
            col_skate = true;
            printf("collision skate avant\n");
        }

        if (collision_hat(0, 7)) {
            obj[0].vao = obj[8].vao;
            obj[0].nb_triangle = obj[8].nb_triangle;
            obj[7].visible = false;
            col_hat = true;
            printf("collision hat recul\n");
        }

        if (col_skate && col_hat)
            WIN = true;

        if (isCollision) {
            obj[0].tr.translation += matrice_rotation(obj[0].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(dL, 0.0f, 0.0f);
            isCollision = false;
        }

        break;

    case 'a':
        obj[0].tr.rotation_euler.y += dtheta;

        break;

    case 'e':
        obj[0].tr.rotation_euler.y -= dtheta;

        break;

    case 'x':
    case 'X':
    case 27:
        exit(0);
        break;

    }

    cam.tr.translation = obj[0].tr.translation - matrice_rotation(obj[0].tr.rotation_euler.y, 0.0f, 1.0f, 0.0f) * vec3(7., 0.0f, 0.0f) + vec3(0.0f, 1.0f, 0.0f);
    cam.tr.rotation_euler.y = M_PI / 2. - obj[0].tr.rotation_euler.y;
    cam.tr.rotation_center = cam.tr.translation;

}

/*****************************************************************************\
* special_callback                                                            *
\*****************************************************************************/
static void special_callback(int key, int, int)
{
    /*switch (key)
    {
    case GLUT_KEY_UP:
        UP = true;
    }*/
}


/*****************************************************************************\
* timer_callback                                                              *
\*****************************************************************************/
static void timer_callback(int)
{
    glutTimerFunc(25, timer_callback, 0);
    glutPostRedisplay();
}

/*****************************************************************************\
* main                                                                         *
\*****************************************************************************/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | MACOSX_COMPATIBILITY);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(display_callback);
    glutKeyboardFunc(keyboard_callback);
    glutSpecialFunc(special_callback);
    glutTimerFunc(25, timer_callback, 0);

    glewExperimental = true;
    glewInit();

    std::cout << "OpenGL: " << (GLchar*)(glGetString(GL_VERSION)) << std::endl;

    init();
    glutMainLoop();

    return 0;
}

/*****************************************************************************\
* draw_text                                                                   *
\*****************************************************************************/
void draw_text(const text* const t)
{
    if (!t->visible) return;

    glDisable(GL_DEPTH_TEST);
    glUseProgram(t->prog);

    vec2 size = (t->topRight - t->bottomLeft) / float(t->value.size());

    GLint loc_size = glGetUniformLocation(gui_program_id, "size"); CHECK_GL_ERROR();
    if (loc_size == -1) std::cerr << "Pas de variable uniforme : size" << std::endl;
    glUniform2f(loc_size, size.x, size.y);     CHECK_GL_ERROR();

    glBindVertexArray(t->vao);                CHECK_GL_ERROR();

    for (unsigned i = 0; i < t->value.size(); ++i)
    {
        GLint loc_start = glGetUniformLocation(gui_program_id, "start"); CHECK_GL_ERROR();
        if (loc_start == -1) std::cerr << "Pas de variable uniforme : start" << std::endl;
        glUniform2f(loc_start, t->bottomLeft.x + i * size.x, t->bottomLeft.y);    CHECK_GL_ERROR();

        GLint loc_char = glGetUniformLocation(gui_program_id, "c"); CHECK_GL_ERROR();
        if (loc_char == -1) std::cerr << "Pas de variable uniforme : c" << std::endl;
        glUniform1i(loc_char, (int)t->value[i]);    CHECK_GL_ERROR();
        glBindTexture(GL_TEXTURE_2D, t->texture_id);                            CHECK_GL_ERROR();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);                    CHECK_GL_ERROR();
    }
}

/*****************************************************************************\
* draw_obj3d                                                                  *
\*****************************************************************************/
void draw_obj3d(const objet3d* const obj, camera cam)
{
    if (!obj->visible) return;

    glEnable(GL_DEPTH_TEST);
    glUseProgram(obj->prog);

    {
        GLint loc_projection = glGetUniformLocation(shader_program_id, "projection"); CHECK_GL_ERROR();
        if (loc_projection == -1) std::cerr << "Pas de variable uniforme : projection" << std::endl;
        glUniformMatrix4fv(loc_projection, 1, false, pointeur(cam.projection));    CHECK_GL_ERROR();

        GLint loc_rotation_view = glGetUniformLocation(shader_program_id, "rotation_view"); CHECK_GL_ERROR();
        if (loc_rotation_view == -1) std::cerr << "Pas de variable uniforme : rotation_view" << std::endl;
        mat4 rotation_x = matrice_rotation(cam.tr.rotation_euler.x, 1.0f, 0.0f, 0.0f);
        mat4 rotation_y = matrice_rotation(cam.tr.rotation_euler.y, 0.0f, 1.0f, 0.0f);
        mat4 rotation_z = matrice_rotation(cam.tr.rotation_euler.z, 0.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(loc_rotation_view, 1, false, pointeur(rotation_x * rotation_y * rotation_z));    CHECK_GL_ERROR();

        vec3 cv = cam.tr.rotation_center;
        GLint loc_rotation_center_view = glGetUniformLocation(shader_program_id, "rotation_center_view"); CHECK_GL_ERROR();
        if (loc_rotation_center_view == -1) std::cerr << "Pas de variable uniforme : rotation_center_view" << std::endl;
        glUniform4f(loc_rotation_center_view, cv.x, cv.y, cv.z, 0.0f); CHECK_GL_ERROR();

        vec3 tv = cam.tr.translation;
        GLint loc_translation_view = glGetUniformLocation(shader_program_id, "translation_view"); CHECK_GL_ERROR();
        if (loc_translation_view == -1) std::cerr << "Pas de variable uniforme : translation_view" << std::endl;
        glUniform4f(loc_translation_view, tv.x, tv.y, tv.z, 0.0f); CHECK_GL_ERROR();
    }
    {
        GLint loc_rotation_model = glGetUniformLocation(obj->prog, "rotation_model"); CHECK_GL_ERROR();
        if (loc_rotation_model == -1) std::cerr << "Pas de variable uniforme : rotation_model" << std::endl;
        mat4 rotation_x = matrice_rotation(obj->tr.rotation_euler.x, 1.0f, 0.0f, 0.0f);
        mat4 rotation_y = matrice_rotation(obj->tr.rotation_euler.y, 0.0f, 1.0f, 0.0f);
        mat4 rotation_z = matrice_rotation(obj->tr.rotation_euler.z, 0.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(loc_rotation_model, 1, false, pointeur(rotation_x * rotation_y * rotation_z));    CHECK_GL_ERROR();

        vec3 c = obj->tr.rotation_center;
        GLint loc_rotation_center_model = glGetUniformLocation(obj->prog, "rotation_center_model");   CHECK_GL_ERROR();
        if (loc_rotation_center_model == -1) std::cerr << "Pas de variable uniforme : rotation_center_model" << std::endl;
        glUniform4f(loc_rotation_center_model, c.x, c.y, c.z, 0.0f);                                  CHECK_GL_ERROR();

        vec3 t = obj->tr.translation;
        GLint loc_translation_model = glGetUniformLocation(obj->prog, "translation_model"); CHECK_GL_ERROR();
        if (loc_translation_model == -1) std::cerr << "Pas de variable uniforme : translation_model" << std::endl;
        glUniform4f(loc_translation_model, t.x, t.y, t.z, 0.0f);                                     CHECK_GL_ERROR();
    }
    glBindVertexArray(obj->vao);                                              CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, obj->texture_id);                            CHECK_GL_ERROR();
    glDrawElements(GL_TRIANGLES, 3 * obj->nb_triangle, GL_UNSIGNED_INT, 0);     CHECK_GL_ERROR();
}

void init_text(text* t) {
    vec3 p0 = vec3(0.0f, 0.0f, 0.0f);
    vec3 p1 = vec3(0.0f, 1.0f, 0.0f);
    vec3 p2 = vec3(1.0f, 1.0f, 0.0f);
    vec3 p3 = vec3(1.0f, 0.0f, 0.0f);

    vec3 geometrie[4] = { p0, p1, p2, p3 };
    triangle_index index[2] = { triangle_index(0, 1, 2), triangle_index(0, 2, 3) };

    glGenVertexArrays(1, &(t->vao));                                              CHECK_GL_ERROR();
    glBindVertexArray(t->vao);                                                  CHECK_GL_ERROR();

    GLuint vbo;
    glGenBuffers(1, &vbo);                                                       CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                          CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometrie), geometrie, GL_STATIC_DRAW);   CHECK_GL_ERROR();

    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();

    GLuint vboi;
    glGenBuffers(1, &vboi);                                                      CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);                                 CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);   CHECK_GL_ERROR();

    t->texture_id = glhelper::load_texture("data/fontB.tga");

    t->visible = true;
    t->prog = gui_program_id;
}

GLuint upload_mesh_to_gpu(const mesh& m)
{
    GLuint vao, vbo, vboi;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, vbo); CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, m.vertex.size() * sizeof(vertex_opengl), &m.vertex[0], GL_STATIC_DRAW); CHECK_GL_ERROR();

    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), 0); CHECK_GL_ERROR();

    glEnableVertexAttribArray(1); CHECK_GL_ERROR();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(vertex_opengl), (void*)sizeof(vec3)); CHECK_GL_ERROR();

    glEnableVertexAttribArray(2); CHECK_GL_ERROR();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(2 * sizeof(vec3))); CHECK_GL_ERROR();

    glEnableVertexAttribArray(3); CHECK_GL_ERROR();
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(3 * sizeof(vec3))); CHECK_GL_ERROR();

    glGenBuffers(1, &vboi); CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi); CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.connectivity.size() * sizeof(triangle_index), &m.connectivity[0], GL_STATIC_DRAW); CHECK_GL_ERROR();

    return vao;
}

void init_snowman()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/snowman.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[0].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[0].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(1.0f, 1.0f, 1.0f));

    obj[0].vao = upload_mesh_to_gpu(m);

    obj[0].nb_triangle = m.connectivity.size();
    obj[0].texture_id = glhelper::load_texture("data/snow.tga");
    obj[0].visible = true;
    obj[0].prog = shader_program_id;

    obj[0].tr.translation = vec3(-2.0f, -0.05f, -5.0f);
}

void init_snow()
{

    mesh m;

    int p = 200;
    //coordonnees geometriques des sommets
    vec3 p0 = vec3(-200.0f, 0.0f, -200.0f);
    vec3 p1 = vec3(200.0f, 0.0f, -200.0f);
    vec3 p2 = vec3(200.0f, 0.0f, 200.0f);
    vec3 p3 = vec3(-200.0f, 0.0f, 200.0f);

    //normales pour chaque sommet
    vec3 n0 = vec3(0.0f, 1.0f, 0.0f);
    vec3 n1 = n0;
    vec3 n2 = n0;
    vec3 n3 = n0;

    //couleur pour chaque sommet
    vec3 c0 = vec3(1.0f, 1.0f, 1.0f);
    vec3 c1 = c0;
    vec3 c2 = c0;
    vec3 c3 = c0;

    //texture du sommet
    vec2 t0 = vec2(0.0f, 0.0f);
    vec2 t1 = vec2(1.0f, 0.0f);
    vec2 t2 = vec2(1.0f, 1.0f);
    vec2 t3 = vec2(0.0f, 1.0f);

    vertex_opengl v0 = vertex_opengl(p0, n0, c0, t0);
    vertex_opengl v1 = vertex_opengl(p1, n1, c1, t1);
    vertex_opengl v2 = vertex_opengl(p2, n2, c2, t2);
    vertex_opengl v3 = vertex_opengl(p3, n3, c3, t3);

    m.vertex = { v0, v1, v2, v3 };

    //indice des triangles
    triangle_index tri0 = triangle_index(0, 1, 2);
    triangle_index tri1 = triangle_index(0, 2, 3);
    m.connectivity = { tri0, tri1 };

    obj[1].nb_triangle = 2;
    obj[1].vao = upload_mesh_to_gpu(m);

    obj[1].texture_id = glhelper::load_texture("data/snow.tga");

    obj[1].visible = true;
    obj[1].prog = shader_program_id;


}

void init_armadillo()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_off_file("data/armadillo_light.off");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.01f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.50f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, matrice_rotation(M_PI / 2.0f, 1.0f, 0.0f, 0.0f));
    apply_deformation(&m, matrice_rotation(M_PI, 0.0f, 1.0f, 0.0f));
    apply_deformation(&m, transform);

    update_normals(&m);
    fill_color(&m, vec3(1.0f, 0.0f, 0.6f));

    obj[2].vao = upload_mesh_to_gpu(m);

    obj[2].nb_triangle = m.connectivity.size();
    obj[2].texture_id = glhelper::load_texture("data/white.tga");

    obj[2].visible = true;
    obj[2].prog = shader_program_id;

    obj[2].tr.translation = vec3(2.0, 0.0, -10.0);
}

void init_sapin()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/sapin.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[3].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[3].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.0f, 1.0f, 0.3f));

    obj[3].vao = upload_mesh_to_gpu(m);

    obj[3].nb_triangle = m.connectivity.size();
    obj[3].texture_id = glhelper::load_texture("data/snow.tga");
    obj[3].visible = true;
    obj[3].prog = shader_program_id;

    obj[3].tr.translation = vec3(2.0f, -0.2f, -20.0f);

}

void init_skate()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/skateboard.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[4].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[4].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.34f, 0.16f, 0.0f));

    obj[4].vao = upload_mesh_to_gpu(m);

    obj[4].nb_triangle = m.connectivity.size();
    obj[4].texture_id = glhelper::load_texture("data/snow.tga");
    obj[4].visible = true;
    obj[4].prog = shader_program_id;

    obj[4].tr.translation = vec3(25.0f, 0.1f, -40.0f);

}

void init_snowman_skate()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/snowman_skate.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[5].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[5].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.5f, 0.0f, 1.0f));

    obj[5].vao = upload_mesh_to_gpu(m);

    obj[5].nb_triangle = m.connectivity.size();
    obj[5].texture_id = glhelper::load_texture("data/snow.tga");
    obj[5].visible = true;
    obj[5].prog = shader_program_id;

    obj[5].tr.translation = vec3(-2.0f, -0.05f, -5.0f);

    obj[5].visible = false;
}

void init_home()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/home.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[6].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[6].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.34f, 0.16f, 0.0f));

    obj[6].vao = upload_mesh_to_gpu(m);

    obj[6].nb_triangle = m.connectivity.size();
    obj[6].texture_id = glhelper::load_texture("data/snow.tga");
    obj[6].visible = true;
    obj[6].prog = shader_program_id;

    obj[6].tr.translation = vec3(-20.0f, -0.05f, 50.0f);
}

void init_hat()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/hat.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[7].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[7].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.9f, 0.1f, 0.0f));

    obj[7].vao = upload_mesh_to_gpu(m);

    obj[7].nb_triangle = m.connectivity.size();
    obj[7].texture_id = glhelper::load_texture("data/snow.tga");
    obj[7].visible = true;
    obj[7].prog = shader_program_id;

    obj[7].tr.translation = vec3(40.0f, 0.1f, -20.0f);

}

void init_santa()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/Santa.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[8].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[8].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(1.0f, 0.0f, 0.0f));

    obj[8].vao = upload_mesh_to_gpu(m);

    obj[8].nb_triangle = m.connectivity.size();
    obj[8].texture_id = glhelper::load_texture("data/snow.tga");
    obj[8].visible = true;
    obj[8].prog = shader_program_id;

    obj[8].tr.translation = vec3(-2.0f, -0.05f, -5.0f);

    obj[8].visible = false;
}

void init_decor()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("data/ball.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    obj[9].tr.rotation_center = vec3(0.0f, 0.0f, 0.0f);
    obj[9].tr.rotation_euler = vec3(0.0f, 0.0f, 0.0f);

    update_normals(&m);
    fill_color(&m, vec3(0.0f, 0.1f, 0.9f));

    obj[9].vao = upload_mesh_to_gpu(m);

    obj[9].nb_triangle = m.connectivity.size();
    obj[9].texture_id = glhelper::load_texture("data/snow.tga");
    obj[9].visible = true;
    obj[9].prog = shader_program_id;

    obj[9].tr.translation = vec3(20.0f, 4.0f, 10.0f);
}
