layout (location = 0) in vec4 position;
out vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec4 objectColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
    color = objectColor;
}
