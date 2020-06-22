layout (location = 0) out vec4 color;

uniform sampler2D starTexture;
in vec4 starColor;

void main() {
    float texSample = texture(starTexture, gl_PointCoord).x;

    color = starColor * vec4(texSample, texSample, texSample, 1);
}
