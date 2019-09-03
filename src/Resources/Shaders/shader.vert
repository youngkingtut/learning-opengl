layout (location = 0) in vec4 position;
out vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
