#version 130

in  vec3 ex_Color;

void
main()
{
    gl_FragColor = vec4(ex_Color,1.0);
}
