//
// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include "Angel.h"
#include <fstream>

using namespace std;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int NumVertices = 6320*3;
point4 vertices[3644];
point4 points[NumVertices];
vec3 normals[NumVertices];
//color4 colors[NumVertices];

enum Projection {PARALLEL, PERSPECTIVE};
int currentProjection;
mat4 projection;
GLuint  program;

GLfloat  o_left = -1.0, o_right = 1.0;
GLfloat  bottom = -1.0, top = 1.0;
GLfloat  zNear = 0.5, zFar = 3.0;

GLfloat delta;
GLfloat  r_x, r_y, r_z;
GLfloat  s_x, s_y, s_z;
GLfloat  t_x, t_y, t_z;

GLfloat radius = 1.0;
GLfloat theta = 0.0;
GLfloat phi = 0.0;
GLfloat height = 0.5;

int camspeed = 60;

bool animate = true;

// OpenGL initialization
void
init()
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(normals), normals);

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader36.glsl", "fshader36.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(0) );

    GLuint vNormal = glGetAttribLocation( program, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(sizeof(points)) );

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    t_x = 0.0;
    t_y = 0.0;
    t_z = 0.0;
    r_x = 0.0;
    r_y = 0.0;
    r_z = 0.0;
    s_x = 0.2;
    s_y = 0.2;
    s_z = 0.2;
    delta = 0.01;

    projection = Ortho( o_left, o_right, bottom, top, zNear, zFar );

}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUniform1f(glGetUniformLocation( program, "t_x" ), t_x);
    glUniform1f(glGetUniformLocation( program, "t_y" ), t_y);
    glUniform1f(glGetUniformLocation( program, "t_z" ), t_z);
    glUniform1f(glGetUniformLocation( program, "r_x" ), r_x);
    glUniform1f(glGetUniformLocation( program, "r_y" ), r_y);
    glUniform1f(glGetUniformLocation( program, "r_z" ), r_z);
    glUniform1f(glGetUniformLocation( program, "s_x" ), s_x);
    glUniform1f(glGetUniformLocation( program, "s_y" ), s_y);
    glUniform1f(glGetUniformLocation( program, "s_z" ), s_z);

    glUniformMatrix4fv(glGetUniformLocation( program, "projection" ), 1, GL_TRUE, projection );

    point4  eye( radius*sin(theta)*cos(phi),
         radius*sin(theta)*sin(phi),
         radius*cos(theta),
         1.0 );
    point4  at( 0.0, height, 0.0, 0.0 );
    vec4    up( 0.0, 1.0, 0.0, 0.0 );
    mat4  mv = LookAt( eye, at, up );
    glUniformMatrix4fv( glGetUniformLocation( program, "model_view" ), 1, GL_TRUE, mv );

    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case 's': camspeed += 1; break;
        case 'S': camspeed -= 1; if (camspeed < 1) { camspeed = 1; } break;
        case 'r': radius *= 2.0; break;
        case 'R': radius *= 0.5; break;
        case 'h': height += 0.1; break;
        case 'H': height *= 0.1; break;
        case ' ': animate = !animate; break;

    }
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void myidle()
{
    if (animate)
    {
        theta += 3.14159/camspeed;
        theta = fmodf(theta, (2*3.14159));
        glutPostRedisplay();
    }
}

//----------------------------------------------------------------------------

void processMenuEvents(int option)
{
     switch( option ) {
        case PARALLEL:
            projection = Ortho( o_left, o_right, bottom, top, zNear, zFar);
            break;
        case PERSPECTIVE:
            projection = Perspective(90.0, 1.0, 0.5, 3.0);
            break;
    }
    glutPostRedisplay();
}

int
main( int argc, char **argv )
{
    // Read in file
    std::ifstream infile("teapot.smf");
    char t;
    std::string x, y, z;
    int v_x, v_y, v_z;
    float f_x, f_y, f_z;
    int v_i = 0;
    int f_i = 0;
    float NormalisationFactor, CombinedSquares, Normal_x, Normal_y, Normal_z;
    float v1_x, v1_y, v1_z, v2_x, v2_y, v2_z, n_x, n_y, n_z;
    while (infile >> t >> x >> y >> z)
    {
        switch (t) {
            case 'v' :
                vertices[v_i]=point4(atof(x.c_str()),atof(y.c_str()),atof(z.c_str())-10.0,1.0);
                v_i++;
                break;
            case 'f' :
                points[f_i] = vertices[atoi(x.c_str())-1];
                points[f_i+1] = vertices[atoi(y.c_str())-1];
                points[f_i+2] = vertices[atoi(z.c_str())-1];

                v1_x = points[f_i+1][0] - points[f_i][0];
                v1_y = points[f_i+1][1] - points[f_i][1];
                v1_z = points[f_i+1][2] - points[f_i][2];
                v2_x = points[f_i+2][0] - points[f_i][0];
                v2_y = points[f_i+2][1] - points[f_i][1];
                v2_z = points[f_i+2][2] - points[f_i][2];

                Normal_x = (v1_y * v2_z) - (v1_z * v2_y);
                Normal_y = -((v2_z * v1_x) - (v2_x * v1_z));
                Normal_z = (v1_x * v2_y) - (v1_y * v2_x);
                CombinedSquares = (Normal_x * Normal_x) + (Normal_y * Normal_y) + (Normal_z * Normal_z);
                NormalisationFactor = sqrt(CombinedSquares);
                n_x = Normal_x / NormalisationFactor;
                n_y = Normal_y / NormalisationFactor;
                n_z = Normal_z / NormalisationFactor;

                normals[f_i] = vec3( n_x, n_y, n_z );
                normals[f_i+1] = vec3( n_x, n_y, n_z );
                normals[f_i+2] = vec3( n_x, n_y, n_z );

                f_i += 3;
                break;
        }
    }

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "I'm a little teapot" );

    glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("PARALLEL", PARALLEL);
    glutAddMenuEntry("PERSPECTIVE", PERSPECTIVE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glewInit();
    init();

    glutDisplayFunc( display );
    glutIdleFunc(myidle);
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
