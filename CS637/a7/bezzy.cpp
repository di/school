
#include "Angel.h"
#include <fstream>

typedef Angel::vec4 point4;

// Define a convenient type for referencing patch control points, which
//   is used in the declaration of the vertices' array (used in "vertices.h")
typedef GLfloat     point3[3];
#include "patches.h"
#include "vertices.h"

int NumTimesToSubdivide = 3;
int PatchesPerSubdivision = 4;
int NumQuadsPerPatch = (int) pow( PatchesPerSubdivision, NumTimesToSubdivide );
int NumTriangles = ( NumQuadsPerPatch * 2 );
const int NumVertices = 32*64*12;

int     Index = 0;
int selectedPoint = 0;
point4  points[NumVertices];

GLuint  Projection;

enum { X = 0, Y = 1, Z = 2 };

GLuint  program;
GLfloat  r_x, r_y, r_z;
GLfloat delta = 0.01;
point4  patch[4][4];
const int NumControlPoints = 16;

point3 verts[NumControlPoints];
using namespace std;

//----------------------------------------------------------------------------

void
divide_curve( point4 c[4], point4 r[4], point4 l[4] )
{
    point4  t, mid = ( c[1] + c[2] ) / 2;
    l[0] = c[0];
    l[1] = ( c[0] + c[1] ) / 2;
    l[2] = ( l[1] + mid ) / 2;
    r[3] = c[3];
    r[2] = ( c[2] + c[3] ) / 2;
    r[1] = ( mid + r[2] ) / 2;
    l[3] = r[0] = ( l[2] + r[1] ) / 2;
    for ( int i = 0; i < 4; ++i ) {
    l[i].w = 1.0;
    r[i].w = 1.0;
    }
}

//----------------------------------------------------------------------------

void
draw_patch( point4 p[4][4] )
{
    // Draw the quad (as two triangles) bounded by the corners of the
    //   Bezier patch.
    points[Index++] = p[0][0];
    points[Index++] = p[3][0];
    points[Index++] = p[3][3];
    points[Index++] = p[0][0];
    points[Index++] = p[3][3];
    points[Index++] = p[0][3];
}

//----------------------------------------------------------------------------

inline void
transpose( point4 a[4][4] )
{
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = i; j < 4; j++ ) {
        point4 t = a[i][j];
        a[i][j] = a[j][i];
        a[j][i] = t;
    }
    }
}

void
divide_patch( point4 p[4][4], int count )
{
    if ( count > 0 ) {
    point4 q[4][4], r[4][4], s[4][4], t[4][4];
    point4 a[4][4], b[4][4];

    // subdivide curves in u direction, transpose results, divide
    // in u direction again (equivalent to subdivision in v)
        for ( int k = 0; k < 4; ++k ) {
            divide_curve( p[k], a[k], b[k] );
    }

        transpose( a );
        transpose( b );

        for ( int k = 0; k < 4; ++k ) {
            divide_curve( a[k], q[k], r[k] );
            divide_curve( b[k], s[k], t[k] );
        }

    // recursive division of 4 resulting patches
        divide_patch( q, count - 1 );
        divide_patch( r, count - 1 );
        divide_patch( s, count - 1 );
        divide_patch( t, count - 1 );
    }
    else {
        draw_patch( p );
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    std::ifstream infile("patchPoints.txt");
    std::string s_x, s_y, s_z;
    float f_x, f_y, f_z;
    int patch_i = 0;
    while (infile >> s_x >> s_y >> s_z)
    {
        point3 a;
        a[0] = atof(s_x.c_str());
        a[1] = atof(s_y.c_str());
        a[2] = atof(s_z.c_str());
        patch_i++;
    }

    // Initialize each patch's control point data
    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 4; ++j ) {
        point3& v = vertices[indices[0][i][j]];
        patch[i][j] = point4( v[X], v[Y], v[Z], 1.0 );
        }
    }

    // Subdivide the patch
    divide_patch( patch, NumTimesToSubdivide );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    Projection = glGetUniformLocation( program, "Projection" );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    r_x = 0.58539;
    r_y = 0.78539;
    r_z = 0.57079;
}

//----------------------------------------------------------------------------

void
redraw (void)
{

    // Initialize each patch's control point data
    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 4; ++j ) {
        point3& v = vertices[indices[0][i][j]];
        patch[i][j] = point4( v[X], v[Y], v[Z], 1.0 );
        }
    }

    Index = 0;
    NumQuadsPerPatch = (int) pow( PatchesPerSubdivision, NumTimesToSubdivide );
    NumTriangles = ( NumQuadsPerPatch * 2 );
    divide_patch( patch, NumTimesToSubdivide );
}

void
display( void )
{
    redraw();
    glClearDepth(0.0);
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glClear( GL_COLOR_BUFFER_BIT );
    glUniform1f(glGetUniformLocation( program, "r_x" ), r_x);
    glUniform1f(glGetUniformLocation( program, "r_y" ), r_y);
    glUniform1f(glGetUniformLocation( program, "r_z" ), r_z);
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
        glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);
        glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 4; ++j ) {
            point3& v = vertices[indices[0][i][j]];
            if (i*4 + j == selectedPoint){
                glPointSize(10.0);
                glBegin(GL_POINTS);
                glVertex3fv(v);
                glEnd();
                glPointSize(5.0);
            } else {
                glBegin(GL_POINTS);
                glVertex3fv(v);
                glEnd();
            }
        }
    }
    for (int i = 0; i < NumVertices; i++){
        points[i] = point4();
    }
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    GLfloat  left = -1.0, right = 7.0;
    GLfloat  bottom = -1.0, top = 7.0;
    GLfloat  zNear = -10.0, zFar = 10.0;

    GLfloat  aspect = GLfloat(width)/height;

    if ( aspect > 0 ) {
    left *= aspect;
    right *= aspect;
    }
    else {
    bottom /= aspect;
    top /= aspect;
    }

    mat4 projection = Ortho( left, right, bottom, top, zNear, zFar );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case 'x' : r_x = r_x-delta; break;
        case 'y' : r_y = r_y-delta; break;
        case 'z' : r_z = r_z-delta; break;
        case 'X' : r_x = r_x+delta; break;
        case 'Y' : r_y = r_y+delta; break;
        case 'Z' : r_z = r_z+delta; break;
        case 'p' : selectedPoint = (selectedPoint + 1) % 16; break;
        case 'r' : if (NumTimesToSubdivide < 6) {NumTimesToSubdivide += 1;}; break;
        case 'R' : if (NumTimesToSubdivide > 3) {NumTimesToSubdivide -= 1;}; break;
        case 'q' : vertices[selectedPoint][0] += 0.01; redraw(); break;
        case 'w' : vertices[selectedPoint][1] += 0.01; redraw(); break;
        case 'e' : vertices[selectedPoint][2] += 0.01; redraw(); break;
        case 'Q' : vertices[selectedPoint][0] -= 0.01; redraw(); break;
        case 'W' : vertices[selectedPoint][1] -= 0.01; redraw(); break;
        case 'E' : vertices[selectedPoint][2] -= 0.01; redraw(); break;

    }
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "a7" );

    glewInit();
    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
