// g++ -O3 circles.cpp -o circles -lglut -lGL
#include "Angel.h"
#include <GL/glut.h>
#include <vector>
#include <cmath>
using namespace std;

struct Shape
{
    Shape(float xx, float yy, float xsc, float ysc, int rr, int gg, int bb, int sds)
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

    void draw(void)
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
            buf.push_back( xs*cos(angle)+x );
            buf.push_back( ys*sin(angle)+y );
        }

        glColorPointer(3, GL_FLOAT, 0, &Colors[0]);
        glVertexPointer( 2, GL_FLOAT, 0, &buf[0] );
        glDrawArrays( GL_TRIANGLE_FAN, 0, buf.size() / 2 );

    }

    vector< float > glAngleFan()
    {

        return buf;
    }

    float x, y, xs, ys;
    int r, g, b, sd;
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

    Shape circ60 = Shape(-0.6, 0.75, 0.2, 0.12, 1.0f, 0.0f, 0.0f, 100) ;
    circ60.draw();
    Shape square1 = Shape(0.0, -0.2, 0.8, 0.8, 1.0f, 1.0f, 1.0f, 4) ;
    square1.draw();
    Shape square2 = Shape(0.0, -0.2, 0.666, 0.666, 0.0f, 0.0f, 0.0f, 4) ;
    square2.draw();
    Shape square3 = Shape(0.0, -0.2, 0.532, 0.532, 1.0f, 1.0f, 1.0f, 4) ;
    square3.draw();
    Shape square4 = Shape(0.0, -0.2, 0.398, 0.398, 0.0f, 0.0f, 0.0f, 4) ;
    square4.draw();
    Shape square5 = Shape(0.0, -0.2, 0.264, 0.264, 1.0f, 1.0f, 1.0f, 4) ;
    square5.draw();
    Shape square6 = Shape(0.0, -0.2, 0.13, 0.13, 0.0f, 0.0f, 0.0f, 4) ;
    square6.draw();
    Shape triangleRGB = Shape(0.0, 0.7, 0.3, 0.3, 1.0f, 0.0f, 0.0f, 3);
    triangleRGB.drawRGB();
    Shape circleSweep = Shape(0.6, 0.7, 0.2, 0.2, 1.0f, 0.0f, 0.0f, 100);
    circleSweep.drawSweep();


    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 500, 500 );

    glutCreateWindow( "Red Triangle" );
    glewExperimental=GL_TRUE;
    glewInit();
    init();

    glutDisplayFunc( display );

    glutMainLoop();
    return 0;
}
