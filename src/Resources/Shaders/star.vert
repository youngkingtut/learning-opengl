layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform float time;
uniform mat4 proj_matrix;
uniform mat4 view_matrix;

out vec4 starColor;

void main() {
    float size = 0.0001 * (1000 + position.z) * (1000 + position.z);
    starColor = smoothstep(1.0, 7.0, size) * color;

    gl_Position = proj_matrix * view_matrix * position;
    gl_PointSize = size;
}
