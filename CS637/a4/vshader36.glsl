attribute vec4 vPosition;
attribute vec4 vColor;
uniform float r_x, r_y, r_z, s_x, s_y, s_z, t_x, t_y, t_z;
varying vec4 color;

mat4 scale() {
    return mat4(s_x, 0, 0, 0,
                0, s_y, 0, 0,
                0, 0, s_z, 0,
                0, 0, 0, 1);
}

mat4 rotate() {
    float cx = cos(r_x);
    float cy = cos(r_y);
    float cz = cos(r_z);
    float sx = sin(r_x);
    float sy = sin(r_y);
    float sz = sin(r_z);
    mat4 m_x = mat4(1, 0, 0, 0,
                    0, cx, -sx, 0,
                    0, sx, cx, 0,
                    0, 0, 0, 1);
    mat4 m_y = mat4(cy, 0, sy, 0,
                    0, 1, 0, 0,
                    -sy, 0, cy, 0,
                    0, 0, 0, 1);
    mat4 m_z = mat4(cz, -sz, 0, 0,
                    sz, cz, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
    return m_x * m_y * m_z;
}

mat4 trans() {
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                t_x, t_y, t_z, 1);
}

void main()
{
    gl_Position = scale() * rotate() * trans() * vPosition;
    color = vColor;
}
