
#include "Angel.h"

unsigned int vao[9];
unsigned int buffer[18];

void makecircle()
{

}

void makesquare(GLfloat color, GLfloat scale, int varr_id, int vbuff_id, int cbuff_id)
{
    GLfloat x = 0.0f;
    GLfloat y = -0.2f;
    GLfloat vertices2[] = { x, y, 0.0f, 
                            x+(0.1f*scale),y+(0.1f*scale),0.0f,
                            x-(0.1f*scale),y+(0.1f*scale),0.0f,
                            x-(0.1f*scale),y-(0.1f*scale),0.0f, 
                            x+(0.1f*scale),y-(0.1f*scale),0.0f, 
                            x+(0.1f*scale),y+(0.1f*scale),0.0f};

    GLfloat colors2[] = {   color, color, color,
                            color, color, color,
                            color, color, color,
                            color, color, color,
                            color, color, color,
                            color, color, color};

    // Create and initialize a buffer object
    glBindVertexArray(vao[varr_id]);
    glGenBuffers(2, &buffer[vbuff_id]);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, buffer[vbuff_id]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, buffer[cbuff_id]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), colors2, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[varr_id]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
}

void maketriangle(int varr_id, int vbuff_id, int cbuff_id)
{
    GLfloat vertices[] =  {    0.0f,1.0f,0.0f,
                        -0.259f,0.55f,0.0f,
                        0.259f,0.55f,0.0f };
    GLfloat colors[] = {    1.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 1.0f };

    // Create and initialize a buffer object
    glBindVertexArray(vao[varr_id]);
    glGenBuffers(2, buffer);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, buffer[vbuff_id]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, buffer[cbuff_id]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), colors, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[varr_id]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/3);
}

//----------------------------------------------------------------------------

void
init( void )
{
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    glGenVertexArrays(9, &vao[0]);
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window

    maketriangle(0, 0, 1);
    makesquare(1.0f, 6.0f, 1, 2, 3);
    makesquare(0.0f, 5.0f, 2, 4, 5);
    makesquare(1.0f, 4.0f, 3, 6, 7);
    makesquare(0.0f, 3.0f, 4, 8, 9);
    makesquare(1.0f, 2.0f, 5, 10, 11);
    makesquare(0.0f, 1.0f, 6, 12, 13);

    glFlush();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int main (int argc, char* argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 500,500 );

    glutCreateWindow( "Red Triangle" );
    glewExperimental=GL_TRUE;
    glewInit();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
