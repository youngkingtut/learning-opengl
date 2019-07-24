layout (location = 1) in vec4 position;
out vec4 color;

uniform mat4 proj_matrix;
uniform mat4 mv_matrix;

void main()
{
  gl_Position = proj_matrix * mv_matrix * position;
  color = position * 2.0 * vec4(0.5, 0.5, 0.5, 1.0);
}
