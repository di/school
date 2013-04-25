// g++ -O3 circles.cpp -o circles -lglut -lGL
#include "Angel.h"
#include <GL/glut.h>
#include <vector>
#include <cmath>
using namespace std;

enum Color { WHITE, BLACK, RED, GREEN, BLUE };
float s_red = 1.0;
float s_green = 1.0;
float s_blue = 1.0;
float w2_red = 1.0;
float w2_green, w2_blue;
int offset = 0;
float pi_offset = 0.0;
float sc_offset = 1.0;
int first, second;

struct Shape
{
    Shape(float xx, float yy, float xsc, float ysc, float rr, float gg, float bb, int sds)
    {
        x = xx;
        y = yy;
        xs = xsc;
        ys = ysc;
        r = rr;
        g = gg;
        b = bb;
        sd = sds;
    }

    void draw(int direction)
    {
        vector< float > Colors;

        for( unsigned int i = 0; i <= sd+1; ++i )
        {
            Colors.push_back( r);
            Colors.push_back( g);
            Colors.push_back( b);
        }

        buf.push_back( 0+x );
        buf.push_back( 0+y );

        for( int i = 0; i <= sd; ++i )
        {
            float angle = i * ((2.0f * 3.1416f) / sd) + (1+(0.5*(sd%2)))*(3.1416f / sd);
            angle += direction * pi_offset;
            buf.push_back( xs*cos(angle)+x );
            buf.push_back( ys*sin(angle)+y );
        }

        glColorPointer(3, GL_FLOAT, 0, &Colors[0]);
        glVertexPointer( 2, GL_FLOAT, 0, &buf[0] );
        glDrawArrays( GL_TRIANGLE_FAN, 0, buf.size() / 2 );
    }

    void drawRGB(void)
    {
        vector< float > Colors;
        Colors.push_back(1.0f);
        Colors.push_back(0.0f);
        Colors.push_back(0.0f);
        //
        Colors.push_back(0.0f);
        Colors.push_back(1.0f);
        Colors.push_back(0.0f);
        //
        Colors.push_back(0.0f);
        Colors.push_back(0.0f);
        Colors.push_back(1.0f);

        for( int i = 0; i <= sd; ++i )
        {
            float angle = i * ((2.0f * 3.1416f) / sd) + (1+(0.5*(sd%2)))*(3.1416f / sd);
            buf.push_back( xs*cos(angle)+x );
            buf.push_back( ys*sin(angle)+y );
        }

        glColorPointer(3, GL_FLOAT, 0, &Colors[0]);
        glVertexPointer( 2, GL_FLOAT, 0, &buf[0] );
        glDrawArrays( GL_TRIANGLE_FAN, 0, buf.size() / 2 );
    }

    void drawSweep(void)
    {
        vector< float > Colors;

        for( unsigned int i = 0; i <= sd+1; ++i )
        {
            Colors.push_back( r * ((float)i/(float)sd));
            Colors.push_back( g * ((float)i/(float)sd));
            Colors.push_back( b * ((float)i/(float)sd));
        }

        for( int i = 0; i <= sd; ++i )
        {
            float angle = i * ((2.0f * 3.1416f) / sd) + (1+(0.5*(sd%2)))*(3.1416f / sd);
            buf.push_back( (xs*sc_offset)*cos(angle)+x );
            buf.push_back( (ys*sc_offset)*sin(angle)+y );
        }

        glColorPointer(3, GL_FLOAT, 0, &Colors[0]);
        glVertexPointer( 2, GL_FLOAT, 0, &buf[0] );
        glDrawArrays( GL_TRIANGLE_FAN, 0, buf.size() / 2 );

    }

    void drawBreath()
    {
        vector< float > Colors;

        for( unsigned int i = 0; i <= sd+1; ++i )
        {
            Colors.push_back( r);
            Colors.push_back( g);
            Colors.push_back( b);
        }

        buf.push_back( 0+x );
        buf.push_back( 0+y );

        for( int i = 0; i <= sd; ++i )
        {
            float angle = i * ((2.0f * 3.1416f) / sd) + (1+(0.5*(sd%2)))*(3.1416f / sd);
            buf.push_back( (xs*sc_offset)*cos(angle)+x );
            buf.push_back( (ys*sc_offset)*sin(angle)+y );
        }

        glColorPointer(3, GL_FLOAT, 0, &Colors[0]);
        glVertexPointer( 2, GL_FLOAT, 0, &buf[0] );
        glDrawArrays( GL_TRIANGLE_FAN, 0, buf.size() / 2 );
    }



    vector< float > glAngleFan()
    {

        return buf;
    }

    float x, y, xs, ys, r, g, b;
    int sd;
    vector< float > buf;
};

void init()
{
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);

    Shape square1 = Shape(0.0, -0.2, 0.8, 0.8, 1.0f, 1.0f, 1.0f, 4) ;
    square1.draw(1);
    Shape square2 = Shape(0.0, -0.2, 0.666, 0.666, 0.0f, 0.0f, 0.0f, 4) ;
    square2.draw(1);
    Shape square3 = Shape(0.0, -0.2, 0.532, 0.532, 1.0f, 1.0f, 1.0f, 4) ;
    square3.draw(1);
    Shape square4 = Shape(0.0, -0.2, 0.398, 0.398, 0.0f, 0.0f, 0.0f, 4) ;
    square4.draw(1);
    Shape square5 = Shape(0.0, -0.2, 0.264, 0.264, 1.0f, 1.0f, 1.0f, 4) ;
    square5.draw(1);
    Shape square6 = Shape(0.0, -0.2, 0.13, 0.13, 0.0f, 0.0f, 0.0f, 4) ;
    square6.draw(1);
    Shape circleSweep = Shape(0.6, 0.7, 0.2, 0.2, 1.0f, 0.0f, 0.0f, 100);
    circleSweep.drawSweep();

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
    glutSwapBuffers();
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);

    Shape triangle = Shape(0.0, 0.7, 0.3, 0.3, w2_red, w2_green, w2_blue, 3);
    triangle.draw(-1);
    Shape circle = Shape(0.6, 0.7, 0.2, 0.2, w2_red, w2_green, w2_blue, 100);
    circle.drawBreath();

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
    glutSwapBuffers();
}

void sub()
{
    glClearColor(s_red, s_green, s_blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);

    Shape circ60 = Shape(0.0, 0.0, 1.0, 0.6, 1.0f, 0.0f, 0.0f, 100) ;
    circ60.draw(0);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
    glutSwapBuffers();
}

void processMenuEvents(int option)
{
switch (option)
 {
 case RED : s_red = 1.0; s_green = 0.0; s_blue = 0.0; break;
 case GREEN : s_red = 0.0; s_green = 1.0; s_blue = 0.0; break;
 case BLUE : s_red = 0.0; s_green = 0.0; s_blue = 1.0; break;
 case WHITE : s_red = 1.0; s_green = 1.0; s_blue = 1.0; break;
 case BLACK: s_red = 0.0; s_green = 0.0; s_blue = 0.0; break;
 }
 glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y) 
{
    switch(key)
{
    case 'r' : w2_red = 1.0; w2_green = 0.0; w2_blue = 0.0; break;
    case 'g' : w2_red = 0.0; w2_green = 1.0; w2_blue = 0.0; break;
    case 'b' : w2_red = 0.0; w2_green = 0.0; w2_blue = 1.0; break;
    case 'y' : w2_red = 1.0; w2_green = 1.0; w2_blue = 0.0; break;
    case 'o' : w2_red = 1.0; w2_green = 0.5; w2_blue = 0.0; break;
    case 'p' : w2_red = 1.0; w2_green = 0.0; w2_blue = 1.0; break;
    case 'w' : w2_red = 1.0; w2_green = 1.0; w2_blue = 1.0; break;
}
 glutPostRedisplay();
}

void myidle()
{
 offset = (offset + 1) % 90;
 pi_offset = offset * ((2.0f * 3.1416f)/90);
 sc_offset = float(offset) / 90.0f;
 if (offset > 45)
{
    sc_offset = 1.0f-sc_offset;
}
 sc_offset = 2*sc_offset;
 glutSetWindow(first);
 glutPostRedisplay();
 glutSetWindow(second);
 glutPostRedisplay();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize( 500, 500 );
    
    first = glutCreateWindow( "Red Triangle" );
    glutDisplayFunc( display );
    glutIdleFunc(myidle);

    glutCreateSubWindow(first, 0, 0, 150, 150);
    glutDisplayFunc( sub );
    int menu;
    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("White",WHITE);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Blue",BLUE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    second = glutCreateWindow( "window 2");
    glutDisplayFunc( display2 );
    glutKeyboardFunc(mykey);
    glutIdleFunc(myidle);


    glewExperimental=GL_TRUE;
    glewInit();
    init();


    glutMainLoop();
    return 0;
}
