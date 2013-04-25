#version 330 core

in  vec2 in_Position;
in  vec3 gl_Color;
out vec3 ex_Color;
 
void
main()
{
    ex_Color = gl_Color;
    gl_Position = vec4(in_Position, 0.0, 1.0);
}
