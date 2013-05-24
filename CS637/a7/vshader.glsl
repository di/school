attribute  vec4 vPosition;

uniform mat4 Projection;
uniform float r_x, r_y, r_z;

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

void main() 
{
    gl_Position = Projection * rotate() * vPosition;
} 
