#version 330 core

layout (location = 1) in vec3 aPos;

void main() {
  gl_Position = vec4(aPos, 1.0);
}
