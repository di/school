//
// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA olors
color4 vertex_colors[8] = {
    color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
    color4( 0.0, 1.0, 1.0, 1.0 ),   // cyan
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 1.0, 1.0, 0.0, 1.0 )  // yellow
};

enum Trans {SCALE, ROTATE, TRANSLATE};

GLuint  program;
GLfloat delta;
GLfloat  r_x, r_y, r_z;
GLfloat  s_x, s_y, s_z;
GLfloat  t_x, t_y, t_z;
int currentTrans;

//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices
int Index = 0;
void
quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
    colorcube();

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
          NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader36.glsl", "fshader36.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(sizeof(points)) );

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    t_x = 0.0;
    t_y = 0.0;
    t_z = 0.0;
    r_x = 0.58539;
    r_y = 0.78539;
    r_z = 1.57079;
    s_x = 1.0;
    s_y = 1.0;
    s_z = 1.0;
    delta = 0.01;
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

    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( currentTrans ) {
        case SCALE:
            switch( key ) {
                case 'x' : s_x += delta; break;
                case 'y' : s_y += delta; break;
                case 'z' : s_z += delta; break;
                case 'X' : s_x -= delta; break;
                case 'Y' : s_y -= delta; break;
                case 'Z' : s_z -= delta; break;
                case 'd' : delta += 0.01; break;
                case 'D' : delta -= 0.01; break;
            }
            break;
        case ROTATE:
            switch( key ) {
                case 'x' : r_x = r_x-delta; break;
                case 'y' : r_y = r_y-delta; break;
                case 'z' : r_z = r_z-delta; break;
                case 'X' : r_x = r_x+delta; break;
                case 'Y' : r_y = r_y+delta; break;
                case 'Z' : r_z = r_z+delta; break;
                case 'd' : delta += 0.01; break;
                case 'D' : delta -= 0.01; break;
            }
            break;
        case TRANSLATE:
            switch( key ) {
                case 'x' : t_x = t_x-delta; break;
                case 'y' : t_y = t_y-delta; break;
                case 'z' : t_z = t_z-delta; break;
                case 'X' : t_x = t_x+delta; break;
                case 'Y' : t_y = t_y+delta; break;
                case 'Z' : t_z = t_z+delta; break;
                case 'd' : delta += 0.01; break;
                case 'D' : delta -= 0.01; break;
            }
            break;
    }
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void processMenuEvents(int option)
{
   currentTrans = option;
}

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Color Cube" );

    glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("SCALE", SCALE);
    glutAddMenuEntry("ROTATE", ROTATE);
    glutAddMenuEntry("TRANSLATE", TRANSLATE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glewInit();
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
